#pragma once
#include "Enemy.h"
#include "CollisionManager.h"
class Sprite;

class Toycar final :
    public Enemy
{
public:
    explicit Toycar( const Point2f& position, float aggroRadius, float dropRadius, unsigned int variation = 0, bool updown = false );

    virtual void DrawBackside( ) const override;

    virtual void UpdateLocation( float elapsedSec ) override;

    virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) override;

private:
    const unsigned int smk_VariationsCount{ 4 };

    const unsigned int mk_Count;
    const bool mk_Updown;

    CollisionManager m_CollisionManager;
    Vector2f m_CollisionLocation;

    std::vector<Sprite*> m_pIdleSprites;

};

