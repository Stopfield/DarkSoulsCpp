#include "BodyPartsParser.h"

enum class BodyPartsParser::LoadState
{
    PART, END_PART
};

enum class BodyPartsParser::Attribute
{
    PART_DESCRIPTION, DAMAGE_MODIFIER
};

map< BodyPartsParser::LoadState, string > BodyPartsParser::load_state_matches = {
    { BodyPartsParser::LoadState::PART,             "[PART]"            },
    { BodyPartsParser::LoadState::END_PART,         "[END_PART]"        }
};

map< BodyPartsParser::Attribute, string > BodyPartsParser::attribute_matches = {
    { BodyPartsParser::Attribute::PART_DESCRIPTION,     "part_description"      },
    { BodyPartsParser::Attribute::DAMAGE_MODIFIER,      "damage_modifier"       }
};

/**
 * Verifica se o arquivo especificado na stream é um
 * Consumable, verificando a primeira linha, que deve ser [CONSUMABLE].
 * Se for, ele tentará dar parse, senão ele retorna nullptr.
 * @param loaded_file_stream Input stream do arquivo já carregado.
*/
BodyPart* BodyPartsParser::loadFromStream( std::ifstream& loaded_file_stream )
{
    // Parse player file
    string first_line;

    loaded_file_stream >> first_line;

    if ( first_line == BodyPartsParser::load_state_matches[ LoadState::PART ])
        return BodyPartsParser::parseFile( loaded_file_stream );
        
    return nullptr;
}

/**
 * Escreve um item consumable em um output stream já definido!
 * Preste atenção! Se você definir um ofstream no início de um
 * arquivo, ele será sobrescrito!
 * @param item                  Item a ser escrito
 * @param loaded_file_stream    Output stream de um arquivo
*/
void BodyPartsParser::saveInStream(const BodyPart& body_part, std::ofstream& loaded_file_stream)
{
    using LoadState = BodyPartsParser::LoadState;
    using Attribute = BodyPartsParser::Attribute;

    // // Pega o arquivo no último caractere
    // std::ofstream file ( file_path, std::ios::app | std::ios::ate );

    loaded_file_stream << BodyPartsParser::load_state_matches[ LoadState::PART ] << "\n";

    loaded_file_stream
        << BodyPartsParser::attribute_matches[ Attribute::PART_DESCRIPTION ]
        << "="
        << body_part.partDescription
        << "\n";
    loaded_file_stream
        << BodyPartsParser::attribute_matches[ Attribute::DAMAGE_MODIFIER ]
        << "="
        << body_part.damageModifier
        << "\n";

    loaded_file_stream << BodyPartsParser::load_state_matches[ LoadState::PART ] << "\n";
    
    loaded_file_stream << "\n";

}

/**
 * Parse the Consumable file and creates a new Consumable object.
 * Uses the static maps and associated enums to do so.
 * This is a line example "attribute=value", named "key=value"
 * for convenience.
 * @param input_stream Input stream for the file.
*/
BodyPart* BodyPartsParser::parseFile( std::ifstream& input_stream )
{
    using Attribute = BodyPartsParser::Attribute;
    using LoadState = BodyPartsParser::LoadState;
    
    string entire_line, line_value, line_key;
    size_t equal_sign_index;

    BodyPart* new_body_part_ptr = new BodyPart;

    while (true)
    {
        std::getline( input_stream, entire_line );

        // If [END_PLAYER], stop parsing.
        if (entire_line == BodyPartsParser::load_state_matches[ LoadState::END_PART ])
            break;

        equal_sign_index = entire_line.find( '=' );

        line_key     = entire_line.substr( 0, equal_sign_index );
        line_value   = entire_line.substr( equal_sign_index + 1, entire_line.size() );

        if (line_key == BodyPartsParser::attribute_matches[ Attribute::PART_DESCRIPTION ])
        {
            new_body_part_ptr->partDescription = line_value;
            continue;
        }

        if (line_key == BodyPartsParser::attribute_matches[ Attribute::DAMAGE_MODIFIER ])
        {
            new_body_part_ptr->damageModifier = std::stod( line_value );
            continue;
        }
    }
    return new_body_part_ptr;
}
