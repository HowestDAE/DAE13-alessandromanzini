#pragma once
#include "Enemy.h"
#include "CollisionManager.h"
#include "Projectile.h"
class Sprite;
class StarBlaster final :
	public Enemy
{
public:
	explicit StarBlaster( const Point2f& position, float aggroRadius, float dropRadius, bool variation = false );
	virtual ~StarBlaster( ) noexcept override;

	StarBlaster( const StarBlaster& ) = delete;
	StarBlaster( StarBlaster&& ) = delete;
	StarBlaster& operator=( const StarBlaster& ) = delete;
	StarBlaster& operator=( StarBlaster&& ) = delete;

	virtual void Draw( ) const override;
	virtual void Update( float elapsedSec ) override;

	virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) override;

private:
	const bool mk_Variation;

	CollisionManager m_CollisionManager;

	const Vector2f mk_CenterLocation;

	static const int smk_ProjectilesCount{ 4 };
	const ProjectileSettings mk_ProjectileSettings;
	Projectile* m_pProjectiles[smk_ProjectilesCount];

	bool m_IsOrdinal;
	bool m_IsShooting;
	static const float smk_ShootDelay;
	float m_ShootingDelayAccumulatedTime;

	Sprite* m_pStarIdleSprite;
	Sprite* m_pStarShootSprite;

	Sprite* m_pOrdinalIdleSprite;
	Sprite* m_pOrdinalRotateSprite;
	Sprite* m_pOrdinalShootSprite;
	Sprite* m_pOrdinalShootVFXSprite;

	Sprite* m_pCardinalIdleSprite;
	Sprite* m_pCardinalRotateSprite;
	Sprite* m_pCardinalShootSprite;
	Sprite* m_pCardinalShootVFXSprite;

};

