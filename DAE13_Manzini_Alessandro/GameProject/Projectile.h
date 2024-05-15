#pragma once
#include "CollidableEntity.h"
#include "Vector2f.h"
#include "ProjectileSettings.h"
#include "Sprite.h"
#include "Weapon.h"
#include "ResourcesLinker.h"
#include "CollisionManager.h"
class Projectile final
	: public CollidableEntity
{
public:
	explicit Projectile( const ProjectileSettings* settings );

	bool GetIsOutOfBound( ) const;

	void Draw( ) const;
	void Update( float elapsedSec );

	virtual bool CheckCollision( CollidableEntity& other ) override;
	virtual void Hit( int damage ) override;

	void Reset( const Point2f& origin, float radius, float rotation );

	void SetSprite( Sprite* pSprite );

private:
	const ProjectileSettings* mk_pProjectileSettings;
	CollisionManager m_CollisionManager;

	bool m_IsActive;
	int m_HP;

	Sprite* m_pSprite;

	Vector2f m_Location;
	Vector2f m_CollisionLocation;
	Vector2f m_Velocity;

	float m_Radius;
	float m_Rotation;
	float m_TravelDistance;
};

