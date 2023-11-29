#ifndef ARMOR_PARSER_H
#define ARMOR_PARSER_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>

using std::map;
using std::cout;
using std::string;

#include "Armor.h"

class ArmorParser
{
public:
    static Armor*       loadFromStream  ( std::ifstream& );
    static void         saveInStream    ( Armor&, std::ofstream& );
private:
    static Armor* parseFile( std::ifstream& );
    enum class LoadState;
    enum class Attribute;

    static map< LoadState, string > load_state_matches;
    static map< Attribute, string > attribute_matches;
};

#endif // ARMOR_PARSER_H