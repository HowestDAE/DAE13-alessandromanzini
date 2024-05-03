#include "pch.h"
#include "Weapon.h"
#include "ResourcesLinker.h"
#include "Projectile.h"

Weapon::Weapon( int initialProjectilesCount, int projectileDamage, float projectileSpeed, float projectileRange, const CollisionCircle& bulletCollisionCircle, const CollisionCircle& exCollisionCircle )
	: mk_InitialProjectilesCount{ initialProjectilesCount }
	, mk_ProjectileDamage{ projectileDamage }
	, mk_ProjectileSpeed{ projectileSpeed }
	, mk_ProjectileRange{ projectileRange }
	, m_pProjectiles{ static_cast<const unsigned int>(initialProjectilesCount) }
	, m_CurrentProjectileIndex{}
{
	for ( int index{}; index < mk_InitialProjectilesCount; ++index )
	{
		m_pProjectiles[index] = new Projectile( this, bulletCollisionCircle );
	}
}

Weapon::~Weapon( )
{
	for ( Projectile* pProjectile : m_pProjectiles )
	{
		delete pProjectile;
		pProjectile = nullptr;
	}
}

int Weapon::GetProjectileDamage( ) const
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

void Weapon::SpawnProjectile( const Point2f& origin, float radius, float rotation )
{
	Projectile* currentProjectile = m_pProjectiles.at( m_CurrentProjectileIndex );
	currentProjectile->Reset( origin, radius, rotation );

	m_CurrentProjectileIndex = (m_CurrentProjectileIndex + 1) % m_pProjectiles.size( );
}

void Weapon::CheckCollision( CollidableEntity& other )
{
	for ( Projectile* pProjectile : m_pProjectiles )
	{
		pProjectile->CheckCollision( other );
	}
}

void Weapon::Draw( ) const
{
	for ( Projectile* pProjectile : m_pProjectiles )
	{
		pProjectile->Draw( );
	}
}

void Weapon::Update( float elapsedSec )
{
	for ( Projectile* pProjectile : m_pProjectiles )
	{
		pProjectile->Update( elapsedSec );
	}
}
