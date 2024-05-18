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
	explicit Entity( const Point2f& position, int hp, int contactDamage = 1 );

	virtual void Draw( ) const override;
	virtual void Update( float elapsedSec ) override;

	virtual void CheckCollision( PlatformManager const* pPlatformManager );

	Vector2f GetVelocity( ) const;
	bool GetIsAlive( ) const;
	int GetHP( ) const;

	virtual float GetTextureWidth( ) const;
	virtual float GetTextureHeight( ) const;

protected:
	Vector2f m_Velocity;

	virtual void UpdateHitFlashing( float elapsedSec, float epsilonTime, bool toggle = false );
	virtual void Hit( int damage ) override;

	virtual void Kill( );
	void Revive( int hp );

	void InitializeQueues( int count = 1 );
	void QueueTexture( int index, Texture2D* pTexture, bool flipX = false, bool flipY = false, bool priority = false );

private:
	bool m_IsAlive;
	int m_HP;
	float m_FlashElapsedTime;

	std::vector<AnimationQueue> m_AnimationQueues;
	std::vector<TextureInfo> m_TextureInfos;

};

