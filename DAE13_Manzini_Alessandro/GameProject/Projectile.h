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

	void Reset( const Point2f& origin, float radius, float rotation );
	void SetSprite( Sprite* pSprite );

	virtual void LinkTexture( ResourcesLinker* pResourceLinker ) override;

private:
	ProjectileSettings const* const mk_pProjectileSettings;
	CollisionManager m_CollisionManager;

	Sprite* m_pSprite;

	Vector2f m_CollisionLocation;

	float m_Radius;
	float m_Rotation;
	float m_TravelDistance;
};

