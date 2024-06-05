#include "pch.h"
#include "StageManager.h"
#include "SoundManager.h"
#include "Constants.h"
#include "ResourcesLinker.h"
#include "PlatformManager.h"
#include "Cuphead.h"
#include "Card.h"
#include "Coin.h"
#include "Toyduck.h"
#include "Toycar.h"
#include "Funwall.h"
#include "NonInterractableProp.h"
#include "Projectile.h"
#include "CSVReader.h"
#include <iostream>

const float StageManager::smk_RequestTitleScreenDelay{ 1.5f };
const float StageManager::smk_RequestWinScreenDelay{ 2.f };

StageManager::StageManager( Camera* pCamera, ResourcesLinker* pResourcesLinker )
	: m_pCamera{ pCamera }
	, m_pResourcesLinker{ pResourcesLinker }
	, m_PlatformManager{ "csv/platform_layout.csv", "csv/finishline_layout.csv", pCamera->GetViewPort( )}
	, m_HUDManager{}
	, m_IsHalted{ true }
	, m_IsCameraFixed{ false }

	, m_TotalElapsedTime{}

	, m_RequestTitleScreenElapsedTime{}
	, m_RequestingTitleScreen{}
	, m_RequestTitleScreen{}

	, m_RequestWinScreenElapsedTime{}
	, m_RequestingWinScreen{}
	, m_RequestWinScreen{}

	, m_DeathScreenLoaded{}

	, mk_pLockedEnemy{}

	, m_pEntities{}
	, m_pEnemies{}
	, m_pCards{}
	, m_pCoins{}
	, m_BackgroundProps{}
	, m_FrontgroundProps{}

	, m_CollectedCoinsCount{}
{
	Initialize( );
}

StageManager::~StageManager( ) noexcept
{
	delete m_pPlayer;

	for ( Entity* pEntity : m_pEntities )
	{
		delete pEntity;
	}
	m_pEntities.clear( );
	m_pEnemies.clear( );
	m_pCards.clear( );
}

void StageManager::Start( ) noexcept
{
	m_IsHalted = false;
	SoundManager::Loop( "bg_music" );
	SoundManager::Play( "intro" );
}

void StageManager::Pause( ) noexcept
{
	m_IsHalted = true;
	SoundManager::Loop( "bg_music", true );
}

void StageManager::Update( float elapsedSec )
{
	if ( m_IsHalted ) return;

	m_TotalElapsedTime += elapsedSec;

	UpdateBackground( elapsedSec );
	UpdateEntities( elapsedSec );
	CheckScreenRequests( elapsedSec );
	
	if ( !m_IsCameraFixed && !GetIsGameOver( ) )
	{
		m_pCamera->Aim( m_PlatformManager.GetCameraPoint( m_pPlayer ), m_pPlayer->GetTextureWidth( ) );
	}

	CheckCollisions( );
	CheckPlayerState( );

	m_HUDManager.Update( elapsedSec );
}

void StageManager::KeyPressEvent( const SDL_KeyboardEvent& e )
{
	const bool pressed{ e.type == SDL_KEYDOWN };
	switch ( e.keysym.sym )
	{
	case SDLK_ESCAPE:
		if ( pressed )
		{
			if ( m_IsHalted )
			{
				Start( );
			}
			else
			{
				Pause( );
			}
			return;
		}

	case SDLK_q:
		if ( pressed )
		{
			m_RequestingTitleScreen = true;
		}
		else
		{
			m_RequestingTitleScreen = false;
			m_RequestTitleScreenElapsedTime = 0.f;
		}
		return;
	}
	
	m_pPlayer->KeyPressEvent( e );
}

bool StageManager::GetIsHalted( ) const
{
	return m_IsHalted;
}

bool StageManager::GetRequestTitleScreen( ) const
{
	return m_RequestTitleScreen;
}

bool StageManager::GetRequestWinScreen( GameStats& gameStats ) const
{
	if ( m_RequestWinScreen )
	{
		gameStats.time = m_TotalElapsedTime;
		gameStats.collectedCoins = m_CollectedCoinsCount;
		gameStats.totalCoins = static_cast<int>( m_pCoins.size( ) );
		gameStats.grade = 'A';

		return true;
	}
	return false;
}

const std::vector<NonInterractableProp>& StageManager::GetBackgroundProps( ) const
{
	return m_BackgroundProps;
}

const std::vector<NonInterractableProp>& StageManager::GetFrontgroundProps( ) const
{
	return m_FrontgroundProps;
}

PlatformManager const* StageManager::GetPlatformManager( ) const
{
	return &m_PlatformManager;
}

HUDManager const* StageManager::GetHUDManager( ) const
{
	return &m_HUDManager;
}

Cuphead const* StageManager::GetPlayer( ) const
{
	return m_pPlayer;
}

