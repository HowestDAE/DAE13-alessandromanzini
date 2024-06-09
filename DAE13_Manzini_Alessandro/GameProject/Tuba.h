#pragma once
#include "Enemy.h"
#include "CollisionManager.h"
#include "BwaAttack.h"

class ResourcesLinker;
class Sprite;
class Tuba final :
    public Enemy
{
public:
    explicit Tuba( const Point2f& position, float aggroRadius, float dropRadius );
    virtual ~Tuba( ) noexcept;

    Tuba( const Tuba& ) = delete;
    Tuba& operator=( const Tuba& ) = delete;
    Tuba( Tuba&& ) = delete;
    Tuba& operator=( Tuba&& ) = delete;
        
    virtual void DrawBackside( ) const override;
    virtual void Update( float elapsedSec, const Vector2f& targetLocation ) override;

    virtual void Kill( ) override;

    virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) override;

private:
    CollisionManager m_CollisionManager;

    static const Vector2f smk_BwaAttackLocation;
    BwaAttack m_BwaAttack;

    static const float smk_TubaAttackSpeed;
    static const float smk_TubaCastSpeed;
    float m_AttackTimer;
    bool m_HasCasted;

    Sprite* m_pIdleSprite;
    Sprite* m_pAttackSprite;
    Sprite* m_pAttackCoverSprite;
    Sprite* m_pDeathSprite;

};

