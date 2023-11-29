#ifndef BODY_PARTS_PARSER_H
#define BODY_PARTS_PARSER_H

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

class BodyPartsParser
{
public:
    static BodyPart*        loadFromStream  ( std::ifstream& );
    static void             saveInStream    ( const BodyPart&, std::ofstream& );
private:
    static BodyPart* parseFile( std::ifstream& );
    enum class LoadState;
    enum class Attribute;

    static map< LoadState, string > load_state_matches;
    static map< Attribute, string > attribute_matches;
};

#endif // BODY_PARTS_PARSER_H