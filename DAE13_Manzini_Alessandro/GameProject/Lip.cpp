#include "pch.h"
#include "Lip.h"
#include "Constants.h"
#include "Sprite.h"

Lip::Lip( )
	: Entity( Point2f{}, 1 )
	, m_CollisionManager{ CollisionCircle{ 45.f, 50.f, 32.f, CollisionType::noHit }, &m_Location }
{
	SetCollisionManager( &m_CollisionManager );
	InitializeQueues( 1 );
}

void Lip::Update( float elapsedSec )
{
	Entity::Update( elapsedSec );

	m_Location += m_Velocity * elapsedSec * Constants::sk_LipSpeed;
}

void Lip::Reset( const Vector2f& location, const Vector2f& aimDirection )
{
	m_Location = location;
	m_Velocity = aimDirection.Normalized( );
}

void Lip::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	m_pLoopSprite = pResourcesLinker->GetSprite( "lips_loop" );
	QueueTexture( 0, m_pLoopSprite );
}
