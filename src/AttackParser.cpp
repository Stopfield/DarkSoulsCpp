#include "AttackParser.h"

enum class AttackParser::LoadState
{
    ATTACK, END_ATTACK
};

enum class AttackParser::Attribute
{
    NAME, DISPLAY_MESSAGE,
    STAMINA_COST_MODIFIER, DAMAGE_MODIFIER
};

map< AttackParser::LoadState, string > AttackParser::load_state_matches = {
    { AttackParser::LoadState::ATTACK,      "[ATTACK]"      },
    { AttackParser::LoadState::END_ATTACK,  "[END_ATTACK]"  }
};

map< AttackParser::Attribute, string > AttackParser::attribute_matches = {
    { AttackParser::Attribute::NAME,                    "name"                  },
    { AttackParser::Attribute::DISPLAY_MESSAGE,         "display_message"       },
    { AttackParser::Attribute::STAMINA_COST_MODIFIER,   "stamina_cost_modifier" },
    { AttackParser::Attribute::DAMAGE_MODIFIER,         "damage_modifier"       }
};

/**
 * Verifica se o arquivo especificado na stream é um
 * Consumable, verificando a primeira linha, que deve ser [CONSUMABLE].
 * Se for, ele tentará dar parse, senão ele retorna nullptr.
 * @param loaded_file_stream Input stream do arquivo já carregado.
*/
Attack* AttackParser::loadFromStream( std::ifstream& loaded_file_stream )
{
    // Parse player file
    string first_line;

    loaded_file_stream >> first_line;

    if ( first_line == AttackParser::load_state_matches[ LoadState::ATTACK ])
        return AttackParser::parseFile( loaded_file_stream );
    
    return nullptr;
}

/**
 * Escreve um item consumable em um output stream já definido!
 * Preste atenção! Se você definir um ofstream no início de um
 * arquivo, ele será sobrescrito!
 * @param item                  Item a ser escrito
 * @param loaded_file_stream    Output stream de um arquivo
*/
void AttackParser::saveInStream(const Attack& item, std::ofstream& loaded_file_stream)
{
    using LoadState = AttackParser::LoadState;
    using Attribute = AttackParser::Attribute;

    // // Pega o arquivo no último caractere
    // std::ofstream file ( file_path, std::ios::app | std::ios::ate );

    // if (!file.is_open())
    // {
    //     std::cerr << "ERRO AO ABRIR ARQUIVO: " << file_path
    //         << "! Durante salvamento de Consumable!\n";
    //     exit( EXIT_FAILURE );
    // }
    
    loaded_file_stream << "\n";

    loaded_file_stream << AttackParser::load_state_matches[ LoadState::ATTACK ] << "\n";

    loaded_file_stream
        << AttackParser::attribute_matches[ Attribute::NAME ]
        << "="
        << item.getName()
        << "\n";
    loaded_file_stream
        << AttackParser::attribute_matches[ Attribute::DISPLAY_MESSAGE ]
        << "="
        << item.getDisplayMessage()
        << "\n";
    loaded_file_stream
        << AttackParser::attribute_matches[ Attribute::STAMINA_COST_MODIFIER ]
        << "="
        << item.getStaminaCostModifier()
        << "\n";
    loaded_file_stream
        << AttackParser::attribute_matches[ Attribute::DAMAGE_MODIFIER ]
        << "="
        << item.getDamageModifier()
        << "\n";

    loaded_file_stream << AttackParser::load_state_matches[ LoadState::END_ATTACK ] << "\n";
}

/**
 * Parse the Consumable file and creates a new Consumable object.
 * Uses the static maps and associated enums to do so.
 * This is a line example "attribute=value", named "key=value"
 * for convenience.
 * @param input_stream Input stream for the file.
*/
Attack *AttackParser::parseFile( std::ifstream& input_stream )
{
    using Attribute = AttackParser::Attribute;
    using LoadState = AttackParser::LoadState;
    
    string entire_line, line_value, line_key;
    size_t equal_sign_index;

    Attack* new_attack = new Attack();

    while (true)
    {
        std::getline( input_stream, entire_line );

        // If [END_PLAYER], stop parsing.
        if (entire_line == AttackParser::load_state_matches[ LoadState::END_ATTACK ])
            break;

        equal_sign_index = entire_line.find( '=' );

        line_key     = entire_line.substr( 0, equal_sign_index );
        line_value   = entire_line.substr( equal_sign_index + 1, entire_line.size() );
                
        if (line_key == AttackParser::attribute_matches[ Attribute::NAME ])
        {
            new_attack->setName( line_value );
            continue;
        }

        if (line_key == AttackParser::attribute_matches[ Attribute::DISPLAY_MESSAGE ])
        {
            new_attack->setDisplayMessage( line_value );
            continue;
        }
        
        if (line_key == AttackParser::attribute_matches[ Attribute::STAMINA_COST_MODIFIER ])
        {
            new_attack->setStaminaCostModifier( std::stod( line_value ) );
            continue;
        }

        if (line_key == AttackParser::attribute_matches[ Attribute::DAMAGE_MODIFIER ])
        {
            new_attack->setDamageModifier( std::stod( line_value ) );
            continue;
        }

    }
    return new_attack;
}
