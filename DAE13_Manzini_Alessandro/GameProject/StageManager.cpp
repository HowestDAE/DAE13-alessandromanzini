#include "pch.h"
#include "StageManager.h"
#include "Constants.h"
#include "ResourcesLinker.h"
#include "PlatformManager.h"
#include "Cuphead.h"
#include "Toyduck.h"
#include "Card.h"
#include "NonInterractableProp.h"
#include "Projectile.h"
#include "CSVReader.h"

StageManager::StageManager( Camera* pCamera, ResourcesLinker* pResourcesLinker )
	: m_pCamera{ pCamera }
	, m_pResourcesLinker{ pResourcesLinker }
	, m_PlatformManager{ "csv/platform_layout.csv" }
	, m_HUDManager{}
	, m_IsHalted{ true }
	, m_IsCameraFixed{ false }

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
	delete m_pToyduck;

	for ( Card* pCard : m_pCards )
	{
		delete pCard;
		pCard = nullptr;
	}
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
	
	if ( !m_IsCameraFixed )
	{
		m_pCamera->Aim( m_pPlayer->GetLocation( ).ToPoint2f(), m_pPlayer->GetTextureWidth( ) );
	}

	CheckCollisions( );

	m_HUDManager.Update( elapsedSec );
}

void StageManager::KeyPressEvent( const SDL_KeyboardEvent& e )
{
	if ( e.keysym.sym == SDLK_ESCAPE && e.type == SDL_KEYDOWN )
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
	
	m_pPlayer->KeyPressEvent( e );
}

bool StageManager::GetIsHalted( ) const
{
	return m_IsHalted;
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

	m_pToyduck = new Toyduck( Constants::sk_CupheadStartingPosition + Vector2f{ 1200.f, 0.f } );
	m_pToyduck->LinkTexture( m_pResourcesLinker );
	m_pEntities.push_back( m_pToyduck );

	Card* currentCard{ new Card( Point2f{ 570.f, 300.f } ) };
	currentCard->LinkTexture( m_pResourcesLinker );
	m_pCards.push_back( currentCard );
	m_pEntities.push_back( currentCard );

	currentCard = new Card( Point2f{ 1210.f, 325.f } );
	currentCard->LinkTexture( m_pResourcesLinker );
	m_pCards.push_back( currentCard );
	m_pEntities.push_back( currentCard );

}

void StageManager::InitializeHUD( )
{
	m_HUDManager.LinkTexture( m_pResourcesLinker );
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

void StageManager::LoadLevelStartAnimation( )
{
	m_pCamera->QueueScreenTexture( m_pResourcesLinker->GetSprite( "iris_transition" ) );
	m_pCamera->QueueScreenTexture( m_pResourcesLinker->GetSprite( "run_n_gun" ) );
	m_pCamera->FeedInScreenTexture( );
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
	m_pToyduck->Update( elapsedSec );

	for ( Card* pCard : m_pCards )
	{
		pCard->Update( elapsedSec );
	}
}

void StageManager::CheckCollisions( )
{
	m_pPlayer->CheckCollision( &m_PlatformManager );

	m_pPlayer->CheckCollision( *m_pToyduck );

	for ( Card* pCard : m_pCards )
	{
		m_pPlayer->CheckCollision( *pCard );
	}
	//m_pPlayer->CheckCollision( m_Cards[0] );
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
