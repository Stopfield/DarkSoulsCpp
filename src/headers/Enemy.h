#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <ctime>
#include <map>

using std::cout;
using std::vector;
using std::rand;
using std::time;

#include "Entity.h"

class Enemy : public Entity
{
    friend ostream& operator<<  ( ostream&, const Enemy& );
    friend int      operator!   ( const Enemy& );
public:
    Enemy   ();
    Enemy   (   string,
                double = 100.0f,
                double = 100.0f,
                double = 50.0f,
                double = 25.0f,
                Vector2D = { 0 },
                vector< BodyPart > = DEFAULT_ENTITY_BODY_PARTS,
                map< short, Attack * > = { } );
    Enemy   ( const Enemy& );
    ~Enemy  ( );

    /* Métodos static não podem ser const */
    inline static unsigned short getNumEnemies() { return Enemy::numEnemies; }

    Attack& chooseAttack    (  );
    void enrageEnemy        ( Enemy& )  const;

    const Enemy&    operator=   ( const Enemy& );
    int             operator==  ( const Enemy& );
    int             operator!=  ( const Enemy& );

private:
    const static unsigned int   MAX_NUM_ENEMIES;
    const static unsigned short MIN_ENEMIES_TO_RAGE;
    
    static unsigned short numEnemies;

    //Isso é o melhor jeito de fazer as coisas? 
    map< short, Attack* > probabilitiesAndAttacks;
};

#endif // ENEMY_H
