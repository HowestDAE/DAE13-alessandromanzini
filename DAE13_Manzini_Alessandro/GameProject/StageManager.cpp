#include "pch.h"
#include "StageManager.h"
#include "Camera.h"
#include "ResourcesLinker.h"
#include "PlatformManager.h"
#include "Cuphead.h"
#include "NonInterractableProp.h"

StageManager::StageManager( Camera* pCamera, ResourcesLinker* pResourcesLinker )
	: m_pCamera{ pCamera }
	, m_pResourcesLinker{ pResourcesLinker }
	, m_IsHalted{ true }
	, m_IsCameraFixed{ false }

	, m_BackgroundProps{}
	, m_FrontgroundProps{}
{
	m_pPlatformManager = new PlatformManager( );

	Initialize( );
}

StageManager::~StageManager( )
{
	delete m_pPlatformManager;
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

	m_pPlayer->Update( elapsedSec );
	if ( !m_IsCameraFixed )
	{
		m_pCamera->Aim( m_pPlayer->GetPosition( ), m_pPlayer->GetTextureWidth( ) );
	}
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

void StageManager::KeyPressEvent( const SDL_KeyboardEvent& e )
{
	m_pPlayer->KeyPressEvent( e );
}

Cuphead const* StageManager::GetPlayer( ) const
{
	return m_pPlayer;
}

const std::vector<NonInterractableProp>& StageManager::GetBackgroundProps( ) const
{
	return m_BackgroundProps;
}

const std::vector<NonInterractableProp>& StageManager::GetFrontgroundProps( ) const
{
	return m_FrontgroundProps;
}

void StageManager::LockCamera(const Point2f& centerPoint )
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
