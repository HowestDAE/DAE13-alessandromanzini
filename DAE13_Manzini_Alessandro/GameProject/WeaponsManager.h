#pragma once
#include <vector>
#include <Vector2f.h>
#include "Weapon.h"
#include "ResourcesLinker.h"
class Projectile;
class WeaponsManager final
{
public:
	WeaponsManager( );
	~WeaponsManager( );

	void SwapWeapons( );
	void Shoot( const Point2f& origin, float radius, float rotation );
	void ShootEX( const Point2f& origin, float radius, float rotation );

	void CheckCollision( CollidableEntity& other );

	void Draw( ) const;
	void Update( float elapsedSec );

	void LinkTexture( ResourcesLinker* pResourcesLinker );

private:
	static const int smk_WeaponsCount{ 2 };
	static const float smk_ShotDelay;
	
	Weapon* m_pWeapons[smk_WeaponsCount];
	int m_EquippedWeaponIndex;

	float m_ShotAccumulatedTime;
};

