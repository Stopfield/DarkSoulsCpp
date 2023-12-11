#ifndef MELEE_WEAPON_H
#define MELEE_WEAPON_H

#include "Weapon.h"
#include "Entity.h"
#include "Attack.h"


class MeleeWeapon : public Weapon
{
    friend ostream& operator<<  ( ostream&, const MeleeWeapon& );
    friend int      operator!   ( const MeleeWeapon& );
public:
    MeleeWeapon             (  );
    MeleeWeapon             ( string, double, double );
    MeleeWeapon             ( const MeleeWeapon& );
    virtual ~MeleeWeapon    (  );

    void use            ( Entity& ) override;
    void inflict_damage ( Entity& ) override;
    void choose_attack  ( const Attack& );

    double  getBluntDamage() const { return this->blunt_damage; }
    void    setBluntDamage( double );

    const MeleeWeapon&  operator=   ( const MeleeWeapon& );
    int                 operator==  ( const MeleeWeapon& );
    int                 operator!=  ( const MeleeWeapon& );

private:
    double blunt_damage;
    double chosen_attack_damage_modifier = 1.0f;
};

#endif  // MELEE_WEAPON_H