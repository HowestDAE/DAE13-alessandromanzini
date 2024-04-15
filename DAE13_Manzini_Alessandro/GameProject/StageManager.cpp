#include "pch.h"
#include "StageManager.h"
#include "ResourcesLinker.h"
#include "PlatformManager.h"
#include "Cuphead.h"
#include "Toyduck.h"
#include "NonInterractableProp.h"
#include "Projectile.h"

StageManager::StageManager( Camera* pCamera, ResourcesLinker* pResourcesLinker )
	: m_pCamera{ pCamera }
	, m_pResourcesLinker{ pResourcesLinker }
	, m_PlatformManager{}
	, m_IsHalted{ true }
	, m_IsCameraFixed{ false }

	, m_BackgroundProps{}
	, m_FrontgroundProps{}
{
	Initialize( );
}

StageManager::~StageManager( )
{
	delete m_pPlayer;
	delete m_pToyduck;
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
		m_pCamera->Aim( m_pPlayer->GetPosition( ), m_pPlayer->GetTextureWidth() );
	}

	CheckCollisions( );
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
}

void StageManager::UpdateProjectiles( float elapsedSec )
{

}

void StageManager::CheckCollisions( )
{
	m_PlatformManager.CheckCollision( m_pPlayer );

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

Cuphead const* StageManager::GetPlayer( ) const
{
	return m_pPlayer;
}

Toyduck const* StageManager::GetToyduck( ) const
{
	return m_pToyduck;
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
