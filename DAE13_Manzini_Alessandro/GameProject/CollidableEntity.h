#pragma once
#include "vector"
#include "Vector2f.h"
class CollisionManager;

class CollidableEntity
{
public:
	CollidableEntity( int contactDamage, bool isPink = false );

	int GetContactDamage( ) const;
	int GetIsPink( ) const;

	CollisionManager const* GetCollisionManager( ) const;
	void SetCollisionManager( CollisionManager const* pCollisionManager );

	void DrawCollision( ) const;

	virtual bool CheckCollision( CollidableEntity& other );
	virtual void Hit( int damage ) = 0;

private:
	const int mk_ContactDamage;
	const bool mk_IsPink;

	CollisionManager const* mk_pCollisionManager;
};

