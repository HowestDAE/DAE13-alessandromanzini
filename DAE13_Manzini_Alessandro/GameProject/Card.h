#pragma once
#include "Entity.h"
#include "CollisionManager.h"

class Card final 
    : public Entity
{
public:
    explicit Card( const Point2f& position );

    virtual void Draw( ) const override;
    virtual void Update( float elapsedSec ) override;

    void ParryCollisionFeedback( );

    virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) override;

private:
    Sprite* m_pIdleSprite;
    Sprite* m_pSpinSprite;
    Sprite* m_pStarsSprite;

    CollisionManager m_CollisionManager;

};

