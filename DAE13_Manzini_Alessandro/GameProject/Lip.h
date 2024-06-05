#pragma once
#include "Entity.h"
#include "CollisionManager.h"
class Sprite;
class Lip final :
    public Entity
{
public:
    Lip( );

    virtual void Update( float elapsedSec ) override;

    void Reset( const Vector2f& location, const Vector2f& aimDirection );

    virtual void LinkTexture( ResourcesLinker* pResourcesLinker );

private:
    CollisionManager m_CollisionManager;

    Sprite* m_pLoopSprite;

};

