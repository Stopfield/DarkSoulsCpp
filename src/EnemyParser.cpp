#include "EnemyParser.h"

enum class EnemyParser::LoadState
{
    ENEMY,
    ENEMY_ENTITY, ENEMY_ATTACK,
    END_ENEMY
};

enum class EnemyParser::Attribute
{
    PROBABILITY
};

map< EnemyParser::LoadState, string > EnemyParser::load_state_matches = {
    { EnemyParser::LoadState::ENEMY,              "[ENEMY]"              },
    { EnemyParser::LoadState::ENEMY_ENTITY,       "[ENEMY_ENTITY]"    },
    { EnemyParser::LoadState::ENEMY_ATTACK,       "[ENEMY_ATTACK]"    },
    { EnemyParser::LoadState::END_ENEMY,          "[END_ENEMY]"          }
};

map< EnemyParser::Attribute, string > EnemyParser::attribute_matches = {
    { EnemyParser::Attribute::PROBABILITY,            "probability"              }
};

/**
 * Verifica se o arquivo especificado na stream é um
 * Consumable, verificando a primeira linha, que deve ser [CONSUMABLE].
 * Se for, ele tentará dar parse, senão ele retorna nullptr.
 * @param loaded_file_stream Input stream do arquivo já carregado.
*/
Enemy* EnemyParser::loadFromStream( std::ifstream& loaded_file_stream )
{
    // Parse player file
    string first_line;

    loaded_file_stream >> first_line;

    std::cout << first_line;

    if ( first_line == EnemyParser::load_state_matches[ LoadState::ENEMY ])
        return EnemyParser::parseFile( loaded_file_stream );
        
    return nullptr;
}

/**
 * Escreve um item consumable em um output stream já definido!
 * Preste atenção! Se você definir um ofstream no início de um
 * arquivo, ele será sobrescrito!
 * @param item                  Item a ser escrito
 * @param loaded_file_stream    Output stream de um arquivo
*/
void EnemyParser::saveInStream(Enemy& entity, std::ofstream& loaded_file_stream)
{
    using LoadState = EnemyParser::LoadState;
    using Attribute = EnemyParser::Attribute;

    // // Pega o arquivo no último caractere
    // std::ofstream file ( file_path, std::ios::app | std::ios::ate );

    loaded_file_stream << "\n";

    loaded_file_stream << EnemyParser::load_state_matches[ LoadState::ENEMY ] << "\n";

    loaded_file_stream << EnemyParser::load_state_matches[ LoadState::ENEMY_ENTITY ] << "\n";
    EntityParser::saveInStream( entity, loaded_file_stream );
    
    for ( auto& probs_and_attacks : *entity.getAttacksAndProbabilities() )
    {
        loaded_file_stream
            << EnemyParser::load_state_matches[ LoadState::ENEMY_ATTACK ]
            << "\n";
        loaded_file_stream
            << EnemyParser::attribute_matches[ Attribute::PROBABILITY ]
            << "="
            << probs_and_attacks.first
            << "\n";
        AttackParser::saveInStream( *probs_and_attacks.second, loaded_file_stream );
    }

    loaded_file_stream << EnemyParser::load_state_matches[ LoadState::END_ENEMY ] << "\n";
    
    loaded_file_stream << "\n";

}

/**
 * Parse the Consumable file and creates a new Consumable object.
 * Uses the static maps and associated enums to do so.
 * This is a line example "attribute=value", named "key=value"
 * for convenience.
 * @param input_stream Input stream for the file.
*/
Enemy* EnemyParser::parseFile( std::ifstream& input_stream )
{
    using Attribute = EnemyParser::Attribute;
    using LoadState = EnemyParser::LoadState;
    
    string entire_line, line_value, line_key;
    size_t equal_sign_index;

    Vector2D*   new_position_ptr    = 0;
    Enemy*      new_enemy_ptr      = new Enemy();

    Attack*     new_attack_ptr;

    while (true)
    {
        std::getline( input_stream, entire_line );

        // If [END_PLAYER], stop parsing.
        if (entire_line == EnemyParser::load_state_matches[ LoadState::END_ENEMY ])
            break;

        equal_sign_index = entire_line.find( '=' );

        line_key     = entire_line.substr( 0, equal_sign_index );
        line_value   = entire_line.substr( equal_sign_index + 1, entire_line.size() );

        /* Entity Parsing */
        if (line_key == EnemyParser::load_state_matches[ LoadState::ENEMY_ENTITY ])
        {
            Entity* entity = (EntityParser::loadFromStream( input_stream ));

            new_enemy_ptr->setName( entity->getName() );
            new_enemy_ptr->setMaxHealth( entity->getMaxHealth() );
            new_enemy_ptr->setHealth( entity->getHealth() );
            new_enemy_ptr->setStrength( entity->getStrength() );
            new_enemy_ptr->setStamina( entity->getStamina() );
            new_enemy_ptr->setDexterity( entity->getDexterity() );
            new_enemy_ptr->setInventory( &entity->getInventory() );
            new_enemy_ptr->setBodyParts(  entity->getBodyParts() );

            delete entity;
            entity = 0;
            
            continue;
        }

        /* Attacks Parsing */
        if (line_key == EnemyParser::load_state_matches[ LoadState::ENEMY_ATTACK ])
        {
            string probability;
            getline( input_stream, probability );
            std::cout << "Probabilidade: " << probability << "\n";
            new_attack_ptr = AttackParser::loadFromStream( input_stream );

            new_enemy_ptr->addAttackAndProbability( new_attack_ptr, stoi( probability ) );

            delete new_attack_ptr;
            new_attack_ptr = 0;
            continue;
        }
    }

    /* Sempre precisa haver partes*/
    if (new_attack_ptr != nullptr)
        delete new_attack_ptr;

    return new_enemy_ptr;
}
