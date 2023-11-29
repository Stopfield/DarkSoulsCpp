#include "ConsumableParser.h"

enum class ConsumableParser::LoadState
{
    CONSUMABLE, END_CONSUMABLE
};

enum class ConsumableParser::Attribute
{
    HEALTH_FACTOR,
    NAME, DESCRIPTION,
    BEFORE, AFTER
};

map< ConsumableParser::LoadState, string > ConsumableParser::load_state_matches = {
    { ConsumableParser::LoadState::CONSUMABLE,      "[CONSUMABLE]"      },
    { ConsumableParser::LoadState::END_CONSUMABLE,  "[END_CONSUMABLE]"  }
};

map< ConsumableParser::Attribute, string > ConsumableParser::attribute_matches = {
    { ConsumableParser::Attribute::HEALTH_FACTOR,   "health_factor" },
    { ConsumableParser::Attribute::NAME,            "name"          },
    { ConsumableParser::Attribute::DESCRIPTION,     "description"   },
    { ConsumableParser::Attribute::BEFORE,          "before"        },
    { ConsumableParser::Attribute::AFTER,           "after"         }
};

/**
 * Verifica se o arquivo especificado na stream é um
 * Consumable, verificando a primeira linha, que deve ser [CONSUMABLE].
 * Se for, ele tentará dar parse, senão ele retorna nullptr.
 * @param loaded_file_stream Input stream do arquivo já carregado.
*/
Consumable* ConsumableParser::loadFromStream( std::ifstream& loaded_file_stream )
{
    // Parse player file
    string first_line;

    loaded_file_stream >> first_line;
    if ( first_line == ConsumableParser::load_state_matches[ LoadState::CONSUMABLE ])
        return ConsumableParser::parseFile( loaded_file_stream );
    
    return nullptr;
}

/**
 * Escreve um item consumable em um output stream já definido!
 * Preste atenção! Se você definir um ofstream no início de um
 * arquivo, ele será sobrescrito!
 * @param item                  Item a ser escrito
 * @param loaded_file_stream    Output stream de um arquivo
*/
void ConsumableParser::saveInStream(Consumable& item, std::ofstream& loaded_file_stream)
{
    using LoadState = ConsumableParser::LoadState;
    using Attribute = ConsumableParser::Attribute;

    // // Pega o arquivo no último caractere
    // std::ofstream file ( file_path, std::ios::app | std::ios::ate );

    // if (!file.is_open())
    // {
    //     std::cerr << "ERRO AO ABRIR ARQUIVO: " << file_path
    //         << "! Durante salvamento de Consumable!\n";
    //     exit( EXIT_FAILURE );
    // }
    
    loaded_file_stream << "\n";

    loaded_file_stream << ConsumableParser::load_state_matches[ LoadState::CONSUMABLE ] << "\n";
    
    loaded_file_stream
        << ConsumableParser::attribute_matches[ Attribute::NAME ]
        << "="
        << item.getName()
        << "\n";
    loaded_file_stream
        << ConsumableParser::attribute_matches[ Attribute::DESCRIPTION ]
        << "="
        << item.getDescription()
        << "\n";
    loaded_file_stream
        << ConsumableParser::attribute_matches[ Attribute::HEALTH_FACTOR ]
        << "="
        << item.getHealthFactor()
        << "\n";
    loaded_file_stream
        << ConsumableParser::attribute_matches[ Attribute::BEFORE ]
        << "="
        << item.getBefore()
        << "\n";
    loaded_file_stream
        << ConsumableParser::attribute_matches[ Attribute::AFTER ]
        << "="
        << item.getAfter()
        << "\n";

    loaded_file_stream << ConsumableParser::load_state_matches[ LoadState::END_CONSUMABLE ] << "\n";
}

/**
 * Parse the Consumable file and creates a new Consumable object.
 * Uses the static maps and associated enums to do so.
 * This is a line example "attribute=value", named "key=value"
 * for convenience.
 * @param input_stream Input stream for the file.
*/
Consumable *ConsumableParser::parseFile( std::ifstream& input_stream )
{
    using Attribute = ConsumableParser::Attribute;
    using LoadState = ConsumableParser::LoadState;
    
    string entire_line, line_value, line_key;
    size_t equal_sign_index;

    Consumable* new_consumable = new Consumable();

    while (true)
    {
        std::getline( input_stream, entire_line );

        // If [END_PLAYER], stop parsing.
        if (entire_line == ConsumableParser::load_state_matches[ LoadState::END_CONSUMABLE ])
            break;

        equal_sign_index = entire_line.find( '=' );

        line_key     = entire_line.substr( 0, equal_sign_index );
        line_value   = entire_line.substr( equal_sign_index + 1, entire_line.size() );
                
        if (line_key == ConsumableParser::attribute_matches[ Attribute::NAME ])
        {
            new_consumable->setName( line_value );
            continue;
        }

        if (line_key == ConsumableParser::attribute_matches[ Attribute::DESCRIPTION ])
        {
            new_consumable->setDescription( line_value );
            continue;
        }

        if (line_key == ConsumableParser::attribute_matches[ Attribute::HEALTH_FACTOR ])
        {
            new_consumable->setHealthFactor( stod( line_value ) );
            continue;
        }

        if (line_key == ConsumableParser::attribute_matches[ Attribute::BEFORE ])
        {
            new_consumable->setBefore( line_value[0] );
            continue;
        }

        if (line_key == ConsumableParser::attribute_matches[ Attribute::AFTER ])
        {
            new_consumable->setAfter( line_value[0] );
            continue;
        }
    }
    return new_consumable;
}
