#include <iostream>

#include "weapon.h"

int main()
{
    Weapon espada("Astora Sword", 252.3, 150);
    cout << "Vida do Inimigo: " << espada.inflictDamage(0) << endl;
    return 0;
}