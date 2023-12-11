#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::ostream;

#include "Item.h"
class Entity;   /* Não precisa importar Entity, só precisa saber que tem */

class Weapon : public Item
{
public:
    Weapon();
    Weapon( string, double, int = 100 );
    Weapon( const Weapon& );
    virtual ~Weapon();

    virtual void use            ( Entity& ) = 0;
    virtual void inflict_damage ( Entity& ) = 0;

    void    increaseDurability  ( double );
    void    decreaseDurability  ( int );

    int     getDurability() const { return this->durability;    }
    double  getDamage()     const { return this->damage;        }

    void setDurability  ( int );
    void setDamage      ( double );

protected:
    const static string DEFAULT_WEAPON_NAME;

    double  damage;
    int     durability;
};  

#endif // WEAPON_H
