#include "pch.h"
#include "Peashooter.h"
#include "Constants.h"

Peashooter::Peashooter( )
	: Weapon( Constants::sk_PeashooterCount, Constants::sk_PeashooterDamage, Constants::sk_ProjectileSpeed, Constants::sk_PeashooterRange )
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
