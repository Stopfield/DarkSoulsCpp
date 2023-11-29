
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
    // Weapon espada_branca("Espada Branca", 15.5f, 150);
    // Weapon lanca_da_lua("Lança da Lua", 10.25f, 250);
    // Weapon espeta_coracao("Espeta Coração", 25.25f, 150);
    // Weapon luz_ardente("Luz Ardente", 30.25f, 500);

    // Attack giro_atomico( "Giro Atômico", 0.8f, 100.0f, "gira loucamente até gerar uma explosão nuclear!");
    // Attack ataque_largo( "Ataque Largo", 0.5f, 0.25f, "ataca girando sua arma no ar!");
    // Attack estocada( "Estocada", 2.5f, 0.15f, "estoca com sua arma!");
    // Attack queda_da_lua( "Queda da Lua", 2.8f, 100.0f, "pula! É como se a lua estivesse caíndo do céu");

    // // vector<Attack> thiago_ataques;

    // Player thiago("Thiago");
    // thiago.equipWeapon( espada_branca );
    // thiago.setMaxHealth( 500.0f );
    // thiago.heal( 500.0f );

    // thiago.addAttack( giro_atomico );
    // thiago.addAttack( ataque_largo );
    // thiago.addAttack( estocada );
    
    // Enemy jonas("Jonas");
    // jonas.equipWeapon( lanca_da_lua );


    // jonas.addAttackAndProbability( &ataque_largo, 25 );
    // jonas.addAttackAndProbability( &estocada, 70 );
    // jonas.addAttackAndProbability( &queda_da_lua, 5 );


    // // std::cout << batalha_do_seculo;

    // // batalha_do_seculo.planTurn( giro_atomico, estocada );
    // // batalha_do_seculo.executeTurn();

    // std::cout << "Jonas, seu maior inimigo está na sua frente com a lança da lua!\n";
    // std::cout << "Faça o melhor para derrotá-lo!\n";

    // // NormalBattle batalha_do_seculo(thiago, jonas);

    // // char enter;

    // // bool resultado = batalha_do_seculo.begin_battle();

    // // if (resultado)
    // // {
    // //     system("clear");
    // //     std::cout << "VOCÊ GANHOU!\n";
    // //     std::cin >> enter;
    // //     return 0;
    // // }
    // // system("clear");
    // // std::cout << "GAME OVER\n";
    // // std::cin >> enter ;

    // string file_path = "/home/thiago/new_dark_souls/Attack.sav";
    // std::ifstream load_stream ( file_path );
    // Attack* new_attack = AttackParser::loadFromStream( load_stream );
    
    // std::cout << *new_attack;

    /* Normal Battle - Demonstração */
    // Weapon espada_branca("Espada Branca", 15.5f, 150);
    // Weapon lanca_da_lua("Lança da Lua", 10.25f, 250);
    // string hero_file_path = "/home/thiago/new_dark_souls/Hero.sav";
    // string enemy_file_path = "/home/thiago/new_dark_souls/Enemy.sav";
    // std::ifstream hero_load_stream  ( hero_file_path );
    // std::ifstream enemy_load_stream ( enemy_file_path );

    // Player* player_ptr = PlayerParser::loadFromStream( hero_load_stream );
    // Enemy* enemy_ptr = EnemyParser::loadFromStream( enemy_load_stream );

    // player_ptr->equipWeapon( lanca_da_lua );
    // enemy_ptr->equipWeapon( espada_branca );

    // std::cout << *player_ptr;
    // std::cout << *enemy_ptr;

    // NormalBattle batalha( *player_ptr, *enemy_ptr );

    // batalha.begin_battle();

    // ====================================================
    /* Boss Battle - Demonstração */

    /* Armas */
    Weapon espada_branca("Espada Branca", 15.5f, 150);
    Weapon lanca_da_lua("Lança da Lua", 10.25f, 250);
    Weapon espeta_coracao("Espeta Coração", 25.25f, 150);
    Weapon luz_ardente("Luz Ardente", 30.25f, 500);

    /* Ataques */
    Attack giro_atomico( "Giro Atômico", 0.8f, 100.0f, "gira loucamente até gerar uma explosão nuclear!");
    Attack ataque_largo( "Ataque Largo", 0.5f, 0.25f, "ataca girando sua arma no ar!");
    Attack estocada( "Estocada", 2.5f, 0.15f, "estoca com sua arma!");
    Attack queda_da_lua( "Queda da Lua", 2.8f, 100.0f, "pula! É como se a lua estivesse caíndo do céu");

    Player thiago("Thiago");
    thiago.equipWeapon( espada_branca );
    thiago.setMaxHealth( 500.0f );
    thiago.heal( 500.0f );

    thiago.addAttack( giro_atomico );
    thiago.addAttack( ataque_largo );
    thiago.addAttack( estocada );

    /* Primeira fase */
    Enemy cavaleiro_negro("Cavaleiro Negro");
    cavaleiro_negro.equipWeapon( espeta_coracao );
    cavaleiro_negro.addAttackAndProbability( &ataque_largo, 50 );
    cavaleiro_negro.addAttackAndProbability( &giro_atomico, 2 );
    cavaleiro_negro.addAttackAndProbability( &estocada,     80 );

    /* Segunda fase */
    Enemy cavaleiro_negro_alado("Cavaleiro Negro Alado");
    cavaleiro_negro_alado.equipWeapon( luz_ardente );
    cavaleiro_negro_alado.addAttackAndProbability( &queda_da_lua, 5 );
    cavaleiro_negro_alado.addAttackAndProbability( &giro_atomico, 2 );
    cavaleiro_negro_alado.addAttackAndProbability( &ataque_largo, 50 );


    BossBattle batalha_com_cavaleiro_negro( thiago );
    batalha_com_cavaleiro_negro.add_phase( cavaleiro_negro );       // Primeira fase
    batalha_com_cavaleiro_negro.add_phase( cavaleiro_negro_alado ); // Segunda fase

    batalha_com_cavaleiro_negro.begin_battle();

    return 0;
}