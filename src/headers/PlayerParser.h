#ifndef PLAYER_PARSER_H
#define PLAYER_PARSER_H

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

class PlayerParser
{
public:
    static Player*      loadFromStream  ( std::ifstream& );
    static void         saveInStream    ( Player&, std::ofstream& );
private:
    static Player* parseFile( std::ifstream& );
    enum class LoadState;
    enum class Attribute;

    static map< LoadState, string > load_state_matches;
    static map< Attribute, string > attribute_matches;
};

#endif // PLAYER_PARSER_H