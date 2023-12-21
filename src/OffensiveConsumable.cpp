#include "OffensiveConsumable.h"

OffensiveConsumable::OffensiveConsumable()
: Consumable()
{
    this->damage = 1.0f;
}

OffensiveConsumable::OffensiveConsumable(
    string name, string description,
    double dmg_modifier, double health_factor )
: Consumable( name, description, health_factor )
{
    this->setDamageModifier( dmg_modifier );
}

OffensiveConsumable::OffensiveConsumable(const OffensiveConsumable& other)
: Consumable( other )
{
    this->damage = other.damage;
}

OffensiveConsumable::~OffensiveConsumable()
{
}

void OffensiveConsumable::use(Entity& ent)
{
    this->inflict_effect( ent );
}

void OffensiveConsumable::inflict_effect(Entity& ent)
{
    ent.receiveDamage(
        (this->health_factor * this->damage) * ent.getHealth()
    );
}

void OffensiveConsumable::setDamageModifier(double dmg)
{
    if (dmg < 0)
    {
        this->damage = 1.0f;
        return;
    }
    this->damage = dmg;
}

#pragma region OperatorOverloads

const OffensiveConsumable &OffensiveConsumable::operator=(const OffensiveConsumable& right)
{
    if (&right != this)
    {
        Consumable::operator=(right);
        this->damage = right.damage;
    }
    return *this;
}

int OffensiveConsumable::operator==(const OffensiveConsumable& right)
{
    if (this->name == right.name)
        return 1;
    return 0;
}

int OffensiveConsumable::operator!=(const OffensiveConsumable& right)
{
    return !( *this == right );
}

ostream &operator<<(ostream& output, const OffensiveConsumable& item)
{
    output << "Offensive Consumable: " << item.name << " | " << item.description;
    output << "Damage: " << item.damage;
    return output;
}

int operator!(const OffensiveConsumable& right)
{
    return !( right.name.empty() || right.name == right.DEFAULT_ITEM_NAME );
}

#pragma endregion