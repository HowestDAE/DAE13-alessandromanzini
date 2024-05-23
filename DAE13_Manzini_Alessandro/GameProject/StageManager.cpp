#include "pch.h"
#include "StageManager.h"
#include "ResourcesLinker.h"
#include "PlatformManager.h"
#include "Cuphead.h"
#include "Toyduck.h"
#include "Card.h"
#include "NonInterractableProp.h"
#include "Projectile.h"

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

void StageManager::Start( )
{
	m_IsHalted = false;
}

void StageManager::Pause( )
{
	m_IsHalted = true;
}

void StageManager::Update( float elapsedSec )
{
	if ( m_IsHalted ) return;

	UpdateBackground( elapsedSec );
	UpdateEntities( elapsedSec );
	UpdateProjectiles( elapsedSec );
	
	if ( !m_IsCameraFixed )
	{
		m_pCamera->Aim( m_pPlayer->GetLocation( ).ToPoint2f(), m_pPlayer->GetTextureWidth( ) );
	}

	CheckCollisions( );

	m_HUDManager.Update( elapsedSec );
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

void StageManager::UpdateProjectiles( float elapsedSec )
{

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

void StageManager::KeyPressEvent( const SDL_KeyboardEvent& e )
{
	m_pPlayer->KeyPressEvent( e );
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
