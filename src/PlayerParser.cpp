#include "PlayerParser.h"

enum class PlayerParser::LoadState
{
    PLAYER,
    PLAYER_ENTITY, PLAYER_ATTACK,
    END_PLAYER
};

enum class PlayerParser::Attribute
{
    NAME
};

map< PlayerParser::LoadState, string > PlayerParser::load_state_matches = {
    { PlayerParser::LoadState::PLAYER,              "[PLAYER]"              },
    { PlayerParser::LoadState::PLAYER_ENTITY,       "[PLAYER_ENTITY]"    },
    { PlayerParser::LoadState::PLAYER_ATTACK,       "[PLAYER_ATTACK]"    },
    { PlayerParser::LoadState::END_PLAYER,          "[END_PLAYER]"          }
};

map< PlayerParser::Attribute, string > PlayerParser::attribute_matches = {
    { PlayerParser::Attribute::NAME,            "name"              }
};

/**
 * Verifica se o arquivo especificado na stream é um
 * Consumable, verificando a primeira linha, que deve ser [CONSUMABLE].
 * Se for, ele tentará dar parse, senão ele retorna nullptr.
 * @param loaded_file_stream Input stream do arquivo já carregado.
*/
Player* PlayerParser::loadFromStream( std::ifstream& loaded_file_stream )
{
    // Parse player file
    string first_line;

    loaded_file_stream >> first_line;

    if ( first_line == PlayerParser::load_state_matches[ LoadState::PLAYER ])
        return PlayerParser::parseFile( loaded_file_stream );
        
    return nullptr;
}

/**
 * Escreve um item consumable em um output stream já definido!
 * Preste atenção! Se você definir um ofstream no início de um
 * arquivo, ele será sobrescrito!
 * @param item                  Item a ser escrito
 * @param loaded_file_stream    Output stream de um arquivo
*/
void PlayerParser::saveInStream(Player& entity, std::ofstream& loaded_file_stream)
{
    using LoadState = PlayerParser::LoadState;
    using Attribute = PlayerParser::Attribute;

    // // Pega o arquivo no último caractere
    // std::ofstream file ( file_path, std::ios::app | std::ios::ate );

    loaded_file_stream << "\n";

    loaded_file_stream << PlayerParser::load_state_matches[ LoadState::PLAYER ] << "\n";

    loaded_file_stream << PlayerParser::load_state_matches[ LoadState::PLAYER_ENTITY ] << "\n";
    EntityParser::saveInStream( entity, loaded_file_stream );
    
    for ( auto& attack : entity.getAttacks() )
    {
        loaded_file_stream
            << PlayerParser::load_state_matches[ LoadState::PLAYER_ATTACK ]
            << "\n";
        AttackParser::saveInStream( *attack, loaded_file_stream );
    }

    loaded_file_stream << PlayerParser::load_state_matches[ LoadState::END_PLAYER ] << "\n";
    
    loaded_file_stream << "\n";

}

/**
 * Parse the Consumable file and creates a new Consumable object.
 * Uses the static maps and associated enums to do so.
 * This is a line example "attribute=value", named "key=value"
 * for convenience.
 * @param input_stream Input stream for the file.
*/
Player* PlayerParser::parseFile( std::ifstream& input_stream )
{
    using Attribute = PlayerParser::Attribute;
    using LoadState = PlayerParser::LoadState;
    
    string entire_line, line_value, line_key;
    size_t equal_sign_index;

    Vector2D*   new_position_ptr    = 0;
    Player*     new_player_ptr      = new Player();

    Attack*           new_attack_ptr;

    while (true)
    {
        std::getline( input_stream, entire_line );

        // If [END_PLAYER], stop parsing.
        if (entire_line == PlayerParser::load_state_matches[ LoadState::END_PLAYER ])
            break;

        equal_sign_index = entire_line.find( '=' );

        line_key     = entire_line.substr( 0, equal_sign_index );
        line_value   = entire_line.substr( equal_sign_index + 1, entire_line.size() );

        /* Entity Parsing */
        if (line_key == PlayerParser::load_state_matches[ LoadState::PLAYER_ENTITY ])
        {
            Entity* entity = (EntityParser::loadFromStream( input_stream ));

            new_player_ptr->setName( entity->getName() );
            new_player_ptr->setMaxHealth( entity->getMaxHealth() );
            new_player_ptr->setHealth( entity->getHealth() );
            new_player_ptr->setStrength( entity->getStrength() );
            new_player_ptr->setStamina( entity->getStamina() );
            new_player_ptr->setDexterity( entity->getDexterity() );
            new_player_ptr->setInventory( &entity->getInventory() );
            new_player_ptr->setBodyParts(  entity->getBodyParts() );

            delete entity;
            entity = 0;
            
            continue;
        }

        /* Attacks Parsing */
        if (line_key == PlayerParser::load_state_matches[ LoadState::PLAYER_ATTACK ])
        {
            new_attack_ptr = AttackParser::loadFromStream( input_stream );
            new_player_ptr->addAttack( *new_attack_ptr );
            delete new_attack_ptr;
            new_attack_ptr = 0;
            continue;
        }
    }

    /* Sempre precisa haver partes*/
    if (new_attack_ptr != nullptr)
        delete new_attack_ptr;

    return new_player_ptr;
}
