#include "RestorativeConsumable.h"

RestorativeConsumable::RestorativeConsumable()
: Consumable()
{
    this->restorative_modifier = 1.0f;
}

RestorativeConsumable::RestorativeConsumable(
    string name, string description,
    double health_factor, double restorative_modifier)
: Consumable(name, description, health_factor)
{
    this->setRestorativeModifier( restorative_modifier );
}

RestorativeConsumable::RestorativeConsumable(const RestorativeConsumable& other)
: Consumable( other )
{
    this->restorative_modifier = other.restorative_modifier;
}

RestorativeConsumable::~RestorativeConsumable()
{
}

void RestorativeConsumable::use(Entity& ent)
{
    this->inflict_effect( ent );
}

void RestorativeConsumable::inflict_effect(Entity& ent)
{
    ent.heal( this->health_factor * this->restorative_modifier );
}

void RestorativeConsumable::setRestorativeModifier(double modifier)
{
    if (modifier < 0)
    {
        this->restorative_modifier = 1.0f;
        return;
    }
    this->restorative_modifier = modifier;
}

#pragma region OperatorOverloads

ostream &operator<<(ostream& output, const RestorativeConsumable& item)
{
    output << "Restorative Consumable: " << item.name << " | " << item.description;
    output << "Restore points: " << item.restorative_modifier;
    return output;
}

int operator!(const RestorativeConsumable& right)
{
    return !( right.name.empty() || right.name == right.DEFAULT_ITEM_NAME );
}

const RestorativeConsumable &RestorativeConsumable::operator=(const RestorativeConsumable& right)
{
    if (&right != this)
    {
        Consumable::operator=(right);
        this->restorative_modifier = right.restorative_modifier;
    }
    return *this;
}

int RestorativeConsumable::operator==(const RestorativeConsumable& right)
{
    if (this->name == right.name)
        return 1;
    return 0;
}

int RestorativeConsumable::operator!=(const RestorativeConsumable& right)
{
    return !( *this == right );
}

#pragma endregion