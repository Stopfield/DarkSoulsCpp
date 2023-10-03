#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::pair;

#include "weapon.h"
#include "enemy.h"
#include "Item.h"

class Enemy;
class Item;

class Player
{
public:
    Player();
    Player( string, double = 100.0f, double = 100.0f, double = 15.0f );
    Player( const Player& );
    ~Player();

    inline static uint getNumPlayers()      { return Player::numPlayers;    };
    inline static size_t getNameMaxSize()   { return Player::NAME_MAX_SIZE; };

    void equipWeapon	( Weapon& );
    bool battle         ( Enemy& );
    void attack		    ( Enemy& ) const;
    void guard          ( );
    void grabItem       ( Item& );
    void useItem        ( Item& );
    void move           ( );
    void showInventory  ( );

    inline bool isUnarmed() const { return (equipedWeapon == 0) ? true : false; }

    // Getters/Setters
    inline string getName()        const   { return this->name;        }
    inline double getHealth()      const   { return this->health;      }
    inline double getStamina()     const   { return this->stamina;     }
    inline double getStrength()    const   { return this->strength;    }
    inline double getVelocity()    const   { return this->velocity;    }
    inline double getPosition()    const   { return this->position;    }
    inline bool isGuarding()       const   { return this->guarding;    }

    /* Retornar um ponteiro constante é má prática! */
    /* Mas e uma referência constante?              */
    inline Weapon& getEquipedWeapon() const { return *this->equipedWeapon; }

    void setName	    ( string );
    void setHealth	    ( double );
    void setStamina	    ( double );
    void setStrenght	( double );
    void setVelocity    ( double );

private:

    static uint numPlayers;
    const static size_t NAME_MAX_SIZE = 20;
    /* Máximo de um item que ele pode ter no inventário! */
    const static size_t ITEM_MAX_STACK = 99;

    vector< pair<Item, short> > inventory;
    
    string name;
    double health;
    double stamina;
    double strength;
    double velocity = 100.0;
    // Placeholder - substituir com Vector3
    double position = 0.0f;

    /* Arma equipada pelo personagem */
    Weapon* equipedWeapon = 0;

    bool guarding = false;
};

#endif // PLAYER_h
