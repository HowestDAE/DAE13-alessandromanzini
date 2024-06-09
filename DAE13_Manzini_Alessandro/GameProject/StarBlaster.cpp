#include "pch.h"
#include "StarBlaster.h"
#include "Sprite.h"
#include "Constants.h"
#include "StageManager.h"
#include "SoundManager.h"

const float StarBlaster::smk_ShootDelay{ 2.4f };

StarBlaster::StarBlaster( const Point2f& position, float aggroRadius, float dropRadius, bool variation )
	: Enemy( position, 1, aggroRadius, dropRadius )
	, mk_Variation{ variation }
	, m_CollisionManager{ CollisionCircle{ 85.f, 85.f, 80.f, CollisionType::noHit }, &m_Location }
	, mk_CenterLocation{ position + Vector2f{ 85.f, 85.f } }
	, mk_ProjectileSettings
	{
		0,
		1,
		1,
		Constants::sk_StarblasterProjectileSpeed,
		Constants::sk_StarblasterProjectileRange,
		CollisionCircle( 97.f, 0.f, 28.f, CollisionType::noHit ),
		"cannon_ball",
		"cannon_death",
		"",
		"projectile_hit"
	}
	, m_IsOrdinal{ true }
	, m_ShootingDelayAccumulatedTime{}
{
	SetCollisionManager( &m_CollisionManager );

	InitializeQueues( 3, 2 );

	for( int i{}; i < smk_ProjectilesCount; ++i )
	{
		m_pProjectiles[i] = new Projectile{ &mk_ProjectileSettings };
		StageManager::PushCompositionEntity( m_pProjectiles[i] );
	}
}

StarBlaster::~StarBlaster( ) noexcept
{
	for( int i{}; i < smk_ProjectilesCount; ++i )
	{
		StageManager::PopCompositionEntity( m_pProjectiles[i] );
		delete m_pProjectiles[i];
	}
}

void StarBlaster::Draw( ) const
{
	for( int i{}; i < smk_ProjectilesCount; ++i )
	{
		m_pProjectiles[i]->Draw( );
	}

	Enemy::Draw( );
}

void StarBlaster::Update( float elapsedSec )
{
	if( !GetIsAggro( ) ) return;

	Enemy::Update( elapsedSec );

	m_ShootingDelayAccumulatedTime += elapsedSec;

	if ( m_ShootingDelayAccumulatedTime >= smk_ShootDelay )
	{
		m_ShootingDelayAccumulatedTime = 0.f;

		const float radius{ 70.f };
		float angleMultiple{ };
		if ( m_IsOrdinal )
		{
			QueueTexture( 0, m_pOrdinalShootSprite );
			QueueTexture( 0, m_pOrdinalRotateSprite );
			QueueTexture( 0, m_pCardinalIdleSprite );
			QueueTexture( 2, m_pOrdinalShootVFXSprite );
		}
		else
		{
			QueueTexture( 0, m_pCardinalShootSprite );
			QueueTexture( 0, m_pCardinalRotateSprite );
			QueueTexture( 0, m_pOrdinalIdleSprite );
			QueueTexture( 2, m_pCardinalShootVFXSprite );

			angleMultiple = 45.f;
		}

		for( int i{}; i < smk_ProjectilesCount; ++i )
		{
			m_pProjectiles[i]->Reset( mk_CenterLocation.ToPoint2f( ), radius, angleMultiple + ( i * 90.f ) );
		}
		SoundManager::Play( "cannon_spawn" );

		QueueTexture( 1, m_pStarShootSprite );
		QueueTexture( 1, m_pStarIdleSprite );

		m_IsOrdinal = !m_IsOrdinal;
	}

	for ( int i{}; i < smk_ProjectilesCount; ++i )
	{
		m_pProjectiles[i]->Update( elapsedSec );
	}
}

void StarBlaster::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	if ( mk_Variation )
	{
		m_pStarIdleSprite = pResourcesLinker->GetSprite( "starblaster_star_b_idle" );
		m_pStarShootSprite = pResourcesLinker->GetSprite( "starblaster_star_b_shoot" );
	}
	else
	{
		m_pStarIdleSprite = pResourcesLinker->GetSprite( "starblaster_star_a_idle" );
		m_pStarShootSprite = pResourcesLinker->GetSprite( "starblaster_star_a_shoot" );
	}

	m_pOrdinalIdleSprite = pResourcesLinker->GetSprite( "starblaster_ordinal_idle" );
	m_pOrdinalRotateSprite = pResourcesLinker->GetSprite( "starblaster_ordinal_rotate" );
	m_pOrdinalShootSprite = pResourcesLinker->GetSprite( "starblaster_ordinal_shoot" );
	m_pOrdinalShootVFXSprite = pResourcesLinker->GetSprite( "starblaster_ordinal_shoot_vfx" );

	m_pCardinalIdleSprite = pResourcesLinker->GetSprite( "starblaster_cardinal_idle" );
	m_pCardinalRotateSprite = pResourcesLinker->GetSprite( "starblaster_cardinal_rotate" );
	m_pCardinalShootSprite = pResourcesLinker->GetSprite( "starblaster_cardinal_shoot" );
	m_pCardinalShootVFXSprite = pResourcesLinker->GetSprite( "starblaster_cardinal_shoot_vfx" );

	QueueTexture( 0, m_pOrdinalIdleSprite );
	QueueTexture( 1, m_pStarIdleSprite );

	for ( int i{}; i < smk_ProjectilesCount; ++i )
	{
		m_pProjectiles[i]->LinkTexture( pResourcesLinker );
	}
}
