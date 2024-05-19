#include "pch.h"
#include "CollidableEntity.h"
#include "CollisionManager.h"

CollidableEntity::CollidableEntity( int contactDamage )
	: mk_ContactDamage( contactDamage )
	, mk_pCollisionManager{}
{
}

int CollidableEntity::GetContactDamage( ) const
{
	return mk_ContactDamage;
}

CollisionManager const* CollidableEntity::GetCollisionManager( ) const
{
	return mk_pCollisionManager;
}

void CollidableEntity::SetCollisionManager( CollisionManager const* pCollisionManager )
{
	mk_pCollisionManager = pCollisionManager;
}

void CollidableEntity::DrawCollision( ) const
{
	mk_pCollisionManager->Draw( );
}

bool CollidableEntity::CheckCollision( CollidableEntity& other )
{
	const CollisionManager* pOtherManager{ other.GetCollisionManager( ) };
	CollisionInfo collisionInfo{};

	if ( mk_pCollisionManager->CheckCollision( *pOtherManager, collisionInfo ) )
	{
		if ( !collisionInfo.hollow )
		{
			Hit( other.GetContactDamage( ) );
			other.Hit( GetContactDamage( ) );
		}
		return true;
	}
	return false;
}
