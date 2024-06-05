#include "pch.h"
#include "Projectile.h"
#include "SoundManager.h"
#include <cmath>
#include "utils.h"
#include "iostream"

Projectile::Projectile( const ProjectileSettings* pSettings )
	: Entity( Point2f{}, pSettings->hp, pSettings->damage )
	, mk_pProjectileSettings{ pSettings }
	, m_pLoopSprite{}
	, m_pDeathSprite{}
	, m_CollisionManager{ pSettings->collisionCircle, &m_CollisionLocation }
	, m_CollisionLocation{}
	, m_Radius{}
	, m_Rotation{}
	, m_TravelDistance{}
{
	InitializeQueues( 1 );
	SetCollisionManager( &m_CollisionManager );
	Kill( );
}

void Projectile::Draw( ) const
{
	if ( GetIsAlive() || !IsQueueReady( 0 ) )
	{
		glPushMatrix( );
		{
			glTranslatef( m_Location.x, m_Location.y, 0.f );
			glRotatef( m_Rotation, 0.f, 0.f, 1.f );
			glTranslatef( - m_Location.x + m_Radius, - m_Location.y - m_pLoopSprite->GetHeight()/2.f, 0.f );
			//glTranslatef( m_Radius - m_Location.x, -GetTextureWidth() / 2.f - m_Location.y, 0.f );
		
			Entity::Draw( );
		}
		glPopMatrix( );
	}
}

void Projectile::Update( float elapsedSec )
{
	Entity::Update( elapsedSec );

	if ( GetIsAlive( ) )
	{	
		const Vector2f displacement{ m_Velocity * elapsedSec };
		m_Location += displacement;
		m_CollisionLocation += displacement;
		m_TravelDistance += mk_pProjectileSettings->speed * elapsedSec;

		if ( m_TravelDistance > mk_pProjectileSettings->range )
		{
			Kill( );
		}
	}
}

bool Projectile::CheckCollision( CollidableEntity& other )
{
	if ( GetIsAlive( ) && CollidableEntity::CheckCollision( other ) )
	{
		SoundManager::Play( mk_pProjectileSettings->hitAudioUid );
		return true;
	}
	return false;
}

void Projectile::Reset( const Point2f& origin, float radius, float rotation )
{
	m_pLoopSprite->Reset( );
	QueueTexture( 0, TextureInfo{ m_pLoopSprite }, true );

	Revive( mk_pProjectileSettings->hp );

	m_Radius = radius;
	m_Rotation = rotation;
	m_TravelDistance = 0.f;

	const float radians{ rotation * float(M_PI) / 180.f };
	const float speed{ mk_pProjectileSettings->speed };
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

void Projectile::Kill( )
{
	Entity::Kill( );

	if ( m_pDeathSprite )
	{
		QueueTexture( 0, m_pDeathSprite );
	}
}

void Projectile::LinkTexture( ResourcesLinker* pResourceLinker )
{
	m_pLoopSprite = pResourceLinker->GetSprite( mk_pProjectileSettings->loopTextureUid );
	m_pDeathSprite = pResourceLinker->GetSprite( mk_pProjectileSettings->deathTextureUid );

	if ( m_pLoopSprite )
	{
		QueueTexture( 0, m_pLoopSprite );
	}
}
