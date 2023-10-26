#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::ostream;

class Weapon
{
    friend ostream& operator<<  ( ostream&, const Weapon& );
    friend int      operator!   (const Weapon& );
public:
    Weapon();
    Weapon( string, double, int = 100 );
    Weapon( const Weapon& );
    ~Weapon();

    double  inflictDamage       ( double );
    void    increaseDurability  ( double );
    void    decreaseDurability  ( int );
    void    printStatus         ( ) const;

    string getName()    const { return this->name;          }
    int getDurability() const { return this->durability;    }
    double getDamage()  const { return this->damage;        }

    void setName        ( string );
    void setDurability  ( int );
    void setDamage      ( double );

    const Weapon& operator= ( const Weapon& );
    int operator== ( const Weapon& );
    int operator!= ( const Weapon& );

private:
    const static size_t NAME_MAX_SIZE;
    const static string DEFAULT_WEAPON_NAME;

    string  name;
    double  damage;
    int     durability;
};  

#endif
