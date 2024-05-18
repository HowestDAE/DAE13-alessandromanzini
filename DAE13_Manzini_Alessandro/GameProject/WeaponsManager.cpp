#include "pch.h"
#include "WeaponsManager.h"
#include "Constants.h"
#include "StageManager.h"
#include "Peashooter.h"
#include "Spread.h"

const float WeaponsManager::smk_ShotDelay{ .15f };
const float WeaponsManager::smk_ExIntermediateDelay{ .3f };
const float WeaponsManager::smk_ExDelay{ .7f };

WeaponsManager::WeaponsManager( )
	: m_pWeapons{ new Peashooter(), new Spread() }
	, m_EquippedWeaponIndex{}
	, m_ShotAccumulatedTime{}
	, m_ExAccumulatedTime{ smk_ExDelay }
	, m_ExNeedsQueue{}
	, m_ExMoves{}
	, m_ExProgress{}
{
}

WeaponsManager::~WeaponsManager( )
{
	for ( int index{}; index < smk_WeaponsCount; ++index )
	{
		delete m_pWeapons[index];
	}
}

void WeaponsManager::SwapWeapons( )
{
	m_EquippedWeaponIndex = (m_EquippedWeaponIndex + 1) % smk_WeaponsCount;
}

void WeaponsManager::Shoot( const Point2f& origin, float radius, float rotation )
{
	if ( m_ShotAccumulatedTime >= smk_ShotDelay )
	{
		m_ShotAccumulatedTime = 0.f;

		m_pWeapons[m_EquippedWeaponIndex]->SpawnProjectile( origin, radius, rotation );
	}
}

void WeaponsManager::ShootEX( const Point2f& origin, float radius, float rotation )
{
	if ( m_ExAccumulatedTime >= smk_ExDelay && m_ExMoves > 0 )
	{
		m_ExAccumulatedTime = 0.f;
		--m_ExMoves;
		m_ExNeedsQueue = true;

		m_pWeapons[m_EquippedWeaponIndex]->SpawnEx( origin, radius, rotation );
	}
}

void WeaponsManager::CheckCollision( CollidableEntity& other )
{
	for ( int index{}; index < smk_WeaponsCount; ++index )
	{
		m_ExProgress += m_pWeapons[index]->CheckCollision( other );
	}
}

void WeaponsManager::Draw( ) const
{
	for ( int index{}; index < smk_WeaponsCount; ++index )
	{
		m_pWeapons[index]->Draw();
	}
}

void WeaponsManager::Update( float elapsedSec )
{
	m_ShotAccumulatedTime += elapsedSec;
	m_ExAccumulatedTime += elapsedSec;

	for ( int index{}; index < smk_WeaponsCount; ++index )
	{
		m_pWeapons[index]->Update( elapsedSec );
	}

	UpdateEx( elapsedSec );
}

void WeaponsManager::UpdateEx( float elapsedSec )
{
	if ( m_ExMoves >= Constants::sk_ExMovesLimit )
	{
		m_ExProgress = 0.f;
	}

	const float maxProgress{ 1.f };
	if ( m_ExProgress > maxProgress )
	{
		++m_ExMoves;
		m_ExProgress -= maxProgress;
	}
}

void WeaponsManager::UpdateHUDManager( HUDManager* pHUDManager ) const
{
	pHUDManager->SetEx( m_ExMoves, m_ExProgress );
}

bool WeaponsManager::RequireExMoveQueue( )
{
	bool temp{ m_ExNeedsQueue };
	m_ExNeedsQueue = false;
	return temp;
}

bool WeaponsManager::GetIsExMoveOngoing( ) const
{
	return m_ExAccumulatedTime < smk_ExIntermediateDelay;
}

void WeaponsManager::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	for ( int index{}; index < smk_WeaponsCount; ++index )
	{
		m_pWeapons[index]->LinkTexture( pResourcesLinker );
	}
}
