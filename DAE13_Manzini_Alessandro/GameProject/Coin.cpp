#include "pch.h"
#include "Coin.h"
#include "Sprite.h"
#include "SoundManager.h"

Coin::Coin( const Point2f& position )
	: Entity( position, 1, 0 )
	, m_CollisionManager{ std::vector<CollisionCircle>{ CollisionCircle{ 39.f, 40.f, 25.f, CollisionType::hollow }, CollisionCircle{ 39.f, 70.f, 25.f, CollisionType::hollow } }, &m_Location }
{
	SetCollisionManager( &m_CollisionManager );
	InitializeQueues( 1, 1 );
}

bool Coin::CheckCollision( CollidableEntity& other )
{
	if ( GetIsAlive( ) )
	{
		const bool collision{ CollidableEntity::CheckCollision( other ) };

		if ( collision )
		{
			Collect( );
			return true;
		}
	}
	return false;
}

void Coin::LinkTexture( ResourcesLinker* pResourcesLinker )
{
	m_pIdleSprite = pResourcesLinker->GetSprite( "coin_idle" );
	m_pCollectedSprite = pResourcesLinker->GetSprite( "coin_collected" );

	QueueTexture( 0, m_pIdleSprite );
}

void Coin::Collect( )
{
	Kill( );
	QueueTexture( 0, m_pCollectedSprite );

	SoundManager::Play( "coin_pickup" );
}
