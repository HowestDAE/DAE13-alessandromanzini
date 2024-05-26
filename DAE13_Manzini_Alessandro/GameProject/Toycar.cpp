#include "pch.h"
#include "Toycar.h"
#include "Constants.h"
#include "Sprite.h"

Toycar::Toycar( const Point2f& position, float aggroRadius, float dropRadius, unsigned int variation, bool updown )
	: Enemy( position, Constants::sk_ToycarStartingHP, aggroRadius, dropRadius )
	, mk_Variation{ variation % smk_VariationsCount }
	, mk_Updown{ updown }
	, m_CollisionManager{ std::vector<CollisionCircle>{ CollisionCircle{ 60.f, 90.f, 65.f, CollisionType::noHit }, CollisionCircle{ 230.f, 90.f, 65.f, CollisionType::noHit  } }, &m_CollisionLocation }
	, m_CollisionLocation{ m_Location }
{
	m_Velocity.Set( -Constants::sk_ToycarSpeed, 0.f );
	SetCollisionManager( &m_CollisionManager );
	InitializeQueues( 1, 1 );

	if ( mk_Updown )
	{
		const float yOffset{ 50.f };
		m_Location.y += yOffset;
	}
}

void Toycar::UpdateLocation( float elapsedSec )
{
	Enemy::UpdateLocation( elapsedSec );
	m_CollisionLocation += m_Velocity * elapsedSec;
}

void Toycar::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	switch ( mk_Variation )
	{
	case 0:
		m_pIdleSprite = pResourcesLinker->GetSprite( "toycar_idle_a" );
		break;
	case 1:
		m_pIdleSprite = pResourcesLinker->GetSprite( "toycar_idle_b" );
		break;
	case 2:
		m_pIdleSprite = pResourcesLinker->GetSprite( "toycar_idle_c" );
		break;
	case 3:
		m_pIdleSprite = pResourcesLinker->GetSprite( "toycar_idle_d" );
		break;
	}

	QueueTexture( 0, m_pIdleSprite, false, mk_Updown );
}
