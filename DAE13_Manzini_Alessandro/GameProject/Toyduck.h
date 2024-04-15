#pragma once
#include "Entity.h"
class SpriteManager;
class Toyduck final :
    public Entity
{
public:
    explicit Toyduck( const Point2f& position );

    virtual void Draw( ) const override;
    virtual void Update( float elapsedSec ) override;

    friend void ResourcesLinker::LinkTexture( Toyduck* pToyduck ) const;

private:
    SpriteManager* m_pIdleSprite;
    SpriteManager* m_pBacktireSprite;
};

