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
	explicit Entity( const Point2f& position, int hp, int contactDamage = 1, bool isPink = false );
	virtual ~Entity( ) noexcept = default;

	Entity( const Entity& other ) = delete;
	Entity( Entity&& other ) noexcept;
	Entity& operator=( const Entity& other ) = delete;
	Entity& operator=( Entity&& other ) = delete;

	virtual void Draw( ) const override;
	void DrawBackside( ) const;
	virtual void Update( float elapsedSec ) override;

	virtual bool CheckCollision( PlatformManager const* pPlatformManager );

	Vector2f GetVelocity( ) const;
	bool GetIsAlive( ) const;
	int GetHP( ) const;

	virtual float GetTextureWidth( ) const;
	virtual float GetTextureHeight( ) const;
	Vector2f GetTextureOffset( ) const;

protected:
	Vector2f m_Velocity;

	virtual void UpdateLocation( float elapsedSec );
	virtual void UpdateHitFlashing( float elapsedSec, float epsilonTime, bool toggle = false );
	virtual void Hit( int damage ) override;

	virtual void Kill( );
	void Revive( int hp );

	void InitializeQueues( unsigned int count = 1, unsigned int backsideIndex = 0 );
	void QueueTexture( unsigned int index, Texture2D* pTexture, bool flipX = false, bool flipY = false, bool priority = false );
	bool IsQueueReady( unsigned int index ) const;

private:
	bool m_IsAlive;
	int m_HP;
	float m_FlashElapsedTime;

	std::vector<AnimationQueue> m_AnimationQueues;
	std::vector<TextureInfo> m_TextureInfos;
	int m_BacksideLimitIndex;

};

