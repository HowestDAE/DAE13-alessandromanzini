#pragma once
#include "vector"
#include "Vector2f.h"
class CollisionManager;

class CollidableEntity
{
public:
	explicit CollidableEntity( int contactDamage, bool isPink = false );
	virtual ~CollidableEntity( ) noexcept = default;

	CollidableEntity( const CollidableEntity& other ) = delete;
	CollidableEntity( CollidableEntity&& other ) = delete;
	CollidableEntity& operator=( const CollidableEntity& rhs) = delete;
	CollidableEntity& operator=( CollidableEntity&& rhs ) = delete;

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

	CollisionManager const* const mk_pCollisionManager;
};

