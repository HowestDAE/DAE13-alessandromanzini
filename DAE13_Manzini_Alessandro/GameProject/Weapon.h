#pragma once
#include <vector>
#include <Vector2f.h>
class Projectile;
class Texture;
class Weapon
{
public:
	enum class WeaponType;

	Weapon( int initialProjectilesCount, float projectileDamage, float projectileSpeed, float projectileRange );
	~Weapon( );

	virtual WeaponType GetType( ) const = 0;

	float GetProjectileDamage( ) const;
	float GetProjectileSpeed( ) const;
	float GetProjectileRange( ) const;
	std::vector<Projectile*>& GetProjectiles( );

	virtual void SpawnProjectile( const Point2f& origin, float radius, float rotation );

	void Draw( ) const;
	void Update( float elapsedSec );

protected:
	const int mk_InitialProjectilesCount;

	const float mk_ProjectileDamage;
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
