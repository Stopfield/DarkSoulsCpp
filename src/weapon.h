#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class Weapon
{
public:
    Weapon();
    Weapon( string, double, int = 100 );
    Weapon( const Weapon& );
    ~Weapon();

    // TODO Botar a entidade aqui. Só placeholder
    // void inflictDamage( /* FUTURO OBJETO */ );
    double inflictDamage( double );
    void printStatus() const;

    string getName()    const { return this->name;          }
    int getDurability() const { return this->durability;    }
    double getDamage()  const { return this->damage;        }

    void setName( string );
    void setDurability( int );
    void setDamage( double );


private:
    string name;
    double damage;
    int durability;

    const size_t NAME_MAX_SIZE = 15;
};  

#endif
