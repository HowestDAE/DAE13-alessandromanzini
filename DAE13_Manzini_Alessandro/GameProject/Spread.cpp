#include "pch.h"
#include "Spread.h"
#include "Constants.h"
#include "ResourcesLinker.h"
#include "Sprite.h"
#include "Projectile.h"

Spread::Spread( )
	: Weapon( Constants::sk_SpreadCount, 
		Constants::sk_SpreadDamage, 
		Constants::sk_ProjectileSpeed, 
		Constants::sk_SpreadRange,
		CollisionCircle{},
		CollisionCircle{} )
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
