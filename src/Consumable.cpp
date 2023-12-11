#include "Consumable.h"
#include "Item.h"

Consumable::Consumable() : Item()
{
    this->health_factor = 1.0;
}

Consumable::Consumable(string name, string description, double health_factor)
: Item( name, description )
{
    this->setHealthFactor( health_factor );
}

Consumable::Consumable(const Consumable& other) : Item( other )
{
    this->health_factor = other.health_factor;
}

Consumable::~Consumable()
{
}

void Consumable::setHealthFactor(double ratio)
{
    if (ratio < 1.0)
    {
        this->health_factor = 1.0;
        return;
    }
    this->health_factor = ratio;
}