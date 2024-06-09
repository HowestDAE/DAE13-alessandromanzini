#include "pch.h"
#include "Toycar.h"
#include "Constants.h"
#include "Sprite.h"
#include "SoundManager.h"

Toycar::Toycar( const Point2f& position, float aggroRadius, float dropRadius, unsigned int count, bool updown )
	: Enemy( position, 1, aggroRadius, dropRadius )
	, mk_Count{ count }
	, mk_Updown{ updown }
	, m_HasAggroed{ false }
	, m_pIdleSprites{ mk_Count }
	, m_CollisionLocation{ m_Location }
{
	m_Velocity.Set( -Constants::sk_ToycarSpeed, 0.f );
	SetCollisionManager( &m_CollisionManager );
	InitializeQueues( mk_Count, mk_Count );

	if ( mk_Updown )
	{
		const float yOffset{ 50.f };
		m_Location.y += yOffset;
	}
}

void Toycar::DrawBackside( ) const
{
	glPushMatrix( );
	for ( unsigned int i{}; i < mk_Count; ++i )
	{
		Entity::Draw( i );
		glTranslatef( m_pIdleSprites.at( 0 )->GetWidth( ), 0.f, 0.f );
	}
	glPopMatrix( );
}

void Toycar::UpdateLocation( float elapsedSec )
{
	Enemy::UpdateLocation( elapsedSec );
	m_CollisionLocation += m_Velocity * elapsedSec;
}

void Toycar::Reset( const Point2f& position )
{
	m_Location = m_CollisionLocation = Vector2f{ position };
	m_HasAggroed = false;
}

void Toycar::Reset( )
{
	m_Location = m_CollisionLocation = Vector2f{ mk_StartLocation };
	m_HasAggroed = false;
}

void Toycar::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	// Every card has 2 circles (count*2)
	std::vector<CollisionCircle> collisionCircles{ mk_Count * 2 };
	collisionCircles.clear( );

	for ( unsigned int i{}; i < mk_Count; ++i )
	{
		const std::string uid{ std::string( "toycar_idle_" ) + char( 'a' + (i % smk_VariationsCount) ) };
		m_pIdleSprites[i] = pResourcesLinker->GetSprite( uid );
		QueueTexture( i, m_pIdleSprites[i], false, mk_Updown );

		collisionCircles.push_back( CollisionCircle{ 60.f + i * m_pIdleSprites[i]->GetWidth( ), 90.f, 65.f, CollisionType::noHit} );
		collisionCircles.push_back( CollisionCircle{ 230.f + i * m_pIdleSprites[i]->GetWidth( ), 90.f, 65.f, CollisionType::noHit } );
	}	
	m_CollisionManager = CollisionManager( std::move( collisionCircles ), &m_CollisionLocation );
	
}

void Toycar::AggroEvent( )
{
	if ( !m_HasAggroed )
	{
		SoundManager::Play( "toycar_honk" );
		SoundManager::Play( "toycar_idle", 20 );
		m_HasAggroed = true;	
	}
}

void Toycar::DropEvent( )
{
	SoundManager::Stop( "toycar_idle" );
}
