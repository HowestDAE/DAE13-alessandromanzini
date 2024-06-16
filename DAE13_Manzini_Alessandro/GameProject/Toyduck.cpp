#include "pch.h"
#include "Toyduck.h"
#include "SoundManager.h"
#include "Constants.h"
#include "Sprite.h"
#include "utils.h"
#include "iostream"

Toyduck::Toyduck( const Point2f& position, float aggroRadius, float dropRadius, bool updown )
	: Enemy( position, Constants::sk_ToyduckStartingHP, aggroRadius, dropRadius )
	, mk_Updown{ updown }
	, m_CollisionManager{ GenerateCollisionManager( updown ) }
{
	m_Velocity.Set( -Constants::sk_ToyduckSpeed, 0.f );
	SetCollisionManager( &m_CollisionManager );
	InitializeQueues( 2, 1 );
}

void Toyduck::Update( float elapsedSec )
{
	Enemy::Update( elapsedSec );
}

void Toyduck::Kill( )
{
	Enemy::Kill( );

	SoundManager::Stop( "toyduck_idle_loop" );
	SoundManager::Play( "toyduck_death" );

	QueueTexture( 0, TextureInfo{ m_pDeathBacktireSprite, false, mk_Updown }, true );
	QueueTexture( 1, TextureInfo{ m_pDeathSprite, false, mk_Updown }, true );
}

void Toyduck::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	m_pIdleSprite = pResourcesLinker->GetSprite( "toyduck_idle" );
	m_pBacktireSprite = pResourcesLinker->GetSprite( "toyduck_backtire" );

	m_pDeathSprite = pResourcesLinker->GetSprite( "toyduck_death" );
	m_pDeathBacktireSprite = pResourcesLinker->GetSprite( "toyduck_death_backtire" );

	QueueTexture( 0, TextureInfo{ m_pBacktireSprite, false, mk_Updown } );
	QueueTexture( 1, TextureInfo{ m_pIdleSprite, false, mk_Updown } );
}

CollisionManager Toyduck::GenerateCollisionManager( bool updown )
{
	if ( updown )
	{
		return CollisionManager{ std::vector<CollisionCircle>{ CollisionCircle{ 180.f, 0.f, 70.f, CollisionType::noHit }, CollisionCircle{ 130.f, -110.f, 60.f } }, &m_Location };
	}

	return CollisionManager{ std::vector<CollisionCircle>{ CollisionCircle{ 180.f, 140.f, 70.f, CollisionType::noHit }, CollisionCircle{ 130.f, 250.f, 60.f } }, &m_Location };
}

void Toyduck::AggroEvent( )
{
	SoundManager::Play( "toyduck_idle_loop", 20 );
}

void Toyduck::DropEvent( )
{
	SoundManager::Stop( "toyduck_idle_loop" );
}
