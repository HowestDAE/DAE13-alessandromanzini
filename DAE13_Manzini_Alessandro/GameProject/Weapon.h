#pragma once
#include <vector>
#include "CollidableEntity.h"
#include "ProjectileSettings.h"
class ResourcesLinker;
class Projectile;
class Texture;

class Weapon
{
public:
	enum class WeaponType;

	explicit Weapon( const ProjectileSettings& projectileSettings, const ProjectileSettings& exMoveSettings, float exProgressPerHit );
	virtual ~Weapon( ) noexcept;

	Weapon( const Weapon& other ) = delete;
	Weapon( Weapon&& other ) noexcept;
	Weapon& operator=( const Weapon& rhs ) = delete;
	Weapon& operator=( Weapon&& rhs ) = delete;

	virtual WeaponType GetType( ) const = 0;

	virtual void SpawnProjectile( const Point2f& origin, float radius, float rotation );
	virtual void SpawnEx( const Point2f& origin, float radius, float rotation );

	// returns the amount of ex progress per hit
	float CheckCollision( CollidableEntity& other );

	void Draw( ) const;
	void Update( float elapsedSec );

	virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) = 0;

protected:
	const ProjectileSettings mk_ProjectileSettings;
	const ProjectileSettings mk_ExMoveSettings;

	const float mk_ExProgressPerHit;

	int m_CurrentProjectileIndex;
	int m_CurrentExMoveIndex;

	std::vector<Projectile*> m_pProjectiles;
	std::vector<Projectile*> m_pExMoves;
};

enum class Weapon::WeaponType
{
	peashooter,
	spread
};
