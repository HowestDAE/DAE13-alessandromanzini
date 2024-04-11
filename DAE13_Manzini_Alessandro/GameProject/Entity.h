#pragma once
#include "TexturedModel.h"
#include "AnimationQueue.h"
class TextureManager;

class Entity
	: public TexturedModel
{
public:
	Entity( const Point2f& position );

	//virtual void Update( float elapsedSec ) override;
	virtual void ProcessPlatformCollision( const Vector2f& displacement );

	Vector2f GetVelocity( ) const;

protected:
	Vector2f m_Velocity;
	AnimationQueue m_AnimationQueue;

	bool TryQueueTexture( TextureManager* pTexture, bool flipX, bool flipY );
};

