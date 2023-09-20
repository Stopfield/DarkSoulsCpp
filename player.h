#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

using std::string;

class Player
{
public:
    Player();
    Player( string, double, double, double);
    Player( const Player& );

    string getName() const;
    double getHealth() const;
    double getStrength() const;

    void setName( string );
    void setStamina( double );
    void setStrenght( double );

private:
    string name;
    double health;
    double stamina;
    double strength;
};

#endif // PLAYER_h