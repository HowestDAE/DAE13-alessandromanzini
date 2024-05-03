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
	void SetCollisionManager( CollisionManager* pCollisionManager );

	void DrawCollision( ) const;

	void CheckCollision( CollidableEntity& other );
	virtual void Hit( int damage ) = 0;

private:
	const int mk_ContactDamage;

	CollisionManager* m_pCollisionManager;
};

