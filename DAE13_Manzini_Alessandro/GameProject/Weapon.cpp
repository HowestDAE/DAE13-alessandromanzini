#include "pch.h"
#include "Weapon.h"
#include "Projectile.h"

Weapon::Weapon( int initialProjectilesCount, float projectileDamage, float projectileSpeed, float projectileRange )
	: mk_InitialProjectilesCount{ initialProjectilesCount }
	, mk_ProjectileDamage{ projectileDamage }
	, mk_ProjectileSpeed{ projectileSpeed }
	, mk_ProjectileRange{ projectileRange }
	, m_pProjectiles{ static_cast<const unsigned int>(initialProjectilesCount) }
	, m_CurrentProjectileIndex{}
{
	for ( int index{}; index < mk_InitialProjectilesCount; ++index )
	{
		m_pProjectiles[index] = new Projectile( this );
	}
}

Projectile* Weapon::GetProjectile( const Point2f& pos, float rotation )
{
	Projectile* currentProjectile = m_pProjectiles.at( m_CurrentProjectileIndex );
	currentProjectile->Reset( pos, rotation );

	m_CurrentProjectileIndex = (m_CurrentProjectileIndex + 1) % m_pProjectiles.size( );

	return currentProjectile;
}

float Weapon::GetProjectileDamage( ) const
{
	return mk_ProjectileDamage;
}

float Weapon::GetProjectileSpeed( ) const
{
	return mk_ProjectileSpeed;
}

float Weapon::GetProjectileRange( ) const
{
	return mk_ProjectileRange;
}

std::vector<Projectile*>& Weapon::GetProjectiles( )
{
	return m_pProjectiles;
}
