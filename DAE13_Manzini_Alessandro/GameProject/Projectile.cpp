#include "pch.h"
#include "Projectile.h"
#include <cmath>

Projectile::Projectile( const Weapon* pWeapon )
	: mk_pWeapon{ pWeapon }
{
	Reset( Point2f{}, 0.f );
}

Weapon::WeaponType Projectile::GetType( ) const
{
	return mk_pWeapon->GetType();
}

bool Projectile::GetIsOutOfBound( ) const
{
	return m_TravelDistance > mk_pWeapon->GetProjectileRange();
}

void Projectile::Draw( ) const
{
	// todo: apply rotation
	m_pSpriteManager->Draw( m_Location.ToPoint2f() );
}

void Projectile::Update( float elapsedSec )
{
	m_Location += m_Velocity * elapsedSec;
	m_TravelDistance += mk_pWeapon->GetProjectileSpeed() * elapsedSec;
}

void Projectile::Reset( const Point2f& pos, float rotation )
{
	m_TravelDistance = 0.f;
	m_Location.Set( pos.x, pos.y );
	m_Rotation = rotation;

	const float radians{ rotation * float(M_PI) / 180.f };
	const float speed{ mk_pWeapon->GetProjectileSpeed( ) };
	m_Velocity.Set( cosf( radians ) * speed, sinf( radians ) * speed );
}
