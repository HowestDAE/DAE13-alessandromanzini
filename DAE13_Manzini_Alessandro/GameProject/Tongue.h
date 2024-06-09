#pragma once
#include "Enemy.h"
#include "CollisionManager.h"
class Sprite;
class Tongue final :
    public Enemy
{
public:
    explicit Tongue( const Point2f& position, float aggroRadius, float dropRadius, bool upsideDown = false );

    virtual void Update( float elapsedSec ) override;

    virtual void Reset( const Point2f& position ) override;
    virtual void Reset( ) override;

    virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) override;

private:
    static const float smk_TongueDuration;

    const bool mk_UpsideDown;

    CollisionManager m_CollisionManager;
    Vector2f m_CollisionLocation;
    Vector2f m_CollisionVelocity;

    Sprite* m_pIntroSprite;
    Sprite* m_pLoopSprite;
    Sprite* m_pOutroSprite;

    float m_TongueElapsedTime;
    bool m_CycleCompleted;

};

