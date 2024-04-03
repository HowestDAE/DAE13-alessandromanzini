#pragma once
#include "Entity.h"
#include "WeaponsManager.h"
#include "MovementManager.h"

class Cuphead final 
    : public Entity
{
public:
    explicit Cuphead( const Point2f& position );
    //Cuphead( const Cuphead& other ) = default;
    //~Cuphead( );

    virtual void Draw( ) const override;
    virtual void Update( float elapsedSec ) override;

    void KeyPressEvent( const SDL_KeyboardEvent& e );

    friend void ResourcesLinker::LinkTexture( Cuphead* cuphead ) const;

    //Cuphead& operator=( const Cuphead& rhs ) = default;

private:
    WeaponsManager m_WeaponManager;
    
    MovementManager m_MovementManager;

    bool m_FlipTextureX;
    bool m_FlipTextureY;
    SpriteManager* m_pIdleSprite;
    SpriteManager* m_pRunSprite;

    void SelectTexture( );
};

