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
