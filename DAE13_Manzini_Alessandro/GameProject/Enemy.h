#pragma once
#include "Entity.h"
class Enemy :
    public Entity
{
public:
    explicit Enemy( const Point2f& position, int hp, float aggroRadius, float dropRadius, int contactDamage = 1, bool isPink = false, bool screenLock = false );

    virtual void Update( float elapsedSec ) override;

    virtual bool CompareAggroDistance( const Vector2f& targetLocation );

    bool GetIsScreenLock( ) const;

private:
    float mk_AggroRadius;
    float mk_DropRadius;

    bool mk_ScreenLock;

    bool m_IsAggro;

};

