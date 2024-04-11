#pragma once
#include<vector>
class Projectile;
class Texture;
class Weapon
{
public:
	enum class WeaponType;

	Weapon( int initialProjectilesCount, float projectileDamage, float projectileSpeed, float projectileRange );

	Projectile* GetProjectile( const Point2f& pos, float rotation );
	virtual WeaponType GetType( ) const = 0;

	float GetProjectileDamage( ) const;
	float GetProjectileSpeed( ) const;
	float GetProjectileRange( ) const;
	std::vector<Projectile*>& GetProjectiles( );

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