const std::vector<Entity*>& StageManager::GetEntities( ) const
{
	return m_pEntities;
}

void StageManager::Initialize( )
{
	InitializeProps( "csv/bg_design.csv" );
	InitializeEntities( "csv/enemies_layout.csv", "csv/cards_layout.csv", "csv/coins_layout.csv" );
	InitializeHUD( );
	InitializeSounds( "csv/level_sound_settings.csv" );

	LoadLevelStartAnimation( );
}

void StageManager::InitializeProps( const std::string& propsCsvPath )
{
	CSVReader reader{ propsCsvPath };

	while ( !reader.eof( ) )
	{
		CreateNIP( static_cast<StageManager::BackgroundScope>(reader.GetInt( "depth" )),
			reader.Get( "label" ),
			Point2f{ reader.GetFloat( "x" ), reader.GetFloat( "y" ) } );

		reader.next( );
	}
}

void StageManager::InitializeEntities( const std::string& enemiesCsvPath, const std::string& cardsCsvPath, const std::string& coinsCsvPath )
{
	m_pPlayer = new Cuphead( Constants::sk_CupheadStartingPosition, &m_HUDManager );
	m_pPlayer->LinkTexture( m_pResourcesLinker );

	LoadEnemiesFromFile( enemiesCsvPath, m_pEnemies );
	LoadEntitiesFromFile( cardsCsvPath, m_pCards );
	LoadEntitiesFromFile( coinsCsvPath, m_pCoins );
}

void StageManager::InitializeHUD( )
{
	m_HUDManager.LinkTexture( m_pResourcesLinker );
}

void StageManager::InitializeSounds( const std::string& soundsCsvPath )
{
}

void StageManager::LoadLevelStartAnimation( )
{
	m_pCamera->QueueScreenTexture( m_pResourcesLinker->GetSprite( "iris_transition" ) );
	m_pCamera->QueueScreenTexture( m_pResourcesLinker->GetSprite( "run_n_gun" ) );
	m_pCamera->FeedInScreenTexture( );

	SoundManager::Reset( );
}

void StageManager::LoadPlayerDeathAnimation( )
{
	m_pCamera->QueueScreenTexture( m_pResourcesLinker->GetSprite( "you_died_screen" ) );
	m_pCamera->FeedInScreenTexture( );

	SoundManager::Loop( "bg_music", true );
	SoundManager::Play( "game_over" );
	
	m_DeathScreenLoaded = true;
}

void StageManager::LoadLevelWinAnimation( )
{
	m_pCamera->QueueScreenTexture( m_pResourcesLinker->GetSprite( "bravo" ) );
	m_pCamera->QueueScreenTexture( m_pResourcesLinker->GetSprite( "iris_transition_reversed" ) );
	m_pCamera->FeedInScreenTexture( );

	SoundManager::Play( "bravo" );
	
	m_RequestingWinScreen = true;
}

void StageManager::LoadEntitiesFromFile( const std::string& csvPath, std::vector<Entity*>& pEntities )
{
	CSVReader reader{ csvPath };

	while ( !reader.eof( ) )
	{
		Entity* const pEntity{ CreateEntity( reader ) };

		pEntities.push_back( pEntity );
		
		reader.next( );
	}
}

void StageManager::LoadEnemiesFromFile( const std::string& csvPath, std::vector<Enemy*>& pEnemies )
{
	CSVReader reader{ csvPath };

	while ( !reader.eof( ) )
	{
		Enemy* const pEntity{ static_cast<Enemy*>( CreateEntity( reader ) ) };

		pEnemies.push_back( pEntity );

		reader.next( );
	}
}

void StageManager::CreateNIP( BackgroundScope scope, const std::string& uid, const Point2f& position, float scale )
{
	NonInterractableProp temp{ int( scope ), (Vector2f( position ) / scale).ToPoint2f( ), uid, scale };
	temp.LinkTexture( m_pResourcesLinker );

	if ( scope >= BackgroundScope::midground1 )
	{
		m_BackgroundProps.push_back( temp );
	}
	else
	{
		m_FrontgroundProps.push_back( temp );
	}
}

