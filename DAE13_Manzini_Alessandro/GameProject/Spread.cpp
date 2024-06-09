#include "pch.h"
#include "Spread.h"
#include "Constants.h"
#include "ResourcesLinker.h"
#include "Sprite.h"
#include "Projectile.h"

Spread::Spread( )
	: Weapon(
		ProjectileSettings
		{
			Constants::sk_SpreadCount,
			1,
			Constants::sk_SpreadDamage,
			Constants::sk_ProjectileSpeed,
			Constants::sk_SpreadRange,
			CollisionCircle{ 70.f, 0.f, 10.f },
			"spread",
			"spread_death",
			"spread_spawn_loop",
			"projectile_hit"
		},
		ProjectileSettings
		{
			Constants::sk_SpreadExCount,
			Constants::sk_SpreadExHP,
			Constants::sk_SpreadExDamage,
			Constants::sk_ProjectileSpeed / 2.f,
			Constants::sk_SpreadExRange,
			CollisionCircle{ 100.f, 0.f, 20.f },
			"spread_ex",
			"spread_death",
			"peashooter_ex_spawn",
			"peashooter_ex_hit"
		}, 
		Constants::sk_SpreadExProgressPerHit )
{
}

void Spread::SpawnProjectile( const Point2f& origin, float radius, float rotation )
{
	const float spreadAngle{ 10.f };

	Weapon::SpawnProjectile( origin, radius, rotation - spreadAngle*2 );
	Weapon::SpawnProjectile( origin, radius, rotation - spreadAngle*3/4 );
	Weapon::SpawnProjectile( origin, radius, rotation + spreadAngle*3/4 );
	Weapon::SpawnProjectile( origin, radius, rotation + spreadAngle*2 );
}

void Spread::SpawnEx( const Point2f& origin, float radius, float rotation )
{
	for( int i{ 0 }; i < 8; ++i )
	{
		Weapon::SpawnEx( origin, radius, float( 45 * i ));
	}
}

Weapon::WeaponType Spread::GetType( ) const
{
	return Weapon::WeaponType::spread;
}
