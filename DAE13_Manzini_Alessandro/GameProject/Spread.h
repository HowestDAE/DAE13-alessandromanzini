#pragma once
#include "Weapon.h"
class Spread final :
    public Weapon
{
public:
    Spread( );

    virtual void SpawnProjectile( const Point2f& origin, float radius, float rotation ) override;
    virtual void SpawnEx( const Point2f& origin, float radius, float rotation ) override;

    virtual Weapon::WeaponType GetType( ) const override;

private:

};

