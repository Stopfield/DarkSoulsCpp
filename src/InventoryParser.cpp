#include "InventoryParser.h"

enum class InventoryParser::LoadState
{
    INVENTORY,
    INVENTORY_ARMOR, INVENTORY_WEAPON, INVENTORY_CONSUMABLE,
    END_INVENTORY
};

enum class InventoryParser::Attribute
{
    SIZE
};

map< InventoryParser::LoadState, string > InventoryParser::load_state_matches = {
    { InventoryParser::LoadState::INVENTORY,            "[INVENTORY]"               },
    { InventoryParser::LoadState::INVENTORY_ARMOR,      "[INVENTORY_ARMOR]"         },
    { InventoryParser::LoadState::INVENTORY_WEAPON,     "[INVENTORY_WEAPON]"        },
    { InventoryParser::LoadState::INVENTORY_CONSUMABLE, "[INVENTORY_CONSUMABLE]"    },
    { InventoryParser::LoadState::END_INVENTORY,        "[END_INVENTORY]"           }
};

map< InventoryParser::Attribute, string > InventoryParser::attribute_matches = {
    { InventoryParser::Attribute::SIZE,  "size"    }
};

/**
 * Verifica se o arquivo especificado na stream é um
 * Consumable, verificando a primeira linha, que deve ser [CONSUMABLE].
 * Se for, ele tentará dar parse, senão ele retorna nullptr.
 * @param loaded_file_stream Input stream do arquivo já carregado.
*/
vector<InventoryItem*>* InventoryParser::loadFromStream( std::ifstream& loaded_file_stream )
{
    // Parse player file
    string first_line;

    loaded_file_stream >> first_line;

    if ( first_line == InventoryParser::load_state_matches[ LoadState::INVENTORY ])
        return InventoryParser::parseFile( loaded_file_stream );
        
    return nullptr;
}

/**
 * Escreve um item consumable em um output stream já definido!
 * Preste atenção! Se você definir um ofstream no início de um
 * arquivo, ele será sobrescrito!
 * @param item                  Item a ser escrito
 * @param loaded_file_stream    Output stream de um arquivo
*/
void InventoryParser::saveInStream(const vector<InventoryItem*>* inventory, std::ofstream& loaded_file_stream)
{
    using LoadState = InventoryParser::LoadState;
    using Attribute = InventoryParser::Attribute;

    // // Pega o arquivo no último caractere
    // std::ofstream file ( file_path, std::ios::app | std::ios::ate );

    loaded_file_stream << "\n";

    loaded_file_stream << InventoryParser::load_state_matches[ LoadState::INVENTORY ] << "\n";

    for ( auto& inventory_item : *inventory )
    {
        /* Is item a Consumable? */
        Consumable* consumable_ptr = dynamic_cast<Consumable*> ( inventory_item->item );
        if (consumable_ptr != nullptr)
        {
            /* [INVENTORY_CONSUMABLE]*/
            loaded_file_stream
                << InventoryParser::load_state_matches[ LoadState::INVENTORY_CONSUMABLE ]
                << "\n";

            /* Quantity */
            loaded_file_stream
                << inventory_item->quantity
                << "\n";
            
            ConsumableParser::saveInStream( *consumable_ptr, loaded_file_stream );
            continue;
        }

        /* Is item a Weapon? */
        Weapon* weapon_ptr = dynamic_cast<Weapon*> ( inventory_item->item );
        if (weapon_ptr != nullptr)
        {
            /* [INVENTORY_WEAPON]*/
            loaded_file_stream
                << InventoryParser::load_state_matches[ LoadState::INVENTORY_WEAPON ]
                << "\n";

            /* Quantity */
            loaded_file_stream
                << inventory_item->quantity
                << "\n";
            
            WeaponParser::saveInStream( *weapon_ptr, loaded_file_stream );
        }

        /* Is item an Armor? */
        Armor* armor_ptr = dynamic_cast<Armor*> ( inventory_item->item );
        if (armor_ptr != nullptr)
        {
            /* [INVENTORY_ARMOR]*/
            loaded_file_stream
                << InventoryParser::load_state_matches[ LoadState::INVENTORY_ARMOR ]
                << "\n";

            /* Quantity */
            loaded_file_stream
                << inventory_item->quantity
                << "\n";
            
            ArmorParser::saveInStream( *armor_ptr, loaded_file_stream );
        }
    }

    loaded_file_stream << InventoryParser::load_state_matches[ LoadState::END_INVENTORY ] << "\n";
    
    loaded_file_stream << "\n";

}

/**
 * Parse the Consumable file and creates a new Consumable object.
 * Uses the static maps and associated enums to do so.
 * This is a line example "attribute=value", named "key=value"
 * for convenience.
 * @param input_stream Input stream for the file.
*/
vector<InventoryItem*>* InventoryParser::parseFile( std::ifstream& input_stream )
{
    using Attribute = InventoryParser::Attribute;
    using LoadState = InventoryParser::LoadState;
    
    string entire_line, line_value, line_key;
    size_t equal_sign_index;

    vector<InventoryItem*>* new_inventory_ptr = new vector<InventoryItem*>;

    while (true)
    {
        std::getline( input_stream, entire_line );

        // If [END_PLAYER], stop parsing.
        if (entire_line == InventoryParser::load_state_matches[ LoadState::END_INVENTORY ])
            break;

        equal_sign_index = entire_line.find( '=' );

        line_key     = entire_line.substr( 0, equal_sign_index );
        line_value   = entire_line.substr( equal_sign_index + 1, entire_line.size() );

        /* Consumable Parsing */
        if (entire_line == InventoryParser::load_state_matches[ LoadState::INVENTORY_CONSUMABLE ])
        {
            string quantity;
            std::getline( input_stream, quantity );

            Consumable* new_consumable_ptr = ConsumableParser::loadFromStream( input_stream );
            
            InventoryItem* new_item_ptr = new InventoryItem {
                new_consumable_ptr, static_cast<short> ( std::stoi( quantity ) )
            };
            new_inventory_ptr->push_back( new_item_ptr );
            continue;
        }

        /* Weapon Parsing */
        if (entire_line == InventoryParser::load_state_matches[ LoadState::INVENTORY_WEAPON ])
        {
            string quantity;
            std::getline( input_stream, quantity );
            Weapon* new_weapon_ptr = WeaponParser::loadFromStream( input_stream );
            
            InventoryItem* new_item_ptr = new InventoryItem {
                new_weapon_ptr, static_cast<short> ( std::stoi( quantity ) )
            };
            new_inventory_ptr->push_back( new_item_ptr );
            continue;
        }

        /* Armor Parsing */
        if (entire_line == InventoryParser::load_state_matches[ LoadState::INVENTORY_ARMOR ])
        {
            string quantity;
            std::getline( input_stream, quantity );
            Armor* new_armor_ptr = ArmorParser::loadFromStream( input_stream );
            
            InventoryItem* new_item = new InventoryItem {
                new_armor_ptr, static_cast<short> ( std::stoi( quantity ) )
            };
            new_inventory_ptr->push_back( new_item );
            continue;
        }
        
    }
    return new_inventory_ptr;
}
