#include "pch.h"
#include "Projectile.h"
#include <cmath>
#include "utils.h"

Projectile::Projectile( const Weapon* pWeapon, const CollisionCircle& collisionCircle )
	: CollidableEntity( pWeapon->GetProjectileDamage() )
	, mk_pWeapon{ pWeapon }
	, m_CollisionManager{ collisionCircle, &m_CollisionLocation }
	, m_Location{}
	, m_CollisionLocation{}
	, m_Radius{}
	, m_Rotation{}
	, m_TravelDistance{}
	, m_Velocity{}
	, m_pSprite{}
	, m_IsActive{}
{
	SetCollisionManager( &m_CollisionManager );
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
			m_pSprite->Draw( Point2f{ m_Radius, -m_pSprite->GetHeight()/2.f } );
			
			//utils::DrawRect( Point2f{ m_Radius, 0.f }, m_pSpriteManager->GetWidth( ), m_pSpriteManager->GetHeight( ) );
			//utils::DrawLine( Point2f{ 0.f, 0.f }, Point2f{ m_Radius, 0.f } );
		}
		glPopMatrix( );
		DrawCollision( );
	}
}

void Projectile::Update( float elapsedSec )
{
	if ( m_IsActive )
	{
		m_Location += m_Velocity * elapsedSec;
		m_CollisionLocation += m_Velocity * elapsedSec;
		m_TravelDistance += mk_pWeapon->GetProjectileSpeed() * elapsedSec;
		m_pSprite->Update( elapsedSec );

		if ( m_TravelDistance > mk_pWeapon->GetProjectileRange( ) )
		{
			m_IsActive = false;
		}
	}
}

void Projectile::Hit( int damage )
{
	m_IsActive = false;
}

void Projectile::Reset( const Point2f& origin, float radius, float rotation )
{
	m_pSprite->Reset( );

	m_TravelDistance = 0.f;

	m_Radius = radius;
	m_Rotation = rotation;
	m_IsActive = true;

	const float radians{ rotation * float(M_PI) / 180.f };
	const float speed{ mk_pWeapon->GetProjectileSpeed( ) };
	const Vector2f directionVector{ cosf( radians ), sinf( radians ) };
	m_Velocity = directionVector * speed;

	// the collision location is offsetted so the collision circle is placed is the right spot
	const Vector2f matchDisplacement{ m_CollisionManager.GetCollisionCircles( ).front( ).circle.center };
	m_Location = Vector2f{ origin };
	m_CollisionLocation.Set(
		m_Location.x + matchDisplacement.x * ( directionVector.x - 1 ),
		m_Location.y + matchDisplacement.x * directionVector.y 
	);
}

void Projectile::SetSprite( Sprite* pSprite )
{
	m_pSprite = pSprite;
}
