
#include <iostream>

#include "Armor.h"
#include "Consumable.h"
#include "Attack.h"
#include "Player.h"
#include "Enemy.h"

#include "ConsumableParser.h"
#include "WeaponParser.h"
#include "ArmorParser.h"
#include "InventoryParser.h"
#include "EntityParser.h"
#include "BodyPartsParser.h"
#include "AttackParser.h"
#include "PlayerParser.h"
#include "EnemyParser.h"
#include "OffensiveConsumable.h"
#include "RestorativeConsumable.h"

#include "NormalBattle.h"
#include "BossBattle.h"
#include "NPC.h"

int main()
{
    std::ifstream attack_stream ("../Attack.sav");
    Attack* new_attack = AttackParser::loadFromStream(attack_stream);
    std::cout << *new_attack;

    std::ifstream entity_stream ("../Hero.sav");
    Player* new_player = PlayerParser::loadFromStream(entity_stream);
    std::cout << *new_player;

    std::ifstream enemy_stream ("../Enemy.sav");
    Enemy* new_enemy = EnemyParser::loadFromStream(enemy_stream);
    std::cout << *new_enemy;

    bool game_loop = true;

    while (game_loop) {
        game_loop = false;
    }

    delete new_enemy;
    delete new_player;
    delete new_attack;
    return 0;
}