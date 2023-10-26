#include <iostream>
#include <iomanip>

#include "Weapon.h"
#include "Enemy.h"
#include "Player.h"
#include "Item.h"
#include "Entity.h"
#include "Attack.h"

using std::cout;

int main()
{
    Item estusFlask("Estus Flask", "Restaura vida", 100.0f);
    Item bomb("Bomb", "Explodes", 0.0f);

    Attack estocada("Estocada", 1.0f, 1.0f, " estoca a arma em ");
    Attack estocada2("Estocada", 1.0f, 1.0f, " asdasdsadsa");
    Attack empty;

    Weapon astoraSword("Astora Sword", 100.0f);
    Weapon bigSword("Big Sword", 50.0f);
    Weapon emptyWe;

    Entity thiago("Thiago");
    Entity empty3;
    thiago.equipWeapon( astoraSword );

    Entity darkKnight("Dark Knight");
    darkKnight.equipWeapon( bigSword );

    thiago.grabItem( estusFlask );
    thiago.grabItem( estusFlask );
    thiago.grabItem( estusFlask );
    thiago.grabItem( estusFlask );

    thiago.grabItem( bomb );
    thiago.grabItem( bomb );
    thiago.grabItem( bomb );

    cout << std::boolalpha << (bool) ( thiago == darkKnight ) << "\n";
    cout << std::boolalpha << (bool) ( thiago != darkKnight ) << "\n";

    thiago = darkKnight;
    cout << std::boolalpha << (bool) ( thiago == darkKnight ) << "\n";
    cout << std::boolalpha << (bool) ( thiago == darkKnight ) << "\n";
    cout << std::boolalpha << (bool) ( !empty3 ) << "\n";
    cout << std::boolalpha << (bool) ( !thiago ) << "\n";


    thiago.showInventory();

    

    // thiago.attack( darkKnight, estocada );
    return 0;
}