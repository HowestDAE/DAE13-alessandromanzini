#include "pch.h"
#include "Tongue.h"
#include "Sprite.h"
#include "Constants.h"

const float Tongue::smk_TongueDuration{ 3.f };

Tongue::Tongue( const Point2f& position, float aggroRadius, float dropRadius, bool upsideDown )
	: Enemy( position, 1 , aggroRadius, dropRadius )
	, mk_UpsideDown{ upsideDown }
	, m_CollisionLocation{ position }
	, m_TongueElapsedTime{}
	, m_CycleCompleted{}
	, m_CollisionVelocity{}
	, m_CollisionManager{}
{
	SetCollisionManager( &m_CollisionManager );

	InitializeQueues( 1 );
}

void Tongue::Update( float elapsedSec )
{
	Enemy::Update( elapsedSec );

	m_CollisionLocation += elapsedSec * m_CollisionVelocity;
	m_TongueElapsedTime += elapsedSec;

	if ( IsQueueReady( 0 ) )
	{
		m_CollisionVelocity.Set( 0.f, 0.f );
	}

	if ( !m_CycleCompleted && m_TongueElapsedTime >= smk_TongueDuration )
	{
		QueueTexture( 0, TextureInfo{ m_pOutroSprite, false, mk_UpsideDown } );
		m_TongueElapsedTime = 0.f;
		m_CycleCompleted = true;
		m_CollisionVelocity.Set( Constants::sk_TongueOutroSpeed, 0.f );
	}
}

void Tongue::Reset( const Point2f& position )
{
	Reset( );
}

void Tongue::Reset( )
{
	QueueTexture( 0, TextureInfo{ m_pIntroSprite, false, mk_UpsideDown }, true );
	QueueTexture( 0, m_pLoopSprite );
	m_TongueElapsedTime = 0.f;
	m_CycleCompleted = false;
	m_CollisionLocation.x = m_Location.x + m_pIntroSprite->GetWidth( );
	m_CollisionVelocity.Set( -Constants::sk_TongueIntroSpeed, 0.f );
}

void Tongue::Kill( )
{
	Enemy::Kill( );
	m_TongueElapsedTime = smk_TongueDuration;
}

bool Tongue::GetIFrameState( ) const
{
	return !GetIsAlive();
}

void Tongue::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	m_pIntroSprite = pResourcesLinker->GetSprite( "tongue_intro" );
	m_pLoopSprite = pResourcesLinker->GetSprite( "tongue_loop" );
	m_pOutroSprite = pResourcesLinker->GetSprite( "tongue_outro" );

	const int circlesCount{ 11 };
	const float circleRadius{ 40.f };
	std::vector<CollisionCircle> collisionCircles{ size_t( circlesCount ) };
	for ( int i{}; i < circlesCount; ++i )
	{
		collisionCircles.push_back( CollisionCircle{ 20.f + circleRadius * i * 2, 80.f, circleRadius, CollisionType::noHit } );
	}
	m_CollisionManager = CollisionManager( collisionCircles, &m_CollisionLocation );

	m_CollisionLocation.x = m_Location.x + m_pIntroSprite->GetWidth( );
}
