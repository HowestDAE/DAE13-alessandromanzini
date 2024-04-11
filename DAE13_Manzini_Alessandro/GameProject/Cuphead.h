#pragma once
#include "Entity.h"
#include "WeaponsManager.h"
#include "MovementManager.h"

class CompositeSpriteManager;
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

    void ProcessPlatformCollision( const Vector2f& displacement ) final;

    // Gets the width of the idle instead of the current texture
    float GetTextureWidth( ) const;

    friend void ResourcesLinker::LinkTexture( Cuphead* pCuphead );
    //Cuphead& operator=( const Cuphead& rhs ) = default;

private:
    WeaponsManager m_WeaponManager;
    MovementManager m_MovementManager;

    SpriteManager* m_pIdleSprite;
    CompositeSpriteManager* m_pRunSprite;
    CompositeSpriteManager* m_pDuckSprite;
    SpriteManager* m_pJumpSprite;
    CompositeSpriteManager* m_pDashGroundSprite;
    CompositeSpriteManager* m_pDashAirSprite;

    bool SelectTexture(MovementManager::AimDirection direction, MovementManager::MovementType movement );
    void UpdateMovement( float elapsedSec );
    void UpdateWeapons( float elapsedSec );
};

