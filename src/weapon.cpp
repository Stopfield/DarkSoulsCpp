#include "weapon.h"

Weapon::Weapon()
: name("Empty Weapon"), damage(0.0f), durability(100.0f)
{
    cout << "Creating empty weapon\n";
}

/**
 * A ordem de inicialização no .h é importante!
*/
Weapon::Weapon(string name, double damage, int durability)
{
    cout << "Creating weapon " << name << "...\n";
    this->setName(name);
    this->setDamage(damage);
    this->setDurability(durability);
}

Weapon::Weapon( const Weapon& other )
{
    this->name = other.name;
    this->damage = other.damage;
    this->durability = other.durability;
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

    if (name.size() > this->NAME_MAX_SIZE)
    {
        cout << "Weapon can't be more than " << NAME_MAX_SIZE << " characters!\n";
        this->name = name.substr(0, NAME_MAX_SIZE);
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
