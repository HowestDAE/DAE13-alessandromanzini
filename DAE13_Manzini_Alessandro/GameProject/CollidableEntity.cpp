#include "pch.h"
#include "CollidableEntity.h"
#include "CollisionManager.h"

CollidableEntity::CollidableEntity( int contactDamage )
	: mk_ContactDamage( contactDamage )
	, m_pCollisionManager{}
{
}

int CollidableEntity::GetContactDamage( ) const
{
	return mk_ContactDamage;
}

CollisionManager const* CollidableEntity::GetCollisionManager( ) const
{
	return m_pCollisionManager;
}

void CollidableEntity::SetCollisionManager( CollisionManager* pCollisionManager )
{
	m_pCollisionManager = pCollisionManager;
}

void CollidableEntity::DrawCollision( ) const
{
	m_pCollisionManager->Draw( );
}

void CollidableEntity::CheckCollision( CollidableEntity& other )
{
	const CollisionManager* pOtherManager{ other.GetCollisionManager( ) };
	CollisionInfo collisionInfo{};

	if ( m_pCollisionManager->CheckCollision( *pOtherManager, collisionInfo ) )
	{
		if ( collisionInfo.selfHit )
		{
			Hit( other.GetContactDamage( ) );
		}
		if ( collisionInfo.otherHit )
		{
			other.Hit( GetContactDamage( ) );
		}
	}
}
