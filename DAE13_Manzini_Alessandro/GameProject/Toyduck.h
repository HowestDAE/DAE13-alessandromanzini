#pragma once
#include "Enemy.h"
#include "CollisionManager.h"
class Sprite;

class Toyduck final :
    public Enemy
{
public:
    explicit Toyduck( const Point2f& position, float aggroRadius, float dropRadius );
    virtual ~Toyduck( ) noexcept = default;

    virtual void Update( float elapsedSec ) override;

    virtual void Kill( ) override;

    virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) override;

private:
    Sprite* m_pIdleSprite;
    Sprite* m_pBacktireSprite;
    Sprite* m_pDeathSprite;
    Sprite* m_pDeathBacktireSprite;

    CollisionManager m_CollisionManager;
};

