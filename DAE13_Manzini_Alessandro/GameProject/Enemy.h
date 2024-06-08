#pragma once
#include "Entity.h"
class Enemy :
    public Entity
{
public:
    explicit Enemy( const Point2f& position, int hp, float aggroRadius, float dropRadius, int contactDamage = 1, bool isPink = false, bool screenLock = false );

    virtual void Update( float elapsedSec ) override;
    virtual void Update( float elapsedSec, const Vector2f& targetLocation );

    virtual bool CompareAggroDistance( const Vector2f& targetLocation );
    
    virtual void Reset( const Point2f& position );

    bool GetIsScreenLock( ) const;

protected:
    virtual void AggroEvent( );
    virtual void DropEvent( );

    bool GetIsAggro( ) const;

private:
    float m_AggroRadius;
    float mk_DropRadius;

    bool mk_ScreenLock;

    bool m_IsAggro;

};

