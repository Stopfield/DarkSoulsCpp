#include <iostream>

#include "weapon.h"
#include "enemy.h"
#include "player.h"
#include "Item.h"

int main()
{

    enum Armas {
        PLAYER,
        SKELETON,
        BOSS
    };

    Item* estusFlask = new Item("Estus Flask", "Cura personagem", 250.0f);
    // Inicializa todo o array "armas" com zero
    Weapon* armas[3] { 0 };
    Player* player;
    // Inicializa todo o array "inimigos" com zero
    Enemy* inimigos[5] { 0 };

    armas[Armas::PLAYER] = new Weapon("Best Weapon", 200.0f, 250);
    armas[Armas::SKELETON] = new Weapon("Rusted Weapon", 100.0f, 250);
    armas[Armas::BOSS] = new Weapon("Dragon Spear", 315.0f, 250);

    player = new Player("Ashen One", 450.0f, 150.0f, 25.0f);
    player->equipWeapon(*armas[Armas::PLAYER]);

    player->grabItem(*estusFlask);
    player->grabItem(*estusFlask);

    // Cria três skeletons
    for (size_t i = 0; i < 3; ++i)
    {
        inimigos[i] = new Enemy("Skeleton", 750.0f);
        inimigos[i]->equipWeapon(*armas[Armas::SKELETON]);
    }

    // Vamos batalhar com os esqueletos!
    for (size_t i = 0; i < 3; ++i)
    {
        if (player->battle( *inimigos[i] ))
        {
            delete inimigos[i];
            inimigos[i] = 0;
            cout << "Venceu! Toma um Estus Flask!\n";
            player->useItem(*estusFlask);
        }
        else
        {
            cout << "Game Over!\n";
            break;
        }
    }

    for (size_t i = 0; i < 3; ++i)
        if (armas[i])
            delete armas[i];

    for (size_t i = 0; i < 5; ++i)
        if (inimigos[i])
            delete inimigos[i];

    delete player;
    delete estusFlask;
    


    // Weapon bigSword("Big Sword", 257.6f);

    // Item estusFlask("Estus Flask", "Recupera vida", 100.0f);
    // Item bomba("Bomba", "Explode!", -50.0f);

    // Item muitosItens[15] = {
    //     Item("aaaa", "bbbb", 10.0f),
    //     Item("xxx", "ccc", 10.0f),
    //     Item("zzz", "ddd", 5.0f),
    //     Item("lll", "vvv", 2.0f)
    // };

    // Player thiago("Thiago");
    // thiago.showInventory();

    // for (size_t i = 0; i < 4; ++i)
    //     thiago.grabItem(muitosItens[i]);

    // thiago.showInventory();
    // thiago.grabItem(estusFlask);
    // thiago.showInventory();

    // // Novo player
    // thiago.equipWeapon(bigSword);

    // Player solarKnight(thiago);
    // solarKnight.setName("Astolfo");
    // solarKnight.showInventory();

    // // solarKnight.equipWeapon(bigSword);
    // cout << "Endereço da arma no main: " << &bigSword << "\n";
    // cout << "Endereço da arma (Astolfo): " << &solarKnight.getEquipedWeapon() << "\n";
    // cout << "Endereço da arma (Thiago): " << &thiago.getEquipedWeapon() << "\n";
    

    return 0;
}