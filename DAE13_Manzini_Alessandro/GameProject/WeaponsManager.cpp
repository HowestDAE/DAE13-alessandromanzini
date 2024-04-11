#include "pch.h"
#include "WeaponsManager.h"
#include "StageManager.h"
#include "Peashooter.h"
#include "Spread.h"
#include "utils.h"

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

void WeaponsManager::Shoot( const Point2f& pos, float rotation )
{
	if ( m_ShotAccumulatedTime > smk_ShotDelay )
	{
		m_ShotAccumulatedTime -= smk_ShotDelay;

		Projectile* pProjectile{ m_pWeapons[m_EquippedWeaponIndex]->GetProjectile( pos, rotation ) };
		StageManager::PushProjectile( pProjectile );
	}
}

void WeaponsManager::Update( float elapsedSec )
{
	m_ShotAccumulatedTime += elapsedSec;
}
