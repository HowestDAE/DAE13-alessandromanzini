#include "pch.h"
#include "Funwall.h"
#include "Constants.h"
#include "Sprite.h"

Funwall::Funwall( const Point2f& position, float aggroRadius, float dropRadius )
	: Enemy( position, Constants::sk_FunwallHP, aggroRadius, dropRadius, 1, false, true )
	, m_CollisionManager{ std::vector<CollisionCircle>{ CollisionCircle{ 180.f, 280.f, 150.f }, CollisionCircle{ 180.f, 580.f, 150.f } }, &m_Location }
	, m_Lips{}
	, m_pHonkSprites{}
	, m_HonkCooldownTimes{}
{
	InitializeQueues( 4, 4 );
	SetCollisionManager( &m_CollisionManager );
}

void Funwall::Draw( ) const
{
	Enemy::Draw( );

	for ( int i{}; i < smk_HonksCount; ++i )
	{
		m_Lips[i].Draw( );
	}
}

void Funwall::Update( float elapsedSec )
{
	Enemy::Update( elapsedSec );

	for ( int i{}; i < smk_HonksCount; ++i )
	{
		m_Lips[i].Update( elapsedSec );
	}
}

void Funwall::Update( float elapsedSec, const Vector2f& targetLocation )
{
	if ( !GetIsAggro( ) ) return;

	Update( elapsedSec );

	for ( int i{}; i < smk_HonksCount; ++i )
	{
		m_HonkCooldownTimes[i] -= elapsedSec;
		if ( m_HonkCooldownTimes[i] <= 0.f )
		{
			QueueTexture( 2 + i, TextureInfo{ m_pHonkSprites[i] }, true );

			const Vector2f spawnLocation{ m_pHonkSprites[i]->GetOffset( ) + m_Location };
			m_Lips[i].Reset( spawnLocation, targetLocation - spawnLocation );

			RandomizeHonk( i );
		}
	}
}

void Funwall::AggroEvent( )
{
	for ( int i{}; i < smk_HonksCount; ++i )
	{
		RandomizeHonk( i );
	}
}

void Funwall::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	m_pBoilSprite = pResourcesLinker->GetSprite( "funwall_boil" );
	m_pEyeIdleSprite = pResourcesLinker->GetSprite( "funwall_eye_idle" );
	m_pEyeHitSprite = pResourcesLinker->GetSprite( "funwall_eye_hit" );

	m_pHonkSprites[0] = pResourcesLinker->GetSprite( "funwall_honk_bottom" );
	m_pHonkSprites[1] = pResourcesLinker->GetSprite( "funwall_honk_top" );

	QueueTexture( 0, m_pBoilSprite );
	QueueTexture( 1, m_pEyeIdleSprite );

	for ( int i{}; i < smk_HonksCount; ++i )
	{
		m_Lips[i].LinkTexture( pResourcesLinker );
	}
}

void Funwall::Hit( int damage )
{
	Enemy::Hit( damage );
	
	QueueTexture( 1, TextureInfo{ m_pEyeHitSprite }, true );
	QueueTexture( 1, TextureInfo{ m_pEyeIdleSprite } );
}

void Funwall::RandomizeHonk( int honkIndex )
{
	m_HonkCooldownTimes[honkIndex] = 4.f;
}
