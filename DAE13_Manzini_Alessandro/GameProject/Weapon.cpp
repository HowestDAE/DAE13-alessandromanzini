#include "pch.h"
#include "Weapon.h"
#include "ResourcesLinker.h"
#include "Projectile.h"

Weapon::Weapon( const ProjectileSettings& projectileSettings, const ProjectileSettings& exMoveSettings, float exProgressPerHit )
	: mk_ProjectileSettings{ projectileSettings }
	, mk_ExMoveSettings{ exMoveSettings }
	, mk_ExProgressPerHit{ exProgressPerHit }

	, m_pProjectiles{ static_cast<const unsigned int>(projectileSettings.initialCount) }
	, m_pExMoves{ static_cast<const unsigned int>(exMoveSettings.initialCount) }
	, m_CurrentProjectileIndex{}
	, m_CurrentExMoveIndex{}
{
	for ( int index{}; index < mk_ProjectileSettings.initialCount; ++index )
	{
		m_pProjectiles[index] = new Projectile( &mk_ProjectileSettings );
	}

	for ( int index{}; index < mk_ExMoveSettings.initialCount; ++index )
	{
		m_pExMoves[index] = new Projectile( &mk_ExMoveSettings );
	}
}

Weapon::~Weapon( )
{
	for ( Projectile* pProjectile : m_pProjectiles )
	{
		delete pProjectile;
		pProjectile = nullptr;
	}

	for ( Projectile* pExMove : m_pExMoves )
	{
		delete pExMove;
		pExMove = nullptr;
	}
}

Weapon::Weapon( Weapon&& other ) noexcept
	: mk_ProjectileSettings{ other.mk_ProjectileSettings }
	, mk_ExMoveSettings{ other.mk_ExMoveSettings }
	, mk_ExProgressPerHit{ other.mk_ExProgressPerHit }

	, m_pProjectiles{ std::move( other.m_pProjectiles ) }
	, m_pExMoves{ std::move( other.m_pExMoves ) }
	, m_CurrentProjectileIndex{ other.m_CurrentProjectileIndex }
	, m_CurrentExMoveIndex{ other.m_CurrentExMoveIndex }
{
}

void Weapon::SpawnProjectile( const Point2f& origin, float radius, float rotation )
{
	// Picks next available projectile
	Projectile* currentProjectile = m_pProjectiles.at( m_CurrentProjectileIndex );
	currentProjectile->Reset( origin, radius, rotation );

	// Next available projectile is set with "modulo number of projectiles"
	m_CurrentProjectileIndex = (m_CurrentProjectileIndex + 1) % m_pProjectiles.size( );
}

void Weapon::SpawnEx( const Point2f& origin, float radius, float rotation )
{
	// Picks next available projectile
	Projectile* currentMoves = m_pExMoves.at( m_CurrentExMoveIndex );
	currentMoves->Reset( origin, radius, rotation );

	// Next available projectile is set with "modulo number of projectiles"
	m_CurrentExMoveIndex = (m_CurrentExMoveIndex + 1) % m_pExMoves.size( );
}

float Weapon::CheckCollision( CollidableEntity& other )
{
	float progress{};
	for ( Projectile* pProjectile : m_pProjectiles )
	{
		if ( pProjectile->CheckCollision( other ) )
		{
			progress += mk_ExProgressPerHit;
		}
	}

	for ( Projectile* pExMove : m_pExMoves )
	{
		pExMove->CheckCollision( other );
	}

	return progress;
}

void Weapon::Draw( ) const
{
	for ( const Projectile* pProjectile : m_pProjectiles )
	{
		pProjectile->Draw( );
	}

	for ( const Projectile* pExMove : m_pExMoves )
	{
		pExMove->Draw( );
	}
}

void Weapon::Update( float elapsedSec )
{
	for ( Projectile* pProjectile : m_pProjectiles )
	{
		pProjectile->Update( elapsedSec );
	}

	for ( Projectile* pExMove : m_pExMoves )
	{
		pExMove->Update( elapsedSec );
	}
}

const std::string& Weapon::GetAudioUid( ) const
{
	return mk_ProjectileSettings.spawnAudioUid;
}

const std::string& Weapon::GetExAudioUid( ) const
{
	return mk_ExMoveSettings.spawnAudioUid;
}

void Weapon::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	for ( Projectile* pProjectile : m_pProjectiles )
	{
		pProjectile->LinkTexture( pResourcesLinker );
	}

	for ( Projectile* pExMove : m_pExMoves )
	{
		pExMove->LinkTexture( pResourcesLinker );
	}
}
