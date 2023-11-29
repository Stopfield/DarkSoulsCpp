
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
#include "AttackParser.h"
#include "PlayerParser.h"
#include "EnemyParser.h"

#include "NormalBattle.h"
#include "BossBattle.h"

int main()
{
    /* Normal Battle - Demonstração */
    Weapon espada_branca("Espada Branca", 15.5f, 150);
    Weapon lanca_da_lua("Lança da Lua", 10.25f, 250);

    string hero_file_path = "/home/thiago/new_dark_souls/Hero.sav";
    string enemy_file_path = "/home/thiago/new_dark_souls/Enemy.sav";
    std::ifstream hero_load_stream  ( hero_file_path );
    std::ifstream enemy_load_stream ( enemy_file_path );

    Player* player_ptr = PlayerParser::loadFromStream( hero_load_stream );
    Enemy* enemy_ptr = EnemyParser::loadFromStream( enemy_load_stream );

    player_ptr->equipWeapon( lanca_da_lua );
    enemy_ptr->equipWeapon( espada_branca );

    std::cout << *player_ptr;
    std::cout << *enemy_ptr;

    NormalBattle batalha( *player_ptr, *enemy_ptr );

    batalha.begin_battle();

    // ====================================================
    /* Boss Battle - Demonstração */
    /* Carregando Armas */
    // string weapons_path = "/home/thiago/DarkSoulsCpp/src/Weapons";
    // std::ifstream stream_espada_branca  (weapons_path + "/EspadaBranca.sav" );
    // std::ifstream stream_lanca_da_lua   (weapons_path + "/LancaDaLua.sav"   );
    // std::ifstream stream_espeta_coracao (weapons_path + "/EspetaCoracao.sav");
    // std::ifstream stream_luz_ardente    (weapons_path + "/LuzArdente.sav"   );


    // Weapon* espada_branca_ptr   = WeaponParser::loadFromStream  ( stream_espada_branca  );
    // Weapon* lanca_da_lua_ptr   = WeaponParser::loadFromStream   ( stream_lanca_da_lua   );
    // Weapon* espeta_coracao_ptr  = WeaponParser::loadFromStream  ( stream_espeta_coracao );
    // Weapon* luz_ardente_ptr     = WeaponParser::loadFromStream  ( stream_luz_ardente    );

    // std::cout << *espada_branca_ptr << std::endl;

    // /* Ataques */
    // string attacks_path = "/home/thiago/DarkSoulsCpp/src/Attacks";
    // std::ifstream stream_giro_atomico   (attacks_path + "/GiroAtomico.sav" );
    // std::ifstream stream_ataque_largo   (attacks_path + "/AtaqueLargo.sav"  );
    // std::ifstream stream_estocada       (attacks_path + "/Estocada.sav"     );
    // std::ifstream stream_queda_da_lua   (attacks_path + "/QuedaDaLua.sav"   );

    // Attack* giro_atomico_ptr    = AttackParser::loadFromStream( stream_giro_atomico );
    // Attack* ataque_largo_ptr    = AttackParser::loadFromStream( stream_ataque_largo );
    // Attack* estocada_ptr        = AttackParser::loadFromStream( stream_estocada     );
    // Attack* queda_da_lua_ptr    = AttackParser::loadFromStream( stream_queda_da_lua );

    // /* Já demonstramos anteriormente o carregamento de entidades */
    // Player thiago("Thiago");
    // thiago.equipWeapon( *espada_branca_ptr );
    // thiago.setMaxHealth( 500.0f );
    // thiago.heal( 500.0f );

    // thiago.addAttack( *giro_atomico_ptr );
    // thiago.addAttack( *ataque_largo_ptr );
    // thiago.addAttack( *estocada_ptr     );

    // /* Primeira fase */
    // Enemy cavaleiro_negro("Cavaleiro Negro");
    // cavaleiro_negro.equipWeapon( *espeta_coracao_ptr );
    // cavaleiro_negro.addAttackAndProbability( ataque_largo_ptr, 50 );
    // cavaleiro_negro.addAttackAndProbability( giro_atomico_ptr, 2 );
    // cavaleiro_negro.addAttackAndProbability( estocada_ptr,     80 );

    // /* Segunda fase */
    // Enemy cavaleiro_negro_alado("Cavaleiro Negro Alado");
    // cavaleiro_negro_alado.equipWeapon( *luz_ardente_ptr );
    // cavaleiro_negro_alado.addAttackAndProbability( queda_da_lua_ptr, 5  );
    // cavaleiro_negro_alado.addAttackAndProbability( giro_atomico_ptr, 2  );
    // cavaleiro_negro_alado.addAttackAndProbability( ataque_largo_ptr, 50 );


    // BossBattle batalha_com_cavaleiro_negro( thiago );
    // batalha_com_cavaleiro_negro.add_phase( cavaleiro_negro );       // Primeira fase
    // batalha_com_cavaleiro_negro.add_phase( cavaleiro_negro_alado ); // Segunda fase

    // batalha_com_cavaleiro_negro.begin_battle();

    // /* Deletes */
    // delete espada_branca_ptr;
    // delete lanca_da_lua_ptr;
    // delete espeta_coracao_ptr;
    // delete luz_ardente_ptr;

    // delete giro_atomico_ptr;
    // delete ataque_largo_ptr;
    // delete estocada_ptr;
    // delete queda_da_lua_ptr;
    
    return 0;
}