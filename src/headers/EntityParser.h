#ifndef ENTITY_PARSER_H
#define ENTITY_PARSER_H

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

class EntityParser
{
public:
    static Entity*      loadFromStream  ( std::ifstream& );
    static void         saveInStream    ( Entity&, std::ofstream& );
private:
    static Entity* parseFile( std::ifstream& );
    enum class LoadState;
    enum class Attribute;

    static map< LoadState, string > load_state_matches;
    static map< Attribute, string > attribute_matches;
};

#endif // INVENTORY_PARSER_H