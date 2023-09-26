#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

using std::string;
using std::cout;

#include "weapon.h"

class Player
{
public:
    Player();
    Player( string, double = 100.0f, double = 100.0f, double = 15.0f );
    Player( const Player& );

    void equipWeapon	( Weapon& );
    void attack		    ( /* Enemy& */ ) const;
    void guard          ( );

    // Getters/Setters
    string getName()        const   { return this->name;     }
    double getHealth()      const   { return this->health;   }
    double getStamina()     const   { return this->stamina;  }
    double getStrength()    const   { return this->strength; }

    /* Retornar um ponteiro constante é má prática! */
    /* Mas e uma referência constante?              */
    const Weapon& getEquipedWeapon() const { return *equipedWeapon; }

    void setName	    ( string );
    void setHealth	    ( double );
    void setStamina	    ( double );
    void setStrenght	( double );

private:
    string name;
    double health;
    double stamina;
    double strength;

    /* Arma equipada pelo personagem */
    Weapon* equipedWeapon;

    bool isGuarding = false;

    const size_t NAME_MAX_SIZE = 20;

    /* Máximo de um item que ele pode ter no inventário! */
    const size_t ITEM_MAX_STACK = 99;

};

#endif // PLAYER_h
