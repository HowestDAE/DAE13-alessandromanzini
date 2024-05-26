#include "pch.h"
#include "StageManager.h"
#include "Constants.h"
#include "ResourcesLinker.h"
#include "PlatformManager.h"
#include "Cuphead.h"
#include "Card.h"
#include "Toyduck.h"
#include "Toycar.h"
#include "NonInterractableProp.h"
#include "Projectile.h"
#include "CSVReader.h"

const float StageManager::smk_RequestTitleScreenDelay{ 1.5f };

StageManager::StageManager( Camera* pCamera, ResourcesLinker* pResourcesLinker )
	: m_pCamera{ pCamera }
	, m_pResourcesLinker{ pResourcesLinker }
	, m_PlatformManager{ "csv/platform_layout.csv" }
	, m_HUDManager{}
	, m_IsHalted{ true }
	, m_IsCameraFixed{ false }

	, m_RequestTitleScreenElapsedTime{}
	, m_RequestingTitleScreen{}
	, m_RequestTitleScreen{}

	, m_pCards{}
	, m_pEntities{}
	, m_BackgroundProps{}
	, m_FrontgroundProps{}
{
	Initialize( );
}

StageManager::~StageManager( )
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
}

void StageManager::Pause( ) noexcept
{
	m_IsHalted = true;
}

void StageManager::Update( float elapsedSec )
{
	if ( m_IsHalted ) return;

	UpdateBackground( elapsedSec );
	UpdateEntities( elapsedSec );
	CheckRequestTitleScreen( elapsedSec );
	
	if ( !m_IsCameraFixed )
	{
		m_pCamera->Aim( m_pPlayer->GetLocation( ).ToPoint2f(), m_pPlayer->GetTextureWidth( ) );
	}

	CheckCollisions( );

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
	InitializeEntities( );
	InitializeHUD( );

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

void StageManager::InitializeEntities( )
{
	m_pPlayer = new Cuphead( Constants::sk_CupheadStartingPosition, &m_HUDManager );
	m_pPlayer->LinkTexture( m_pResourcesLinker );

	LoadEnemiesFromFile( "csv/enemies_layout.csv", m_pEnemies );
	LoadEntitiesFromFile( "csv/cards_layout.csv", m_pCards );
}

void StageManager::InitializeHUD( )
{
	m_HUDManager.LinkTexture( m_pResourcesLinker );
}

void StageManager::LoadLevelStartAnimation( )
{
	m_pCamera->QueueScreenTexture( m_pResourcesLinker->GetSprite( "iris_transition" ) );
	m_pCamera->QueueScreenTexture( m_pResourcesLinker->GetSprite( "run_n_gun" ) );
	m_pCamera->FeedInScreenTexture( );
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

	case 1: // Toyduck
		pEntity = new Toyduck( Point2f{ reader.GetFloat( "x" ), reader.GetFloat( "y" ) }, reader.GetFloat( "aggro" ), reader.GetFloat( "drop" ) );
		break;

	case 2: // Toycar
		pEntity = new Toycar( Point2f{ reader.GetFloat( "x" ), reader.GetFloat( "y" ) }, reader.GetFloat( "aggro" ), reader.GetFloat( "drop" ), 3 );
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

	for ( Entity* pEntity : m_pEntities )
	{
		pEntity->Update( elapsedSec );
	}
}

void StageManager::CheckRequestTitleScreen( float elapsedSec )
{
	if ( m_RequestingTitleScreen )
	{
		m_RequestTitleScreenElapsedTime += elapsedSec;
		if ( m_RequestTitleScreenElapsedTime >= smk_RequestTitleScreenDelay )
		{
			m_RequestTitleScreen = true;
		}
	}
}

void StageManager::CheckCollisions( )
{
	m_pPlayer->CheckCollision( &m_PlatformManager );

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
		m_pPlayer->CheckCollision( *static_cast<Card*>( pCard ) );
	}
}

void StageManager::LockCamera( const Point2f& centerPoint )
{
	m_IsCameraFixed = true;
	m_pCamera->Aim( centerPoint );
	// create boundaries with platformmanager
}

void StageManager::UnlockCamera( )
{
	m_IsCameraFixed = false;
	// clear platformmanager boundaries
}
