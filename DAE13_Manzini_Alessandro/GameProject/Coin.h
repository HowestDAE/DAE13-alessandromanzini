#pragma once
#include "Entity.h"
#include "CollisionManager.h"
class Sprite;

class Coin final
	: public Entity
{
public:
	explicit Coin( const Point2f& position );

	virtual bool CheckCollision( CollidableEntity& other ) override;

	virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) override;

private:
	CollisionManager m_CollisionManager;

	Sprite* m_pIdleSprite;
	Sprite* m_pCollectedSprite;

	void Collect( );

};

