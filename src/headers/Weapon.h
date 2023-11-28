#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::ostream;

#include "Item.h"

class Weapon : public Item
{
    friend ostream& operator<<  ( ostream&, const Weapon& );
    friend int      operator!   (const Weapon& );
public:
    Weapon();
    Weapon( string, double, int = 100 );
    Weapon( const Weapon& );
    virtual ~Weapon();

    void    increaseDurability  ( double );
    void    decreaseDurability  ( int );

    int getDurability() const { return this->durability;    }
    double getDamage()  const { return this->damage;        }

    void setDurability  ( int );
    void setDamage      ( double );

    const Weapon& operator= ( const Weapon& );
    int operator==          ( const Weapon& );
    int operator!=          ( const Weapon& );

protected:
    const static string DEFAULT_WEAPON_NAME;

    double  damage;
    int     durability;
};  

#endif // WEAPON_H