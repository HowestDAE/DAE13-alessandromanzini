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

	void DrawCollision( ) const;

	int GetContactDamage( ) const;
	int GetIsPink( ) const;

	void SetCollisionManager( CollisionManager const* pCollisionManager );
	CollisionManager const* GetCollisionManager( ) const;

	virtual bool GetIFrameState( ) const = 0;

	virtual void Hit( int damage ) = 0;
	virtual bool CheckCollision( CollidableEntity& other );	

private:
	const int mk_ContactDamage;
	const bool mk_IsPink;

	CollisionManager const* mk_pCollisionManager;
};

