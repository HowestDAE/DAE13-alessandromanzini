#include "pch.h"
#include "Toyduck.h"
#include "Constants.h"
#include "Sprite.h"
#include "utils.h"

Toyduck::Toyduck( const Point2f& position )
	: Entity( position, Constants::sk_ToyduckStartingHP )
	, m_pIdleSprite{}
	, m_pBacktireSprite{}
	, m_CollisionManager{ std::vector<CollisionCircle>{ CollisionCircle{ 180.f, 130.f, 70.f, CollisionType::noHit }, CollisionCircle{ 130.f, 250.f, 60.f } }, &m_Location}
{
	m_Velocity.Set( -Constants::sk_ToyduckSpeed, 0.f );
	SetCollisionManager( &m_CollisionManager );
	InitializeQueues( 2, 1 );
}

void Toyduck::Update( float elapsedSec )
{
	Entity::Update( elapsedSec );
	UpdateLocation( elapsedSec );
}

void Toyduck::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	m_pIdleSprite = pResourcesLinker->GetSprite( "toyduck_idle" );
	m_pBacktireSprite = pResourcesLinker->GetSprite( "toyduck_backtire" );

	QueueTexture( 0, m_pBacktireSprite );
	QueueTexture( 1, m_pIdleSprite );
}
