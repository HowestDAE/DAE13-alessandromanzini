#pragma once
#include "Weapon.h"
class Peashooter final :
    public Weapon
{
public:
    Peashooter();
    virtual ~Peashooter( ) noexcept = default;

    virtual Weapon::WeaponType GetType( ) const override;

    virtual void SpawnProjectile( const Point2f& origin, float radius, float rotation ) override;
    virtual void LinkTexture( ResourcesLinker* pResourcesLinker ) override;

private:
    bool m_IsAlternatedShot;
};

