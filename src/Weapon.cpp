#include "Weapon.h"

const size_t Weapon::NAME_MAX_SIZE          = 15;
const string Weapon::DEFAULT_WEAPON_NAME    = "Empty Weapon";

Weapon::Weapon()
: name(Weapon::DEFAULT_WEAPON_NAME), damage(0.0f), durability(100.0f)
{
    // cout << "Creating empty weapon\n";
}

/**
 * A ordem de inicialização no .h é importante!
*/
Weapon::Weapon(string name, double damage, int durability)
{
    // cout << "Creating weapon " << name << "...\n";
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
    // cout << "Destroying weapon " << this->name << "...\n";
}

/* Legado */
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

/**
 * Aumenta a durabilidade da arma por uma porcentagem do total.
 * @param amount Incrementa a durabilidade por um valor numérico. Não pode ser negativo
*/
void Weapon::increaseDurability( double ratio)
{
    if (ratio < 0)
        return;
    this->setDurability( (int) (durability + (durability * ratio)) );
}

/**
 * Diminui a durabilidade da arma por um valor
 * @param amount Valor numérico que vai ser decrementado. Não pode ser negativo.
*/
void Weapon::decreaseDurability( int amount )
{
    if (amount < 0)
        return;
    this->setDurability( this->durability - amount );
}

/* Legado */
void Weapon::printStatus() const
{
    cout << "\n======   WEAPON   =====\n";
    cout << "* " << this->name << "\n";
    cout << "* Damage: \t" << this->damage << "\n";
    cout << "* Durability: \t" << this->durability << "\n";
    cout << "======   WEAPON   =====\n\n";
}

#pragma region Setters

void Weapon::setName(string name)
{
    if (name.empty())
    {
        // cout << "Weapon name can't be empty! Defaulting to \"Empty Weapon\"";
        this->name = "Empty Weapon";
        return;
    }

    if (name.size() > Weapon::NAME_MAX_SIZE)
    {
        // cout << "Weapon can't be more than " << NAME_MAX_SIZE << " characters!\n";
        this->name = name.substr(0, Weapon::NAME_MAX_SIZE);
        return;
    }

    this->name = name;
}

void Weapon::setDamage(double damage)
{
    if (damage < 0)
    {
        // cout << "Damage can't be negative! Defaulting to zero\n";
        this->damage = 0;
        return;
    }
    this->damage = damage;
}

void Weapon::setDurability(int durability)
{
    if (durability < 0)
    {
        // cout << "Durability can't be negative! Defaulting to 0\n";
        this->durability = 0;
        return;
    }
    this->durability = durability;
}

#pragma endregion

#pragma region Operator Overloads

ostream& operator<< (ostream& output, const Weapon& weapon)
{
    output << "\n======   WEAPON   =====\n";
    output << "* " << weapon.name << "\n";
    output << "* Damage: \t" << weapon.damage << "\n";
    output << "* Durability: \t" << weapon.durability << "\n";
    return output;  
}

int operator! (const Weapon& weapon)
{
    return ( weapon.name.empty() || weapon.name == Weapon::DEFAULT_WEAPON_NAME );
}

const Weapon& Weapon::operator= (const Weapon& right)
{
    if (&right != this)
    {
        this->name = right.name;
        this->damage = right.damage;
        this->durability = right.durability;
    }
    return *this;
}

int Weapon::operator== (const Weapon& right )
{
    if (this->name == right.name)
        return 1;
    return 0;
}

int Weapon::operator!= (const Weapon& right)
{
    return !( *this == right );
}

#pragma endregion
