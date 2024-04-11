#pragma once
#include "Weapon.h"
class Peashooter final :
    public Weapon
{
public:
    Peashooter();

    virtual Weapon::WeaponType GetType( ) const override;
};

