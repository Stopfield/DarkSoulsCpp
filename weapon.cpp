#include "weapon.h"

Weapon::Weapon()
{
    cout << "Creating empty weapon\n";
    this->setName("Empty Weapon");
    this->setDurability(100);    
    this->setDamage(0.0);    
}

/**
 * A ordem de inicialização no .h é importante!
*/
Weapon::Weapon(string name, double damage, int durability)
:name(name), damage(damage), durability(durability)
{
    cout << "Creating weapon " << name << "...\n";
}

Weapon::~Weapon()
{
    cout << "Destroying weapon " << this->name << "...\n";
}

void Weapon::setName(string name)
{
    if (name.empty())
    {
        cout << "Weapon name can't be empty! Defaulting to \"Empty Weapon\"";
        this->name = "Empty Weapon";
        return;
    }
    this->name = name;
}

void Weapon::setDamage(double damage)
{
    if (damage < 0)
    {
        cout << "Damage can't be negative! Defaulting to zero\n";
        this->damage = 0;
        return;
    }
    this->damage = damage;
}

void Weapon::setDurability(int durability)
{
    if (durability < 0)
    {
        cout << "Durability can't be negative! Defaulting to 0\n";
        this->durability = 0;
        return;
    }
    this->durability = durability;
}

double Weapon::inflictDamage(double enemyLife)
{
    if (this->durability > 0)
    {
        if (enemyLife <= 0)
            cout << "O inimigo já morreu!\n";

        this->setDurability(this->durability - 1);
        return enemyLife - this->damage;
    }
    cout << "A espada está quebrada! Não dá dano\n";
    return enemyLife;
}

void Weapon::printStatus() const
{
    cout << "\n======   WEAPON   =====\n";
    cout << "* " << this->name << "\n";
    cout << "* Damage: \t" << this->damage << "\n";
    cout << "* Durability: \t" << this->durability << "\n";
    cout << "======   WEAPON   =====\n\n";
}