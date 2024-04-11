#pragma once
#include <vector>
#include "Weapon.h"
#include "ResourcesLinker.h"
class Projectile;
class WeaponsManager final
{
public:
	WeaponsManager( );
	~WeaponsManager( );

	void SwapWeapons( );
	void Shoot( const Point2f& pos, float rotation );
	void ShootEX( const Point2f& pos, float rotation );

	void Update( float elapsedSec );

	friend void ResourcesLinker::LinkTexture( Cuphead* pCuphead );

private:
	static const int smk_WeaponsCount{ 2 };
	static const float smk_ShotDelay;
	
	Weapon* m_pWeapons[smk_WeaponsCount];
	int m_EquippedWeaponIndex;

	float m_ShotAccumulatedTime;
};

