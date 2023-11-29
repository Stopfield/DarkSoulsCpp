#include "EntityParser.h"

enum class EntityParser::LoadState
{
    ENTITY,
    ENTITY_INVENTORY, ENTITY_BODY_PART,
    END_ENTITY
};

enum class EntityParser::Attribute
{
    NAME,
    MAX_HEALTH, HEALTH,
    STAMINA, STRENGTH, DEXTERITY,
    REPRESENTATION,
    POSITION_X, POSITION_Y
};

map< EntityParser::LoadState, string > EntityParser::load_state_matches = {
    { EntityParser::LoadState::ENTITY,              "[ENTITY]"              },
    { EntityParser::LoadState::ENTITY_INVENTORY,    "[ENTITY_INVENTORY]"    },
    { EntityParser::LoadState::ENTITY_BODY_PART,    "[ENTITY_BODY_PART]"    },
    { EntityParser::LoadState::END_ENTITY,          "[END_ENTITY]"          }
};

map< EntityParser::Attribute, string > EntityParser::attribute_matches = {
    { EntityParser::Attribute::NAME,            "name"              },
    { EntityParser::Attribute::MAX_HEALTH,      "max_health"        },
    { EntityParser::Attribute::HEALTH,          "health"            },
    { EntityParser::Attribute::STAMINA,         "stamina"           },
    { EntityParser::Attribute::STRENGTH,        "strength"          },
    { EntityParser::Attribute::DEXTERITY,       "dexterity"         },
    { EntityParser::Attribute::REPRESENTATION,  "representation"    },
    { EntityParser::Attribute::POSITION_X,      "position_x"        },
    { EntityParser::Attribute::POSITION_Y,      "position_y"        }
};

/**
 * Verifica se o arquivo especificado na stream é um
 * Consumable, verificando a primeira linha, que deve ser [CONSUMABLE].
 * Se for, ele tentará dar parse, senão ele retorna nullptr.
 * @param loaded_file_stream Input stream do arquivo já carregado.
*/
Entity* EntityParser::loadFromStream( std::ifstream& loaded_file_stream )
{
    // Parse player file
    string first_line;

    loaded_file_stream >> first_line;

    if ( first_line == EntityParser::load_state_matches[ LoadState::ENTITY ])
        return EntityParser::parseFile( loaded_file_stream );
        
    return nullptr;
}

/**
 * Escreve um item consumable em um output stream já definido!
 * Preste atenção! Se você definir um ofstream no início de um
 * arquivo, ele será sobrescrito!
 * @param item                  Item a ser escrito
 * @param loaded_file_stream    Output stream de um arquivo
*/
void EntityParser::saveInStream(Entity& entity, std::ofstream& loaded_file_stream)
{
    using LoadState = EntityParser::LoadState;
    using Attribute = EntityParser::Attribute;

    // // Pega o arquivo no último caractere
    // std::ofstream file ( file_path, std::ios::app | std::ios::ate );

    loaded_file_stream << "\n";

    loaded_file_stream << EntityParser::load_state_matches[ LoadState::ENTITY ] << "\n";
    
    /* name */
    loaded_file_stream
        << EntityParser::attribute_matches[ Attribute::NAME ]
        << "="
        << entity.getName()
        << "\n";
    /* max_health */
    loaded_file_stream
        << EntityParser::attribute_matches[ Attribute::MAX_HEALTH ]
        << "="
        << entity.getMaxHealth()
        << "\n";
    /* health */
    loaded_file_stream
        << EntityParser::attribute_matches[ Attribute::HEALTH ]
        << "="
        << entity.getHealth()
        << "\n";
    /* stamina */
    loaded_file_stream
        << EntityParser::attribute_matches[ Attribute::STAMINA ]
        << "="
        << entity.getStamina()
        << "\n";
    /* strength */
    loaded_file_stream
        << EntityParser::attribute_matches[ Attribute::STRENGTH ]
        << "="
        << entity.getStrength()
        << "\n";
    /* dexterity */
    loaded_file_stream
        << EntityParser::attribute_matches[ Attribute::DEXTERITY ]
        << "="
        << entity.getDexterity()
        << "\n";
    /* stamina */
    loaded_file_stream
        << EntityParser::attribute_matches[ Attribute::REPRESENTATION ]
        << "="
        << entity.getRepresentation()
        << "\n";
    /* position_x */    
    loaded_file_stream
        << EntityParser::attribute_matches[ Attribute::POSITION_X ]
        << "="
        << entity.getPosition().x
        << "\n";
    /* position_y */    
    loaded_file_stream
        << EntityParser::attribute_matches[ Attribute::POSITION_Y ]
        << "="
        << entity.getPosition().y
        << "\n";

    loaded_file_stream << EntityParser::load_state_matches[ LoadState::ENTITY_INVENTORY ] << "\n";
    
    InventoryParser::saveInStream( &entity.getInventory(), loaded_file_stream );

    for ( auto& body_part : entity.getBodyParts() )
    {
        loaded_file_stream
            << EntityParser::load_state_matches[ LoadState::ENTITY_BODY_PART ]
            << "\n";
        BodyPartsParser::saveInStream( body_part, loaded_file_stream );
    }

    loaded_file_stream << EntityParser::load_state_matches[ LoadState::END_ENTITY ] << "\n";
    
    loaded_file_stream << "\n";

}

