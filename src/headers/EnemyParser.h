#ifndef ENEMY_PARSER_H
#define ENEMY_PARSER_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>

using std::map;
using std::cout;
using std::string;
using std::vector;

#include "InventoryParser.h"
#include "BodyPartsParser.h"
#include "EntityDetails.h"
#include "Entity.h"
#include "Player.h"
#include "EntityParser.h"
#include "AttackParser.h"

#include "Enemy.h"

class EnemyParser
{
public:
    static Enemy*       loadFromStream  ( std::ifstream& );
    static void         saveInStream    ( Enemy&, std::ofstream& );
private:
    static Enemy* parseFile( std::ifstream& );
    enum class LoadState;
    enum class Attribute;

    static map< LoadState, string > load_state_matches;
    static map< Attribute, string > attribute_matches;
};

#endif // ENEMY_PARSER_H