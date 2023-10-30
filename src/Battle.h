#ifndef BATTLE_H
#define BATTLE_H

#include "Player.h"
#include "Enemy.h"

/**
 * Administra a batalha entre entidades Player e Enemy.
*/
class Battle
{
public:
    void planTurn();
    void executeTurn();
private:
    Player  *const  player;
    Enemy   *const  enemy;
    unsigned int    turn;
};

#endif