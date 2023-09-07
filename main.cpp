#include <iostream>

#include "weapon.h"

int main()
{
    // Criando uma espada com 253.3 de dano e durabilidade de 150
    Weapon espada("Astora Sword", 252.3, 150);

    espada.printStatus();

    // Atacou um inimigo por exemplo
    cout << "Ataca um inimigo com " << espada.getName() << "\n";
    cout << endl;

    cout << "Durabilidade antes do ataque: " << espada.getDurability() << "\n";
    cout << "Vida do Inimigo: 260.0 - " << espada.getDamage() << " = " << espada.inflictDamage(260.0) << "\n";
    cout << "Durabilidade atual da espada: " << espada.getDurability() << "\n";
    cout << endl;

    cout << "Personagem afiou a espada e dobrou seu ataque!\n";
    espada.setDamage( espada.getDamage() * 2 );

    cout << "Dano atual da espada: " << espada.getDamage() << "\n";
    cout << "Ataca um inimigo com: " << espada.getName() << "\n";
    cout << "Vida do inimigo: 260.0 - "
        << espada.getDamage()
        << " = "
        << espada.inflictDamage(260.0) << "\n";

    cout << endl;

    // O personagem usou muito a espada e ela quebrou!
    cout << "O personagem usou muito a espada e ela quebrou!\n";
    espada.setDurability(0);

    cout << endl;

    cout << "Durabilidade da espada: " << espada.getDurability() << "\n";
    espada.inflictDamage(100);

    cout << endl;

    Weapon espadaVazia;
    espadaVazia.printStatus();

    return 0;
}