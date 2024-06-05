#pragma once
#include <vector>
#include <Vector2f.h>
#include "Weapon.h"
#include "ResourcesLinker.h"
#include "HUDManager.h"
class Projectile;
class WeaponsManager final
{
public:
	WeaponsManager( );
	~WeaponsManager( ) noexcept;

	WeaponsManager( const WeaponsManager& other ) = delete;
	WeaponsManager( WeaponsManager&& other ) noexcept;
	WeaponsManager& operator=( const WeaponsManager& rhs ) = delete;
	WeaponsManager& operator=( WeaponsManager&& rhs ) = delete;

	void SwapWeapons( );
	void Shoot( const Point2f& origin, float radius, float rotation );
	void ShootEX( const Point2f& origin, float radius, float rotation );

	void CheckCollision( CollidableEntity& other );

	void Draw( ) const;
	void Update( float elapsedSec );

	void UpdateEx( float elapsedSec );
	void UpdateHUDManager( HUDManager* pHUDManager ) const;

	// Gets the ex queue flag and turns it to false
	bool RequireExMoveQueue( );
	bool GetIsExMoveOngoing( ) const;

	void StopAudioLoop( );

	void LinkTexture( ResourcesLinker* pResourcesLinker );

private:
	static const int smk_WeaponsCount{ 2 };
	static const float smk_ShotDelay;
	static const float smk_ExIntermediateDelay;
	static const float smk_ExDelay;
	
	Weapon* m_pWeapons[smk_WeaponsCount];
	int m_EquippedWeaponIndex;

	float m_ShotAccumulatedTime;
	float m_ExAccumulatedTime;
	bool m_ExNeedsQueue;

	int m_ExMoves;
	float m_ExProgress;

	bool m_IsAudioLoopPlaying;
};

