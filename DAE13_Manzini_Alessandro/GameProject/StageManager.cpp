#include "pch.h"
#include "StageManager.h"
#include "Camera.h"
#include "ResourcesLinker.h"
#include "PlatformManager.h"
#include "Cuphead.h"
#include "NonInterractableProp.h"
#include "Projectile.h"

std::list<Projectile*> StageManager::sm_pProjectiles{};

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
}

void StageManager::UpdateProjectiles( float elapsedSec )
{
	for ( Projectile* pProjectile : sm_pProjectiles )
	{
		pProjectile->Update( elapsedSec );
	}
}

void StageManager::CheckCollisions( )
{
	m_PlatformManager.CheckCollision( m_pPlayer );

	// https://stackoverflow.com/questions/16269696/erasing-while-iterating-an-stdlist
	for ( std::list<Projectile*>::iterator i = sm_pProjectiles.begin( ); i != sm_pProjectiles.end( );)
	{
		if ( (*i)->GetIsOutOfBound( ) )
		{
			i = sm_pProjectiles.erase( i );
		}
		else
		{
			++i;
		}
	}
}

void StageManager::KeyPressEvent( const SDL_KeyboardEvent& e )
{
	m_pPlayer->KeyPressEvent( e );
}

Cuphead const* StageManager::GetPlayer( ) const
{
	return m_pPlayer;
}

const std::list<Projectile*>& StageManager::GetProjectiles( ) const
{
	return sm_pProjectiles;
}

const std::vector<NonInterractableProp>& StageManager::GetBackgroundProps( ) const
{
	return m_BackgroundProps;
}

const std::vector<NonInterractableProp>& StageManager::GetFrontgroundProps( ) const
{
	return m_FrontgroundProps;
}

void StageManager::PushProjectile( Projectile* pProjectile )
{
	sm_pProjectiles.push_back( pProjectile );
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
