#include "WeaponParser.h"

enum class WeaponParser::LoadState
{
    WEAPON, END_WEAPON
};

enum class WeaponParser::Attribute
{
    DAMAGE, MIN_STRENGTH, MIN_DEXTERITY, DURABILITY,
    NAME, DESCRIPTION,
    BEFORE, AFTER
};

map< WeaponParser::LoadState, string > WeaponParser::load_state_matches = {
    { WeaponParser::LoadState::WEAPON,      "[WEAPON]"      },
    { WeaponParser::LoadState::END_WEAPON,  "[END_WEAPON]"  }
};

map< WeaponParser::Attribute, string > WeaponParser::attribute_matches = {
    { WeaponParser::Attribute::DAMAGE,          "damage"            },
    { WeaponParser::Attribute::MIN_STRENGTH,    "min_strength"      },
    { WeaponParser::Attribute::MIN_DEXTERITY,   "min_dexterity"     },
    { WeaponParser::Attribute::DURABILITY,      "durability"        },
    { WeaponParser::Attribute::NAME,            "name"              },
    { WeaponParser::Attribute::DESCRIPTION,     "description"       },
    { WeaponParser::Attribute::BEFORE,          "before"            },
    { WeaponParser::Attribute::AFTER,           "after"             }
};

/**
 * Verifica se o arquivo especificado na stream é um
 * Consumable, verificando a primeira linha, que deve ser [CONSUMABLE].
 * Se for, ele tentará dar parse, senão ele retorna nullptr.
 * @param loaded_file_stream Input stream do arquivo já carregado.
*/
Weapon* WeaponParser::loadFromStream( std::ifstream& loaded_file_stream )
{
    // Parse player file
    string first_line;

    loaded_file_stream >> first_line;

    if ( first_line == WeaponParser::load_state_matches[ LoadState::WEAPON ])
        return WeaponParser::parseFile( loaded_file_stream );
    
    return nullptr;
}

/**
 * Escreve um item consumable em um output stream já definido!
 * Preste atenção! Se você definir um ofstream no início de um
 * arquivo, ele será sobrescrito!
 * @param item                  Item a ser escrito
 * @param loaded_file_stream    Output stream de um arquivo
*/
void WeaponParser::saveInStream(Weapon& item, std::ofstream& loaded_file_stream)
{
    using LoadState = WeaponParser::LoadState;
    using Attribute = WeaponParser::Attribute;

    // // Pega o arquivo no último caractere
    // std::ofstream file ( file_path, std::ios::app | std::ios::ate );

    // if (!file.is_open())
    // {
    //     std::cerr << "ERRO AO ABRIR ARQUIVO: " << file_path
    //         << "! Durante salvamento de Consumable!\n";
    //     exit( EXIT_FAILURE );
    // }
    
    loaded_file_stream << "\n";

    loaded_file_stream << WeaponParser::load_state_matches[ LoadState::WEAPON ] << "\n";

    loaded_file_stream
        << WeaponParser::attribute_matches[ Attribute::NAME ]
        << "="
        << item.getName()
        << "\n";
    loaded_file_stream
        << WeaponParser::attribute_matches[ Attribute::DESCRIPTION ]
        << "="
        << item.getDescription()
        << "\n";
    loaded_file_stream
        << WeaponParser::attribute_matches[ Attribute::DAMAGE ]
        << "="
        << item.getDamage()
        << "\n";
    loaded_file_stream
        << WeaponParser::attribute_matches[ Attribute::DURABILITY ]
        << "="
        << item.getDamage()
        << "\n";

    loaded_file_stream << WeaponParser::load_state_matches[ LoadState::END_WEAPON ] << "\n";
}

/**
 * Parse the Consumable file and creates a new Consumable object.
 * Uses the static maps and associated enums to do so.
 * This is a line example "attribute=value", named "key=value"
 * for convenience.
 * @param input_stream Input stream for the file.
*/
Weapon *WeaponParser::parseFile( std::ifstream& input_stream )
{
    // using Attribute = WeaponParser::Attribute;
    // using LoadState = WeaponParser::LoadState;
    
    // string entire_line, line_value, line_key;
    // size_t equal_sign_index;

    // Weapon* new_weapon = new Weapon();

    // while (true)
    // {
    //     std::getline( input_stream, entire_line );

    //     // If [END_PLAYER], stop parsing.
    //     if (entire_line == WeaponParser::load_state_matches[ LoadState::END_WEAPON ])
    //         break;

    //     equal_sign_index = entire_line.find( '=' );

    //     line_key     = entire_line.substr( 0, equal_sign_index );
    //     line_value   = entire_line.substr( equal_sign_index + 1, entire_line.size() );
                
    //     if (line_key == WeaponParser::attribute_matches[ Attribute::NAME ])
    //     {
    //         new_weapon->setName( line_value );
    //         continue;
    //     }

    //     if (line_key == WeaponParser::attribute_matches[ Attribute::DESCRIPTION ])
    //     {
    //         new_weapon->setDescription( line_value );
    //         continue;
    //     }

    //     if (line_key == WeaponParser::attribute_matches[ Attribute::DAMAGE ])
    //     {
    //         new_weapon->setDamage( stod( line_value ) );
    //         continue;
    //     }

    //     if (line_key == WeaponParser::attribute_matches[ Attribute::DURABILITY ])
    //     {
    //         new_weapon->setDurability( stod( line_value ) );
    //         continue;
    //     }
    // }
    // return new_weapon;
    return 0;
}
