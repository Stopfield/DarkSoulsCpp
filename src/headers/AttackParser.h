#ifndef ATTACK_PARSER_H
#define ATTACK_PARSER_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>

using std::map;
using std::cout;
using std::string;

#include "Attack.h"

class AttackParser
{
public:
    static Attack*      loadFromStream  ( std::ifstream& );
    static void         saveInStream    ( const Attack&, std::ofstream& );
private:
    static Attack* parseFile( std::ifstream& );
    enum class LoadState;
    enum class Attribute;

    static map< LoadState, string > load_state_matches;
    static map< Attribute, string > attribute_matches;
};

#endif // ATTACK_PARSER_H