#include "pch.h"
#include "Projectile.h"
#include <cmath>
#include "utils.h"

Projectile::Projectile( const Weapon* pWeapon )
	: mk_pWeapon{ pWeapon }
	, m_Location{}
	, m_Radius{}
	, m_Rotation{}
	, m_TravelDistance{}
	, m_Velocity{}
	, m_pSpriteManager{}
	, m_IsActive{}
{
}

Weapon::WeaponType Projectile::GetType( ) const
{
	return mk_pWeapon->GetType();
}

bool Projectile::GetIsOutOfBound( ) const
{
	return m_IsActive;
}

void Projectile::Draw( ) const
{
	if ( m_IsActive )
	{
		glPushMatrix( );
		{
			glTranslatef( m_Location.x, m_Location.y, 0.f );
			glRotatef( m_Rotation, 0.f, 0.f, 1.f );
			//m_pSpriteManager->Draw( Point2f{ m_Radius, 0.f } );
			m_pSpriteManager->Draw( Point2f{ m_Radius, -m_pSpriteManager->GetHeight()/2.f} );
			
			//utils::DrawRect( Point2f{ m_Radius, 0.f }, m_pSpriteManager->GetWidth( ), m_pSpriteManager->GetHeight( ) );
			//utils::DrawLine( Point2f{ 0.f, 0.f }, Point2f{ m_Radius, 0.f } );
		}
		glPopMatrix( );
	}
}

void Projectile::Update( float elapsedSec )
{
	if ( m_IsActive )
	{
		m_Location += m_Velocity * elapsedSec;
		m_TravelDistance += mk_pWeapon->GetProjectileSpeed() * elapsedSec;
		m_pSpriteManager->Update( elapsedSec );

		if ( m_TravelDistance > mk_pWeapon->GetProjectileRange( ) )
		{
			m_IsActive = false;
		}
	}
}

void Projectile::Reset( const Point2f& origin, float radius, float rotation )
{
	m_pSpriteManager->Reset( );

	m_TravelDistance = 0.f;

	m_Location = Vector2f{ origin };

	m_Radius = radius;
	m_Rotation = rotation;
	m_IsActive = true;

	const float radians{ rotation * float(M_PI) / 180.f };
	const float speed{ mk_pWeapon->GetProjectileSpeed( ) };
	m_Velocity.Set( cosf( radians ) * speed, sinf( radians ) * speed );
}
