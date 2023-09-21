#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

using std::string;
using std::cout;

class Player
{
public:
    Player();
    Player( string, double, double, double);
    Player( const Player& );

    string getName()        const   { return this->name;     }
    double getHealth()      const   { return this->health;   }
    double getStamina()     const   { return this->stamina;  }
    double getStrength()    const   { return this->strength; }

    void setName( string );
    void setHealth( double );
    void setStamina( double );
    void setStrenght( double );

private:
    string name;
    double health;
    double stamina;
    double strength;

    const size_t NAME_MAX_STR = 20;

};

#endif // PLAYER_h