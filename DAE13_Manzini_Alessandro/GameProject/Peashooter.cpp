#include "pch.h"
#include "Peashooter.h"
#include "Constants.h"
#include "ResourcesLinker.h"
#include "Sprite.h"
#include "Projectile.h"

Peashooter::Peashooter( )
	: Weapon( Constants::sk_PeashooterCount, 
		Constants::sk_PeashooterDamage, 
		Constants::sk_ProjectileSpeed, 
		Constants::sk_PeashooterRange, 
		Constants::sk_PeashooterCollisionCircle, 
		Constants::sk_PeashooterExCollisionCircle )
	, m_IsAlternatedShot{}
{
}

Weapon::WeaponType Peashooter::GetType( ) const
{
	return Weapon::WeaponType::peashooter;
}

void Peashooter::SpawnProjectile( const Point2f& origin, float radius, float rotation )
{
	if (m_IsAlternatedShot )
	{
		Weapon::SpawnProjectile( origin + Vector2f{ 0.f, -15.f }, radius, rotation );
	}
	else
	{
		Weapon::SpawnProjectile( origin, radius, rotation );
	}

	m_IsAlternatedShot = !m_IsAlternatedShot;
}

void Peashooter::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	for ( Projectile* pProjectile : m_pProjectiles )
	{
		Sprite* pSprite{ pResourcesLinker->GetSprite( "peashooter" ) };
		pProjectile->SetSprite( pSprite );
	}
}
