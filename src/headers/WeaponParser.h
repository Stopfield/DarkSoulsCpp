#ifndef WEAPON_PARSER_H
#define WEAPON_PARSER_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>

using std::map;
using std::cout;
using std::string;

#include "Weapon.h"


class WeaponParser
{
public:
    static Weapon*      loadFromStream  ( std::ifstream& );
    static void         saveInStream    ( Weapon&, std::ofstream& );
private:
    static Weapon* parseFile( std::ifstream& );
    enum class LoadState;
    enum class Attribute;

    static map< LoadState, string > load_state_matches;
    static map< Attribute, string > attribute_matches;
};

#endif // WEAPON_PARSER_H