#pragma once
#include "TexturedModel.h"
#include "AnimationQueue.h"
#include "CollidableEntity.h"
class Texture2D;
class CollisionManager;
class PlatformManager;

class Entity
	: public TexturedModel
	, public CollidableEntity
{
public:
	Entity( const Point2f& position, int hp, int contactDamage = 1 );

	virtual void Update( float elapsedSec ) override;
	virtual void CheckCollision( PlatformManager const* pPlatformManager );

	virtual void Hit( int damage ) override;

	Vector2f GetVelocity( ) const;
	bool GetIsAlive( ) const;

protected:
	Vector2f m_Velocity;
	AnimationQueue m_AnimationQueue;

	int m_HP;

private:
	bool m_IsAlive;

};

