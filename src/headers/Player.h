#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

using std::string;
using std::cout;

#include "Entity.h"

class Player : public Entity
{
public:
    Player();
    Player( string,
            double = 100.0f,
            double = 100.0f,
            double = 50.0f,
            double = 25.0f,
            Vector2D = { 0 },
            vector< BodyPart > = DEFAULT_ENTITY_BODY_PARTS );
    Player( const Player& );
    ~Player();

    // void receiveInput   ( );
    void addAttack      ( Attack& );
 
    inline static uint getNumPlayers() { return Player::numPlayers; };

private:
    void copyAttacks        ( const Player& );
    void deleteAttacks      (  );

    static unsigned int numPlayers;
    vector< Attack* >   attacks;        // É melhor um ponteiro de ataques ou só ataques?
};

#endif // PLAYER_h
