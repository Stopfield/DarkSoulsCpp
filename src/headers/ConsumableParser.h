#ifndef CONSUMABLE_PARSER_H
#define CONSUMABLE_PARSER_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>

using std::map;
using std::cout;
using std::string;

#include "Consumable.h"


class ConsumableParser
{
public:
    static Consumable* loadFromStream( std::ifstream& );
    static void        saveInStream( Consumable&, std::ofstream& );
private:
    static Consumable* parseFile( std::ifstream& );
    enum class LoadState;
    enum class Attribute;

    static map< LoadState, string > load_state_matches;
    static map< Attribute, string > attribute_matches;
    
};

#endif // CONSUMABLE_PARSER_H