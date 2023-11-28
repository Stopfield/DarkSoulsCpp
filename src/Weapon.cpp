#include "Weapon.h"

const string Weapon::DEFAULT_WEAPON_NAME    = "Empty Weapon";

Weapon::Weapon() : Item()
{
    this->setName( Weapon::DEFAULT_WEAPON_NAME );
    this->setDamage( 0.0f );
    this->setDurability( 100 );
}

/**
 * A ordem de inicialização no .h é importante!
*/
Weapon::Weapon(string name, double damage, int durability) : Item()
{
    // cout << "Creating weapon " << name << "...\n";
    this->setName(name);
    this->setDamage(damage);
    this->setDurability(durability);
}

Weapon::Weapon( const Weapon& other ) : Item( static_cast<Item> (other) )
{
    this->name = other.name;
    this->damage = other.damage;
    this->durability = other.durability;
}

Weapon::~Weapon()
{
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

#pragma region Setters

void Weapon::setDamage(double damage)
{
    if (damage < 0)
    {
        this->damage = 0;
        return;
    }
    this->damage = damage;
}

void Weapon::setDurability(int durability)
{
    if (durability < 0)
    {
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
        static_cast<Item> (*this) = static_cast<Item> (right);
        this->damage = right.damage;
        this->durability = right.durability;
    }
    return *this;
}

int Weapon::operator== (const Weapon& right )
{
    return ( static_cast<Item> (*this) == static_cast<Item> (right) );
}

int Weapon::operator!= (const Weapon& right)
{
    return !( *this == right );
}

#pragma endregion
