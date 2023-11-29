#include "ArmorParser.h"

enum class ArmorParser::LoadState
{
    ARMOR, END_ARMOR
};

enum class ArmorParser::Attribute
{
    DAMAGE_REDUCTION, MIN_STRENGTH, WEIGHT,
    NAME, DESCRIPTION,
    BEFORE, AFTER
};

map< ArmorParser::LoadState, string > ArmorParser::load_state_matches = {
    { ArmorParser::LoadState::ARMOR,      "[ARMOR]"      },
    { ArmorParser::LoadState::END_ARMOR,  "[END_ARMOR]"  }
};

map< ArmorParser::Attribute, string > ArmorParser::attribute_matches = {
    { ArmorParser::Attribute::DAMAGE_REDUCTION, "damage_reduction"  },
    { ArmorParser::Attribute::MIN_STRENGTH,     "min_strength"      },
    { ArmorParser::Attribute::WEIGHT,           "weight"            },
    { ArmorParser::Attribute::NAME,             "name"              },
    { ArmorParser::Attribute::DESCRIPTION,      "description"       },
    { ArmorParser::Attribute::BEFORE,           "before"            },
    { ArmorParser::Attribute::AFTER,            "after"             },
};

/**
 * Verifica se o arquivo especificado na stream é um
 * Consumable, verificando a primeira linha, que deve ser [CONSUMABLE].
 * Se for, ele tentará dar parse, senão ele retorna nullptr.
 * @param loaded_file_stream Input stream do arquivo já carregado.
*/
Armor* ArmorParser::loadFromStream( std::ifstream& loaded_file_stream )
{
    // Parse player file
    string first_line;

    loaded_file_stream >> first_line;
        
    if ( first_line == ArmorParser::load_state_matches[ LoadState::ARMOR ])
        return ArmorParser::parseFile( loaded_file_stream );
    
    return nullptr;
}

/**
 * Escreve um item consumable em um output stream já definido!
 * Preste atenção! Se você definir um ofstream no início de um
 * arquivo, ele será sobrescrito!
 * @param item                  Item a ser escrito
 * @param loaded_file_stream    Output stream de um arquivo
*/
void ArmorParser::saveInStream(Armor& item, std::ofstream& loaded_file_stream)
{
    using LoadState = ArmorParser::LoadState;
    using Attribute = ArmorParser::Attribute;
    
    loaded_file_stream << "\n";

    loaded_file_stream << ArmorParser::load_state_matches[ LoadState::ARMOR ] << "\n";

    loaded_file_stream
        << ArmorParser::attribute_matches[ Attribute::NAME ]
        << "="
        << item.getName()
        << "\n";
    loaded_file_stream
        << ArmorParser::attribute_matches[ Attribute::DESCRIPTION ]
        << "="
        << item.getDescription()
        << "\n";
    loaded_file_stream
        << ArmorParser::attribute_matches[ Attribute::DAMAGE_REDUCTION ]
        << "="
        << item.getDamageReduction()
        << "\n";
    loaded_file_stream
        << ArmorParser::attribute_matches[ Attribute::MIN_STRENGTH ]
        << "="
        << item.getMinStrength()
        << "\n";
    loaded_file_stream
        << ArmorParser::attribute_matches[ Attribute::WEIGHT ]
        << "="
        << item.getWeight()
        << "\n";
    loaded_file_stream
        << ArmorParser::attribute_matches[ Attribute::BEFORE ]
        << "="
        << item.getBefore()
        << "\n";
    loaded_file_stream
        << ArmorParser::attribute_matches[ Attribute::AFTER ]
        << "="
        << item.getAfter()
        << "\n";

    loaded_file_stream << ArmorParser::load_state_matches[ LoadState::END_ARMOR ] << "\n";
}

/**
 * Parse the Consumable file and creates a new Consumable object.
 * Uses the static maps and associated enums to do so.
 * This is a line example "attribute=value", named "key=value"
 * for convenience.
 * @param input_stream Input stream for the file.
*/
Armor* ArmorParser::parseFile( std::ifstream& input_stream )
{
    using Attribute = ArmorParser::Attribute;
    using LoadState = ArmorParser::LoadState;
    
    string entire_line, line_value, line_key;
    size_t equal_sign_index;

    Armor* new_armor = new Armor();

    while (true)
    {
        std::getline( input_stream, entire_line );

        // If [END_PLAYER], stop parsing.
        if (entire_line == ArmorParser::load_state_matches[ LoadState::END_ARMOR ])
            break;

        equal_sign_index = entire_line.find( '=' );

        line_key     = entire_line.substr( 0, equal_sign_index );
        line_value   = entire_line.substr( equal_sign_index + 1, entire_line.size() );
                
        if (line_key == ArmorParser::attribute_matches[ Attribute::NAME ])
        {
            new_armor->setName( line_value );
            continue;
        }

        if (line_key == ArmorParser::attribute_matches[ Attribute::DESCRIPTION ])
        {
            new_armor->setDescription( line_value );
            continue;
        }

        if (line_key == ArmorParser::attribute_matches[ Attribute::DAMAGE_REDUCTION ])
        {
            new_armor->setDamageReduction( stod( line_value ) );
            continue;
        }

        if (line_key == ArmorParser::attribute_matches[ Attribute::MIN_STRENGTH ])
        {
            new_armor->setMinStrength( stod( line_value ) );
            continue;
        }

        if (line_key == ArmorParser::attribute_matches[ Attribute::WEIGHT ])
        {
            new_armor->setWeight( stod( line_value ) );
            continue;
        }
        
        if (line_key == ArmorParser::attribute_matches[ Attribute::BEFORE ])
        {
            new_armor->setBefore( line_value[0] );
            continue;
        }

        if (line_key == ArmorParser::attribute_matches[ Attribute::AFTER ])
        {
            new_armor->setAfter( line_value[0] );
            continue;
        }
    }
    return new_armor;
}
