#pragma once
#include "Entity.h"
#include "Vector2f.h"
#include "ProjectileSettings.h"
#include "Sprite.h"
#include "Weapon.h"
#include "ResourcesLinker.h"
#include "CollisionManager.h"
class Projectile final
	: public Entity
{
public:
	explicit Projectile( const ProjectileSettings* settings );
	virtual ~Projectile( ) noexcept = default;

	void Draw( ) const;
	void Update( float elapsedSec );

	virtual bool CheckCollision( CollidableEntity& other ) override;
	virtual bool GetIFrameState( ) const override;

	void Reset( const Point2f& origin, float radius, float rotation );

	virtual void Kill( ) override;

	virtual void LinkTexture( ResourcesLinker* pResourceLinker ) override;

private:
	ProjectileSettings const* const mk_pProjectileSettings;
	CollisionManager m_CollisionManager;

	Sprite* m_pLoopSprite;
	Sprite* m_pDeathSprite;

	Vector2f m_CollisionLocation;

	float m_Radius;
	float m_Rotation;
	float m_TravelDistance;
};

