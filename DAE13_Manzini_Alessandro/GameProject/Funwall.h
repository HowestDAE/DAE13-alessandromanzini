#pragma once
#include "Enemy.h"
#include "Lip.h"
#include "CollisionManager.h"
class Sprite;
class Funwall final :
    public Enemy
{
public:
    explicit Funwall( const Point2f& position, float aggroRadius, float dropRadius, bool tongueVariation );
    virtual ~Funwall( ) noexcept override;

    Funwall( const Funwall& ) = delete;
    Funwall( Funwall&& ) = delete;
    Funwall& operator=( const Funwall& ) = delete;
    Funwall& operator=( Funwall&& ) = delete;

    virtual void Draw( ) const override;
    virtual void DrawBackside( ) const override;

    virtual void Update( float elapsedSec ) override;
    virtual void Update( float elapsedSec, const Vector2f& targetLocation ) override;

    virtual bool CompareAggroDistance( const Vector2f& targetLocation ) override;

    virtual void AggroEvent( ) override;

    virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) override;

private:
    const static float smk_LipsSpawnDelay;
    const static Vector2f smk_ToycarBottomSpawnOffset;
    const static Vector2f smk_ToycarTopSpawnOffset;
    const static Vector2f smk_TongueBottomSpawnOffset;
    const static Vector2f smk_TongueTopSpawnOffset;

    const bool mk_TongueVariation;

    CollisionManager m_CollisionManager;

    Sprite* m_pBoilSprite;
    Sprite* m_pEyeIdleSprite;
    Sprite* m_pEyeHitSprite;

    Sprite* m_pDeathSprite;
    Sprite* m_pDeathCoverSprite;
    Sprite* m_pDeathVFXSprite;
    Point2f m_DeathVFXPosition;

    static const int smk_SidesCount{ 2 };

    Sprite* m_pHonkSprites[smk_SidesCount];
    Sprite* m_pHonkVFXSprites[smk_SidesCount];
    float m_HonkCooldownTimes[smk_SidesCount];
    bool m_HasHonked[smk_SidesCount];
    Lip m_Lips[smk_SidesCount];

    static const float smk_UhohCastDelay;
    static const float smk_UhohAttackDelay;
    static const float smk_UhohRecoverDelay;
    Sprite* m_pUhohSprite[smk_SidesCount];
    Sprite* m_pOpeningSprite[smk_SidesCount];
    Sprite* m_pOpenSprite[smk_SidesCount];
    Sprite* m_pClosingSprite[smk_SidesCount];
    Sprite* m_pMouthCoverSprite[smk_SidesCount];
    bool m_HasCastedUhoh;
    bool m_HasAttackedUhoh;
    int m_UhohIndex;
    float m_UhohCooldownTime;
    Enemy* m_pUhohEnemies[smk_SidesCount];

    static const float smk_HitSFXDelay;
    float m_HitSFXTimer;

    void InitializeUhOhEntities( float aggroRadius, float dropRadius );

    void UpdateHonkAttack( float elapsedSec, const Vector2f& targetLocation );
    void UpdateUhohAttack( float elapsedSec );

    virtual void Hit( int damage ) override;

    void RandomizeHonk( int honkIndex );
    void RandomizeDeathVFX( );

    virtual void Kill( ) override;

};