Entity* StageManager::CreateEntity( const CSVReader& reader )
{
	Entity* pEntity{};

	switch ( reader.GetInt( "id" ) )
	{
	case 0: // Card
		pEntity = new Card( Point2f{ reader.GetFloat( "x" ), reader.GetFloat( "y" ) } );
		break;

	case 1: // Coin
		pEntity = new Coin( Point2f{ reader.GetFloat( "x" ), reader.GetFloat( "y" ) } );
		break;

	case 2: // Toyduck
		pEntity = new Toyduck( Point2f{ reader.GetFloat( "x" ), reader.GetFloat( "y" ) }, reader.GetFloat( "aggro" ), reader.GetFloat( "drop" ), reader.GetBoolean( "quirk" ) );
		break;

	case 3: // Toycar
		pEntity = new Toycar( Point2f{ reader.GetFloat( "x" ), reader.GetFloat( "y" ) }, reader.GetFloat( "aggro" ), reader.GetFloat( "drop" ), 4, reader.GetBoolean( "quirk" ) );
		break;

	case 4: // Funwall
		pEntity = new Funwall( Point2f{ reader.GetFloat( "x" ), reader.GetFloat( "y" ) }, reader.GetFloat( "aggro" ), reader.GetFloat( "drop" ) );
		break;
	}
	pEntity->LinkTexture( m_pResourcesLinker );
	m_pEntities.push_back( pEntity );

	return pEntity;
}

void StageManager::UpdateBackground( float elapsedSec )
{
	for ( NonInterractableProp& prop : m_BackgroundProps )
	{
		prop.Update( elapsedSec );
	}
	for ( NonInterractableProp& prop : m_FrontgroundProps )
	{
		prop.Update( elapsedSec );
	}
}

void StageManager::UpdateEntities( float elapsedSec )
{
	m_pPlayer->Update( elapsedSec );

	for ( Enemy* pEnemy : m_pEnemies )
	{
		pEnemy->Update( elapsedSec, m_pPlayer->GetLocation () );

		if ( pEnemy->GetIsScreenLock( ) )
		{
			LockCamera( m_PlatformManager.GetCameraPoint( pEnemy ) );
			mk_pLockedEnemy = pEnemy;
		}
	}

	for ( Entity* pCard : m_pCards )
	{
		pCard->Update( elapsedSec );
	}

	for ( Entity* pCoin : m_pCoins )
	{
		pCoin->Update( elapsedSec );
	}

	if ( m_IsCameraFixed && !mk_pLockedEnemy->GetIsAlive( ) )
	{
		UnlockCamera( );
		mk_pLockedEnemy = nullptr;
	}
}

void StageManager::CheckScreenRequests( float elapsedSec )
{
	if ( m_RequestingTitleScreen )
	{
		m_RequestTitleScreenElapsedTime += elapsedSec;
		if ( m_RequestTitleScreenElapsedTime >= smk_RequestTitleScreenDelay )
		{
			m_RequestTitleScreen = true;
		}
	}
	
	if ( m_RequestingWinScreen )
	{
		m_RequestWinScreenElapsedTime += elapsedSec;
		if ( m_RequestWinScreenElapsedTime >= smk_RequestWinScreenDelay )
		{
			m_RequestWinScreen = true;
		}
	}
}

void StageManager::CheckCollisions( )
{
	CheckPlayerCollisions( );
	CheckEntitiesCollisions( );
}

void StageManager::CheckPlayerCollisions( )
{
	m_pPlayer->CheckCollision( &m_PlatformManager );

	if ( m_PlatformManager.CheckFinishLine( m_pPlayer ) && !GetIsGameOver( ) )
	{
		LoadLevelWinAnimation( );
		m_pPlayer->Win( );
	}
}

void StageManager::CheckEntitiesCollisions( )
{
	for ( Enemy* pEnemy : m_pEnemies )
	{
		if ( pEnemy->CompareAggroDistance( m_pPlayer->GetLocation( ) ) )
		{
			if ( pEnemy->GetIsAlive( ) )
			{
				m_pPlayer->CheckCollision( *pEnemy );
			}
		}
	}

	for ( Entity* pCard : m_pCards )
	{
		m_pPlayer->CheckCollision( *static_cast<Card*>(pCard) );
	}

	for ( Entity* pCoin : m_pCoins )
	{
		if ( static_cast<Coin*>(pCoin)->CheckCollision( *m_pPlayer ) )
		{
			CollectCoin( );
		}
	}
}

void StageManager::CheckPlayerState( )
{
	if ( !m_pPlayer->GetIsAlive( ) && !GetIsGameOver( ) )
	{
		LoadPlayerDeathAnimation( );
	}
}

void StageManager::LockCamera( const Point2f& centerPoint )
{
	if ( !m_IsCameraFixed )
	{
		m_IsCameraFixed = true;
		m_pCamera->Aim( centerPoint );
		m_PlatformManager.SetCameraBounds( centerPoint );
	}
}

void StageManager::UnlockCamera( )
{
	m_IsCameraFixed = false;
	m_PlatformManager.DropCameraBounds( );
}

void StageManager::CollectCoin( ) noexcept
{
	++m_CollectedCoinsCount;
	std::cout << "[STAGE] Coin collected. Coins: " << m_CollectedCoinsCount << std::endl;
}

bool StageManager::GetIsGameOver( ) const
{
	return m_DeathScreenLoaded || m_RequestingWinScreen;
}
