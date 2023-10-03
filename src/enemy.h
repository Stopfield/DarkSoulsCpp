#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cstdlib>
#include <ctime>

using std::string;
using std::cout;
using std::vector;
using std::array;
using std::rand;
using std::time;

#include "weapon.h"
#include "player.h"

class Player;

class Enemy
{
public:
    Enemy   ();
    Enemy   ( string, double = 100.0f, double = 100.0f, double = 15.0f );
    Enemy   ( const Enemy& );
    ~Enemy  ();

    /* Métodos static não podem ser const */
    inline static uint getNumEnemies()      { return Enemy::numEnemies;     }
    inline static size_t getNameMaxSize()   { return Enemy::NAME_MAX_SIZE;  }

    static string chooseBodyPart();
    static void enrageEnemy( Enemy& );

    void equipWeapon	( Weapon& );
    void attack		    ( Player& ) const;
    void guard          ( );

    /* Retornar um ponteiro constante é má prática! */
    /* Mas e uma referência constante?              */
    inline const Weapon& getEquipedWeapon() const { return *this->equipedWeapon; }
    inline bool isUnarmed() const { return (equipedWeapon == 0) ? true : false; }
    inline bool isGuarding() const { return this->guarding; }

    // Getters/Setters
    inline string getName()        const   { return this->name;     }
    inline double getHealth()      const   { return this->health;   }
    inline double getStamina()     const   { return this->stamina;  }
    inline double getStrength()    const   { return this->strength; }

    void setName	    ( string );
    void setHealth	    ( double );
    void setStamina	    ( double );
    void setStrenght	( double );

private:

    /* Atributos static também ficam no private! */
    const static array<string, 3> BODY_PARTS;
    const static uint MAX_NUM_ENEMIES;
    const static size_t NAME_MAX_SIZE;
    const static ushort MIN_ENEMIES_TO_RAGE;

    static uint numEnemies;

    string name;
    double health;
    double stamina;
    double strength;
    bool guarding = false;

    /* Arma equipada pelo personagem */
    Weapon* equipedWeapon = 0;

    /* Máximo de um item que ele pode ter no inventário! */
    // const size_t ITEM_MAX_STACK = 99;
};

#endif // ENEMY_H
