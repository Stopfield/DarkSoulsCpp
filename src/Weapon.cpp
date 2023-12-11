#include "Weapon.h"

const string Weapon::DEFAULT_WEAPON_NAME    = "Empty Weapon";

Weapon::Weapon() : Item( )
{
    this->setName( Weapon::DEFAULT_WEAPON_NAME );
    this->setDamage( 0.0f );
    this->setDurability( 100 );
}

/**
 * A ordem de inicialização no .h é importante!
*/
Weapon::Weapon(string name, double damage, int durability) : Item(  )
{
    // cout << "Creating weapon " << name << "...\n";
    this->setName(name);
    this->setDamage(damage);
    this->setDurability(durability);
}

Weapon::Weapon( const Weapon& other ) : Item( other )
{
    this->name          = other.name;
    this->damage        = other.damage;
    this->durability    = other.durability;
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
