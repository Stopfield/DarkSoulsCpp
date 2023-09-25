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
    ~Weapon();

    string getName() const { return this->name; };
    int getDurability() const { return this->durability; };
    double getDamage() const { return this->damage; };

    void setName( string );
    void setDurability( int );
    void setDamage( double );

    // TODO Botar o inimigo aqui. Só placeholder
    // void inflictDamage( /* FUTURO OBJETO */ );
    double inflictDamage( double );

    void printStatus() const;

private:
    string name;
    double damage;
    int durability;

    const size_t MAX_NAME_SIZE = 15;
};  

#endif
