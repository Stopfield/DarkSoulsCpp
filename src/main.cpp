
#include <iostream>

#include "Weapon.h"
#include "Armor.h"
#include "Entity.h"
#include "Consumable.h"
#include "Attack.h"
#include "Player.h"
#include "Enemy.h"

#include "ConsumableParser.h"
#include "WeaponParser.h"
#include "ArmorParser.h"
#include "InventoryParser.h"
#include "EntityParser.h"
#include "BodyPartsParser.h"

int main()
{
    // Consumable* estus_flask;

    // estus_flask = ConsumableParser::loadFromStream( "/home/thiago/new_dark_souls/Consumable.sav" );

    // if (!estus_flask)
    //     std::cerr << "ERROR LOADING";

    // std::cout << estus_flask->getHealthFactor() << "\n";
    // std::cout << estus_flask->getRepresentation();

    // string file_path = "/home/thiago/new_dark_souls/Consumable.sav";
    // Carregamento
    // std::ifstream loadedFile ( file_path );

    // Consumable* estus_flask;
    // Consumable* teste;
    // Consumable* bomba;
    // estus_flask = ConsumableParser::loadFromStream( loadedFile );
    // teste = ConsumableParser::loadFromStream( loadedFile );
    // bomba = ConsumableParser::loadFromStream( loadedFile );

    // std::cout << *estus_flask << "\n";
    // std::cout << *teste << "\n";
    // std::cout << *bomba << "\n";

    // Consumable item("Qualquer texto", "Descrição");

    // std::ofstream loaded_file_stream ( file_path );
    // ConsumableParser::saveInStream( item, loaded_file_stream );
    
    // /* Carregamento */
    // string file_path = "/home/thiago/new_dark_souls/Weapons.sav";
    // std::ifstream loadedFile ( file_path );

    // Weapon weapon_to_save;

    // Weapon* new_weapon;
    // new_weapon = WeaponParser::loadFromStream( loadedFile );
    // /* Carregamento */


    // /* Salvamento */
    // string file_path = "/home/thiago/new_dark_souls/Weapons.sav";
    // std::ofstream loadedFile ( file_path );

    // Weapon weapon_to_save;

    // WeaponParser::saveInStream( weapon_to_save, loadedFile );
    // /* Salvamento */

    // string file_path = "/home/thiago/new_dark_souls/Armors.sav";
    // std::ifstream loadedFile ( file_path );

    // Armor* new_armor;
    // new_armor = ArmorParser::loadFromStream( loadedFile );

    // std::cout << *new_armor;

    // delete new_armor;

    /* Inventory demonstration */
    // Entity thiago;
    // thiago.showInventory();

    // vector< InventoryItem* >* inventory_ptr;

    // string file_path = "/home/thiago/new_dark_souls/Inventory.sav";
    // std::ifstream loaded_file (file_path);
    // inventory_ptr = InventoryParser::loadFromStream( loaded_file );

    // thiago.setInventory( inventory_ptr );

    // thiago.showInventory();

    // for (auto& i : *inventory_ptr)
    // {
    //     std::cout << i->quantity << "\n";
    // }

    // // std::cout << *inventory_ptr->at(3)->item;

    /* Body Part parser*/
    // string file_path = "/home/thiago/new_dark_souls/BodyPart.sav";

    // Leitura
    // std::ifstream loaded_file (file_path);
    // BodyPart* part = BodyPartsParser::loadFromStream( loaded_file );

    // std::cout << part->partDescription << " : " << part->damageModifier << "\n";
    
    // Salvamento
    // std::ofstream loaded_file (file_path);
    // BodyPart parte_nova { "HEAD", 10.0 };
    // BodyPartsParser::saveInStream( parte_nova, loaded_file );

    // /* Salvamento Inventário */
    // string save_file_path = "/home/thiago/new_dark_souls/InventoryNew.sav";
    // string file_path = "/home/thiago/new_dark_souls/Inventory.sav";
    // std::ofstream save_file     (save_file_path);
    // std::ifstream loaded_file   (file_path);

    // vector< InventoryItem* >* inventory_ptr;

    // inventory_ptr = InventoryParser::loadFromStream( loaded_file );
    
    // InventoryParser::saveInStream( inventory_ptr, save_file );


    /* Entity Parser */
    string load_file_path = "/home/thiago/new_dark_souls/Entity.sav";
    string save_file_path = "/home/thiago/new_dark_souls/EntityNew.sav";
    std::ifstream load_file_stream (load_file_path);
    std::ofstream save_file_stream (save_file_path);

    Entity* thiago = EntityParser::loadFromStream( load_file_stream );
    EntityParser::saveInStream( *thiago, save_file_stream );

    std::cout << (*thiago) << "\n";
    delete thiago;

    return 0;
}