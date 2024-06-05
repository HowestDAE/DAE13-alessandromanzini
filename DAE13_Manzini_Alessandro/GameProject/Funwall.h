#pragma once
#include "Enemy.h"
#include "Lip.h"
#include "CollisionManager.h"
class Sprite;
class Funwall final :
    public Enemy
{
public:
    explicit Funwall( const Point2f& position, float aggroRadius, float dropRadius );

    virtual void Draw( ) const override;

    virtual void Update( float elapsedSec ) override;
    virtual void Update( float elapsedSec, const Vector2f& targetLocation ) override;

    virtual void AggroEvent( ) override;

    virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) override;

private:
    CollisionManager m_CollisionManager;

    Sprite* m_pBoilSprite;
    Sprite* m_pEyeIdleSprite;
    Sprite* m_pEyeHitSprite;

    static const int smk_HonksCount{ 2 };
    Sprite* m_pHonkSprites[smk_HonksCount];
    float m_HonkCooldownTimes[smk_HonksCount];

    Lip m_Lips[smk_HonksCount];

    virtual void Hit( int damage ) override;

    void RandomizeHonk( int honkIndex );

};

