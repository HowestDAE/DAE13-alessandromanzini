#include "pch.h"
#include "WeaponsManager.h"
#include "StageManager.h"
#include "Peashooter.h"
#include "Spread.h"

const float WeaponsManager::smk_ShotDelay{ .15f };

WeaponsManager::WeaponsManager( )
	: m_pWeapons{ new Peashooter(), new Spread() }
	, m_EquippedWeaponIndex{}
	, m_ShotAccumulatedTime{}
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
	if ( m_ShotAccumulatedTime > smk_ShotDelay )
	{
		m_ShotAccumulatedTime = 0.f;

		m_pWeapons[m_EquippedWeaponIndex]->SpawnProjectile( origin, radius, rotation );
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

	for ( int index{}; index < smk_WeaponsCount; ++index )
	{
		m_pWeapons[index]->Update( elapsedSec );
	}
}

void WeaponsManager::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	for ( int index{}; index < smk_WeaponsCount; ++index )
	{
		m_pWeapons[index]->LinkTexture( pResourcesLinker );
	}
}
