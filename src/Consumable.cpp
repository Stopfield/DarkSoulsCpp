#include "Consumable.h"

Consumable::Consumable() : Item()
{
    this->health_factor = 1.0;
}

Consumable::Consumable(string name, string description, double health_factor)
    : Item( name, description )
{
    this->setHealthFactor( health_factor );
}

Consumable::Consumable(const Consumable& other) : Item( static_cast<Item> (other) )
{
    this->health_factor = other.health_factor;
}

Consumable::~Consumable()
{
}

void Consumable::setHealthFactor(double ratio)
{
    if (ratio < 1.0)
        this->health_factor = 1.0;
}

#pragma region OperatorOverloads

ostream& operator<< ( ostream& output, const Consumable& item )
{
    output << "Consumable: " << item.name << " | " << item.description;
    return output;
}

int operator! ( const Consumable& right )
{
    return !( static_cast<Item> (right) );
}

const Consumable &Consumable::operator=(const Consumable &right)
{
    if (&right != this)
    {
        static_cast<Item> (*this) = static_cast<Item> (right);
        this->name = right.name;
        this->description = right.description;
    }
    return *this;
}

int Consumable::operator== ( const Consumable& right )
{    
    return ( static_cast<Item> (*this) == static_cast<Item> (right) );
}

int Consumable::operator!= (const Consumable& right)
{
    return !( *this == right );
}

#pragma endregion