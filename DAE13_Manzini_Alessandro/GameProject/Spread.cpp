#include "pch.h"
#include "Spread.h"
#include "Constants.h"
#include "ResourcesLinker.h"
#include "Sprite.h"
#include "Projectile.h"

Spread::Spread( )
	:	Weapon(
			ProjectileSettings
			{
				Constants::sk_SpreadCount,
				1,
				Constants::sk_SpreadDamage,
				Constants::sk_ProjectileSpeed,
				Constants::sk_SpreadRange,
				CollisionCircle{ 130.f, 0.f, 10.f }
			},
			ProjectileSettings
			{
				Constants::sk_SpreadExCount,
				Constants::sk_SpreadExHP,
				Constants::sk_SpreadExDamage,
				Constants::sk_ProjectileSpeed,
				Constants::sk_SpreadExRange,
				CollisionCircle{ }
			}, 
			Constants::sk_SpreadExProgressPerHit )
{
}

Weapon::WeaponType Spread::GetType( ) const
{
	return Weapon::WeaponType::spread;
}

void Spread::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	/*for ( Projectile* pProjectile : m_pProjectiles )
	{
		Sprite* pSprite{ pResourcesLinker->GetSprite( "spread" ) };
		pProjectile->SetSprite( pSprite );
	}*/
}
