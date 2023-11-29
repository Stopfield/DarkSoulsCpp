#ifndef INVENTORY_PARSER_H
#define INVENTORY_PARSER_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>

using std::map;
using std::cout;
using std::string;
using std::vector;

#include "EntityDetails.h"
#include "ConsumableParser.h"
#include "ArmorParser.h"
#include "WeaponParser.h"

class InventoryParser
{
public:
    static vector<InventoryItem*>*  loadFromStream  ( std::ifstream& );
    static void                     saveInStream    ( const vector<InventoryItem*>*, std::ofstream& );
private:
    static vector<InventoryItem*>* parseFile( std::ifstream& );
    enum class LoadState;
    enum class Attribute;

    static map< LoadState, string > load_state_matches;
    static map< Attribute, string > attribute_matches;
};

#endif // INVENTORY_PARSER_H