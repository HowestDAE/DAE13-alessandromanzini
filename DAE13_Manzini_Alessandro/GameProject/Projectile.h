#pragma once
#include "Vector2f.h"
#include "SpriteManager.h"
#include "Weapon.h"
#include "ResourcesLinker.h"
class Projectile
{
public:
	explicit Projectile( const Weapon* pWeapon );

	Weapon::WeaponType GetType( ) const;
	bool GetIsOutOfBound( ) const;

	void Draw( ) const;
	void Update( float elapsedSec );

	void Reset( const Point2f& pos, float rotation );

	friend void ResourcesLinker::LinkTexture( Projectile* pProjectile );

private:
	SpriteManager* m_pSpriteManager;
	float m_Rotation;

	const Weapon* mk_pWeapon;

	float m_TravelDistance;

	Vector2f m_Location;
	Vector2f m_Velocity;
};

