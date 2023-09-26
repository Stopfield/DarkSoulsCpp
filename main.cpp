#include <iostream>

#include "weapon.h"
#include "enemy.h"
#include "player.h"

int main()
{
    /* Player não constante - arma constante */
    Player player("Thiago");
    Enemy undead("Undead", 550, 100, 25);

    // Criando uma espada com 253.3 de dano e durabilidade de 150
    Weapon espada("Astora Sword", 252.3, 150);
    const Weapon draconian("Draconian Sword", 150.0, 75);

    player.equipWeapon(espada);

    const Weapon * varWeapon = &player.getEquipedWeapon();
    std::cout << "Var: " << varWeapon->getName() << std::endl;

    // Pode atacar, não é constante
    if (!player.isUnarmed())
    {
        player.attack(undead);
        std::cout << player.getName() << " ataca com "
                    << player.getEquipedWeapon().getName() << "\n";
    }
    std::cout << "Undead HP: " << undead.getHealth() << "\n";
    std::cout << "Durabilidade da Arma: " << player.getEquipedWeapon().getDurability() << std::endl;

    /* E com uma constante? */
    varWeapon = &draconian;

    std::cout << "Var: " << varWeapon->getName() << std::endl;
    std::cout << "Player: " << player.getEquipedWeapon().getName() << std::endl;

    /* E com const? Nem pode! O atributo deveria ser const também! */
    // player.equipWeapon(draconian);

    const Player constancio("Constâncio");

    // A arma não é constante, então pode
    constancio.attack(undead);

    // Sempre verificar se está sem equipamento
    if (!constancio.isUnarmed())
    {
        std::cout << "Constancio's Weapon: " <<
                    constancio.getEquipedWeapon().getDamage() << "\n";
    }

    /* Não pode! */
    // constancio.equipWeapon(espada);

    return 0;
}