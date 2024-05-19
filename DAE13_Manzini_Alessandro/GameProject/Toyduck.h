#pragma once
#include "Entity.h"
#include "CollisionManager.h"
class Sprite;

class Toyduck final :
    public Entity
{
public:
    explicit Toyduck( const Point2f& position );

    virtual void Update( float elapsedSec ) override;

    virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) override;

private:
    Sprite* m_pIdleSprite;
    Sprite* m_pBacktireSprite;

    CollisionManager m_CollisionManager;
};

