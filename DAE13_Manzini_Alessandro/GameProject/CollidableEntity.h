#pragma once
#include "vector"
#include "Vector2f.h"
class CollisionManager;

class CollidableEntity
{
public:
	CollidableEntity( int contactDamage );

	int GetContactDamage( ) const;

	CollisionManager const* GetCollisionManager( ) const;
	void SetCollisionManager( CollisionManager const* pCollisionManager );

	void DrawCollision( ) const;

	virtual bool CheckCollision( CollidableEntity& other );
	virtual void Hit( int damage ) = 0;

private:
	const int mk_ContactDamage;

	CollisionManager const* mk_pCollisionManager;
};

