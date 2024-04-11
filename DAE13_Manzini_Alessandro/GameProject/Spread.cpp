#include "pch.h"
#include "Spread.h"
#include "Constants.h"

Spread::Spread( )
	: Weapon( Constants::sk_SpreadCount, Constants::sk_SpreadDamage, Constants::sk_ProjectileSpeed, Constants::sk_SpreadRange )
{
}

Weapon::WeaponType Spread::GetType( ) const
{
	return Weapon::WeaponType::spread;
}
