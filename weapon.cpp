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
        this->name = name;
        return;
    }
    this->name = name;
}

void Weapon::setDamage(double damage)
{
    if (damage < 0)
    {
        cout << "Damage can't be negative! Defaulting to zero\n";
        this->damage = damage;
        return;
    }
    this->damage = damage;
}

void Weapon::setDurability(int durability)
{
    if (durability < 0)
    {
        cout << "Durability can't be negative! Converting to 0\n";
        this->durability = 0;
        return;
    }
    this->durability = durability;
}

double Weapon::inflictDamage(double enemyLife)
{
    if (enemyLife <= 0)
    {
        cout << "O inimigo já morreu!\n";
    }
    this->setDurability(this->durability - 1);
    return enemyLife - this->damage;
}

void Weapon::printStatus() const
{
    cout << "\n* " << this->name << "\n";
    cout << "* Damage: \t" << this->damage << "\n";
    cout << "* Durability: \t" << this->durability << "\n\n";
}