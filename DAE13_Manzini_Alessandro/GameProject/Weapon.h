#pragma once
#include <vector>
#include "CollisionCircle.h"
#include "CollidableEntity.h"
class ResourcesLinker;
class Projectile;
class Texture;

class Weapon
{
public:
	enum class WeaponType;

	Weapon( int initialProjectilesCount, int projectileDamage, float projectileSpeed, float projectileRange, const CollisionCircle& bulletCollisionCircle, const CollisionCircle& exCollisionCircle );
	~Weapon( );

	virtual WeaponType GetType( ) const = 0;

	int GetProjectileDamage( ) const;
	float GetProjectileSpeed( ) const;
	float GetProjectileRange( ) const;

	virtual void SpawnProjectile( const Point2f& origin, float radius, float rotation );

	void CheckCollision( CollidableEntity& other );

	void Draw( ) const;
	void Update( float elapsedSec );

	virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) = 0;

protected:
	const int mk_InitialProjectilesCount;

	const int mk_ProjectileDamage;
	const float mk_ProjectileSpeed;
	const float mk_ProjectileRange;

	int m_CurrentProjectileIndex;

	std::vector<Projectile*> m_pProjectiles;
};

enum class Weapon::WeaponType
{
	peashooter,
	spread
};
