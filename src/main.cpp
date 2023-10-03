#include <iostream>

#include "weapon.h"
#include "enemy.h"
#include "player.h"
#include "Item.h"

int main()
{

    /* Exemplo 1*/
    // Player thiago("Thiago");
    // Enemy undead("Undead");

    // Weapon astoraSword("Astora Sword", 10.0f);
    // Weapon draconianSword("Draconian Sword", 15.0f);

    // undead.equipWeapon( astoraSword );
    // thiago.equipWeapon( draconianSword );

    // std::cout << "Thiago: " << thiago.getHealth() << "\n";
    // undead.attack(thiago);
    // std::cout << "Thiago: " << thiago.getHealth() << "\n";
    
    /* ==== Exemplo 1.5 ====*/
    // std::cout << "Players: " << Player::getNumPlayers() << "\n";
    // std::cout << "Enemies: " << Enemy::getNumEnemies() << "\n";

    // Player thiago("Thiago");
    // Enemy undead("Undead");

    // std::cout << "Players: " << Player::getNumPlayers() << "\n";
    // std::cout << "Enemies: " << Enemy::getNumEnemies() << "\n";

    // Player constancio("Constâncio");
    // Enemy knight("Black Knight");

    // std::cout << "Players: " << Player::getNumPlayers() << "\n";
    // std::cout << "Enemies: " << Enemy::getNumEnemies() << "\n";

    /* ==== Exemplo 2 ====*/
    /* Tamanho máximo de string - static*/
    // Player thiago("Thiago");
    // Enemy undead("Undead");

    // thiago.setName("Aaaaaaaaaaaaaaaaaaaaaaa");
    // undead.setName("Bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");

    /* ==== Exemplo 3 ====*/
    /* Número máximo de inimigos */

    /* Assim ele cria os 5! */
    // Enemy enemies[5];

    // Enemy* enemies[65];

    // for (int i = 0; i < 67; i++)
    // {
    //     std::cout << Enemy::getNumEnemies() << "\n";
    //     enemies[i] = new Enemy();
    // }

    /* ==== Exemplo 4 ====*/
    /* Batalha (While) */
    /* Vitória */
    // Player thiago("Thiago");
    // Enemy* inimigo = new Enemy("Undead");

    // Weapon astoraSword("Astora Sword", 15.5f);
    // Weapon ironSpear("Iron Spear", 20.0f);
    // Weapon greatSword("Great Sword", 200.0f);

    // thiago.equipWeapon(ironSpear);
    // inimigo->equipWeapon(astoraSword);

    // if (thiago.battle(*inimigo))
    //     cout << "VITÓRIA! >:) \n";
    // else
    //     cout << "Derrota! :( \n";

    // delete inimigo;

    // /* Derrota */
    // std::cout << "\n\n===========================\n";
    // std::cout << "Batalha com o Black Knight!\n";

    // thiago.setHealth(100.0f);

    // inimigo = new Enemy("Black Knight", 150.0f);
    // inimigo->equipWeapon(greatSword);

    // if (thiago.battle(*inimigo))
    //     cout << "VITÓRIA! >:) \n";
    // else
    //     cout << "Derrota! :( \n";

    // delete inimigo;

    /* ==== Exemplo 5 ====*/
    /* Utilização de item (for)*/
    // Item estusFlask("Estus Flask", "Recupera vida", 100.0f);

    // Player thiago("Thiago");
    // thiago.grabItem(estusFlask);
    // thiago.showInventory();

    // for (size_t i = 0; i < 10; i++)
    //     thiago.grabItem(estusFlask);

    // cout << "Health: " << thiago.getHealth() << "\n";
    // thiago.showInventory();
    // thiago.useItem(estusFlask);
    // cout << "Health: " << thiago.getHealth() << "\n";
    // thiago.showInventory();

    /* === Exemplo 6 === */
    /* Enrage enemy! */

    Enemy undead("Undead");
    Enemy::enrageEnemy(undead);

    Enemy* inimigos[5];
    for (size_t i = 0; i < 4; i++)
        inimigos[i] = new Enemy();
    
    Enemy::enrageEnemy(undead);


    return 0;
}