/**
 * Parse the Consumable file and creates a new Consumable object.
 * Uses the static maps and associated enums to do so.
 * This is a line example "attribute=value", named "key=value"
 * for convenience.
 * @param input_stream Input stream for the file.
*/
Entity* EntityParser::parseFile( std::ifstream& input_stream )
{
    using Attribute = EntityParser::Attribute;
    using LoadState = EntityParser::LoadState;
    
    string entire_line, line_value, line_key;
    size_t equal_sign_index;

    Vector2D*   new_position_ptr    = 0;
    Entity*     new_entity_ptr      = new Entity();

    vector<BodyPart>    entity_body_parts;
    BodyPart*           new_part_ptr;

    while (true)
    {
        std::getline( input_stream, entire_line );

        // If [END_PLAYER], stop parsing.
        if (entire_line == EntityParser::load_state_matches[ LoadState::END_ENTITY ])
            break;

        equal_sign_index = entire_line.find( '=' );

        line_key     = entire_line.substr( 0, equal_sign_index );
        line_value   = entire_line.substr( equal_sign_index + 1, entire_line.size() );

        /* Name Parsing */               
        if (line_key == EntityParser::attribute_matches[ Attribute::NAME ])
        {
            new_entity_ptr->setName( line_value );
            continue;
        }

        /* Max_health Parsing */               
        if (line_key == EntityParser::attribute_matches[ Attribute::MAX_HEALTH ])
        {
            new_entity_ptr->setMaxHealth( std::stod( line_value ) );
            continue;
        }

        /* Health Parsing */               
        if (line_key == EntityParser::attribute_matches[ Attribute::HEALTH ])
        {
            new_entity_ptr->setHealth( std::stod( line_value ) );
            continue;
        }

        /* Stamina Parsing */               
        if (line_key == EntityParser::attribute_matches[ Attribute::STAMINA ])
        {
            new_entity_ptr->setStamina( std::stod( line_value ) );
            continue;
        }

        /* Strength Parsing */               
        if (line_key == EntityParser::attribute_matches[ Attribute::STRENGTH ])
        {
            new_entity_ptr->setStrength( std::stod( line_value ) );
            continue;
        }

        /* Dexterity Parsing */               
        if (line_key == EntityParser::attribute_matches[ Attribute::DEXTERITY ])
        {
            new_entity_ptr->setDexterity( std::stod( line_value ) );
            continue;
        }

        /* Representation Parsing */               
        if (line_key == EntityParser::attribute_matches[ Attribute::REPRESENTATION ])
        {
            new_entity_ptr->setRepresentation( line_value[0] );
            continue;
        }

        /* Position X Parsing */               
        if (line_key == EntityParser::attribute_matches[ Attribute::POSITION_X ])
        {
            if (new_position_ptr == 0)
            {
                new_position_ptr = new Vector2D { 0 };
            }
            new_position_ptr->x = std::stoi( line_value );
            continue;
        }

        /* Position X Parsing */               
        if (line_key == EntityParser::attribute_matches[ Attribute::POSITION_Y ])
        {
            if (new_position_ptr == 0)
                new_position_ptr = new Vector2D { 0 };
            new_position_ptr->y = std::stoi( line_value );
            continue;
        }

        /* Inventory Parsing */
        if (line_key == EntityParser::load_state_matches[ LoadState::ENTITY_INVENTORY ])
        {
            new_entity_ptr->setInventory( InventoryParser::loadFromStream( input_stream ) );
            continue;
        }

        /* Body Parts Parsing */
        if (line_key == EntityParser::load_state_matches[ LoadState::ENTITY_BODY_PART ])
        {
            new_part_ptr = BodyPartsParser::loadFromStream( input_stream );
            entity_body_parts.push_back( *new_part_ptr );
            new_part_ptr = 0;
            continue;
        }
    }

    /* Se houver alguma posição, set e delete o ponteiro */
    if (new_position_ptr != 0)
    {
        new_entity_ptr->setPosition( *new_position_ptr );
        delete new_position_ptr;
    }

    /* Sempre precisa haver partes*/
    if (new_part_ptr != nullptr)
        delete new_part_ptr;

    new_entity_ptr->setBodyParts( entity_body_parts );

    return new_entity_ptr;
}
