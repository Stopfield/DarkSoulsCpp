#include <iostream>

#include "weapon.h"
#include "enemy.h"
#include "player.h"

int main()
{
    /* Um inimigo para testar */
    Enemy undead("Undead", 550, 100, 25);

    /* Player não constante - arma constante */
    Player player("Thiago");

    // Criando uma espada
    Weapon espada("Astora Sword", 252.3, 150);

    player.equipWeapon(espada);

    player.attack(undead);

    // Posso alterar minha arma aqui fora, um inimigo pode destruí-la, por ex.
    // Mas o usuário não pode alterar a arma com que o usuário está equipado
    // com atribuição de ponteiros.
    Weapon * varWeapon = &player.getEquipedWeapon();
    std::cout << "Var: " << varWeapon->getName() << std::endl;

    // Pode atacar, não é constante
    if (!player.isUnarmed())
    {
        player.attack(undead);
        std::cout << player.getName() << " ataca com "
                    << player.getEquipedWeapon().getName() << "\n";
    }
    std::cout << "Undead HP: " << undead.getHealth() << "\n";
    std::cout << "Durabilidade da Arma: "
                << player.getEquipedWeapon().getDurability() << std::endl;

    /* E com uma constante? */
    const Weapon draconian("Draconian Sword", 150.0, 75);

    /* E com const? Nem pode! O atributo deveria ser const também! */
    // player.equipWeapon(draconian);

    /* Player constante - Bem limitado, só pode fazer algumas coisas */
    const Player constancio("Constâncio");

    // A arma não é constante, então pode
    constancio.attack(undead);

    // Sempre verificar se está sem equipamento
    if (!constancio.isUnarmed())
    {
        cout << "Constancio's Weapon: "
                << constancio.getEquipedWeapon().getDamage() << "\n";
    }

    /* Armas */
    draconian.printStatus();
    // draconian.setName("ERRO!");

    /* Não pode! */
    // constancio.equipWeapon(espada);

    /* Quero criar a Astora Sword++! Vou copiar! */
    Weapon astoraSwordPP(espada);
    astoraSwordPP.setName("Astora Sword ++");
    astoraSwordPP.setDamage(espada.getDamage() * 2);

    cout << astoraSwordPP.getName() << " : " << astoraSwordPP.getDamage()
         << "\n"
         << espada.getName() << " : " << espada.getDamage() << "\n";
    
    /* Preciso de uma variação mais forte de um Undead! */

    Enemy bigUndead(undead);
    bigUndead.setName("Big Undead");
    bigUndead.setStrenght(150.0f);
    bigUndead.equipWeapon(astoraSwordPP);

    cout << bigUndead.getName() << " : " << bigUndead.getStrength()
        << "\n"
        << undead.getName() << " : " << undead.getStrength() << "\n";

    /* Preciso de uma cópia do Player! Ele vai mudar de personagem! */
    Player novoPlayer(player);
    novoPlayer.setName("Player 2");
    novoPlayer.setStamina(50.0f);
    novoPlayer.setHealth(200.0f);

    cout << novoPlayer.getName() << " : " << novoPlayer.getPosition()
        << "\n"
        << player.getName() << " : " << player.getPosition() << "\n";

    return 0;
}