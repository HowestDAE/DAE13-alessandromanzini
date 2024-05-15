#pragma once
#include "Entity.h"
#include "WeaponsManager.h"
#include "MovementManager.h"
#include "CollisionManager.h"
class Sprite;
class HUDManager;

class Cuphead final 
    : public Entity
{
public:
    explicit Cuphead( const Point2f& position, HUDManager* pHUDManager );
    /*Cuphead( const Cuphead& other ) = delete;
    Cuphead& operator=( const Cuphead& rhs ) = delete;
    Cuphead( Cuphead&& other ) = delete;
    Cuphead& operator=( Cuphead&& rhs ) = delete;
    ~Cuphead( );*/

    virtual void Draw( ) const override;
    virtual void Update( float elapsedSec ) override;

    void KeyPressEvent( const SDL_KeyboardEvent& e );

    virtual void CheckCollision( PlatformManager const* pPlatformManager ) override;
    virtual bool CheckCollision( CollidableEntity& other ) override;

    virtual void Hit( int damage ) override;

    // Gets the width of the idle instead of the current texture
    float GetTextureWidth( ) const;

    virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) override;

private:
    HUDManager* m_pHUDManager;

    WeaponsManager m_WeaponManager;
    MovementManager m_MovementManager;

    CollisionManager m_StandingCollisionManager;
    CollisionManager m_DuckingCollisionManager;

    bool m_IsInvincible;
    float m_IFramesElapsedTime;

    Sprite* m_pIdleSprite;
    Sprite* m_pRunSprite;
    Sprite* m_pDuckBeginSprite;
    Sprite* m_pDuckSprite;
    Sprite* m_pDuckShootSprite;
    Sprite* m_pJumpSprite;
    Sprite* m_pParrySprite;
    Sprite* m_pDashGroundSprite;
    Sprite* m_pDashAirSprite;
    Sprite* m_pShootStraightSprite;
    Sprite* m_pShootDiagonalupSprite;
    Sprite* m_pShootDiagonaldownSprite;
    Sprite* m_pShootDownSprite;
    Sprite* m_pShootUpSprite;
    Sprite* m_pAimUpSprite;
    Sprite* m_pAimStraightSprite;
    Sprite* m_pAimDiagonaldownSprite;
    Sprite* m_pAimDiagonalupSprite;
    Sprite* m_pAimDownSprite;
    Sprite* m_pExAirUpSprite;
    Sprite* m_pExAirStraightSprite;
    Sprite* m_pExAirDiagonaldownSprite;
    Sprite* m_pExAirDiagonalupSprite;
    Sprite* m_pExAirDownSprite;
    Sprite* m_pRunShootStraightSprite;
    Sprite* m_pRunShootDiagonalupSprite;
    Sprite* m_pHitSprite;
    Sprite* m_pGhostSprite;

    void UpdateMovement( float elapsedSec );
    void UpdateWeapons( float elapsedSec );
    void UpdateIFrames( float elapsedSec );

    void UpdateHUDManager( ) const;

    void TryShoot( );
    void SelectTexture( );

    void SelectIdle( );
	void SelectDuck( bool isShooting, bool isTransitioning );
	void SelectAim( bool isShooting, MovementManager::AimDirection direction );
	void SelectRun( bool isShooting, MovementManager::AimDirection direction );
	void SelectJump( );
	void SelectParry( );
	void SelectDashGround( );
	void SelectDashAir( );
    void SelectExMove( MovementManager::AimDirection direction );

    void QueueTexture( Texture2D* pTexture, bool priority = false );

    void Kill( );
};
