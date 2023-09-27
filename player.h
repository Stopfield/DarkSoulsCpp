#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

using std::string;
using std::cout;

#include "weapon.h"
#include "enemy.h"

class Player
{
public:
    Player();
    Player( string, double = 100.0f, double = 100.0f, double = 15.0f );
    Player( const Player& );
    ~Player() {};

    void equipWeapon	( Weapon& );
    void attack		    ( Enemy& ) const;
    void guard          ( );
    void grabItem       ( );
    void move           ( );

    bool isUnarmed() const { return (equipedWeapon == 0) ? true : false; }

    // Getters/Setters
    string getName()        const   { return this->name;        }
    double getHealth()      const   { return this->health;      }
    double getStamina()     const   { return this->stamina;     }
    double getStrength()    const   { return this->strength;    }
    double getVelocity()    const   { return this->velocity;    }
    double getPosition()    const   { return this->position;    }
    bool isGuarding()       const   { return this->guarding;    }

    /* Retornar um ponteiro constante é má prática! */
    /* Mas e uma referência constante?              */
    Weapon& getEquipedWeapon() const { return *this->equipedWeapon; }

    void setName	    ( string );
    void setHealth	    ( double );
    void setStamina	    ( double );
    void setStrenght	( double );
    void setVelocity    ( double );

private:
    string name;
    double health;
    double stamina;
    double strength;
    double velocity = 100.0;
    // Placeholder - substituir com Vector3
    double position = 0.0f;

    // Representa um item - PLACEHOLDER
    int item = 0;

    /* Arma equipada pelo personagem */
    Weapon* equipedWeapon = 0;

    bool guarding = false;

    const size_t NAME_MAX_SIZE = 20;

    /* Máximo de um item que ele pode ter no inventário! */
    const size_t ITEM_MAX_STACK = 99;
};

#endif // PLAYER_h
