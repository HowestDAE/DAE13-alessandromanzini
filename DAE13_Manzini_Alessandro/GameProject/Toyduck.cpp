#include "pch.h"
#include "Toyduck.h"
#include "Constants.h"
#include "Sprite.h"
#include "utils.h"

Toyduck::Toyduck( const Point2f& position, float aggroRadius, float dropRadius )
	: Enemy( position, Constants::sk_ToyduckStartingHP, aggroRadius, dropRadius )
	, m_CollisionManager{ std::vector<CollisionCircle>{ CollisionCircle{ 180.f, 140.f, 70.f, CollisionType::noHit }, CollisionCircle{ 130.f, 250.f, 60.f } }, &m_Location }
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

	QueueTexture( 0, TextureInfo{ m_pDeathBacktireSprite }, true );
	QueueTexture( 1, TextureInfo{ m_pDeathSprite }, true );
}

void Toyduck::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	m_pIdleSprite = pResourcesLinker->GetSprite( "toyduck_idle" );
	m_pBacktireSprite = pResourcesLinker->GetSprite( "toyduck_backtire" );

	m_pDeathSprite = pResourcesLinker->GetSprite( "toyduck_death" );
	m_pDeathBacktireSprite = pResourcesLinker->GetSprite( "toyduck_death_backtire" );
	m_pDeathSprite->SetNoRepeat( true );
	m_pDeathBacktireSprite->SetNoRepeat( true );

	QueueTexture( 0, m_pBacktireSprite );
	QueueTexture( 1, m_pIdleSprite );
}
