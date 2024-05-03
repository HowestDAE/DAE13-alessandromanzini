#pragma once
#include "Weapon.h"
class Spread final :
    public Weapon
{
public:
    Spread( );

    virtual Weapon::WeaponType GetType( ) const override;
    virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) override;

private:
};

