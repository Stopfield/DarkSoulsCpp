#include "Armor.h"

const string Armor::DEFAULT_ARMOR_NAME    = "Empty Armor";

Armor::Armor() : Item()
{
    this->damage_reduction = 0.0f;
    this->min_strength = 0.0f;
    this->weight = 0.0f;
}

/**
 * A ordem de inicialização no .h é importante!
*/
Armor::Armor(double damage_reduction, double min_strength, double weight) : Item()
{
    this->setDamageReduction( damage_reduction );
    this->setMinStrength( min_strength );
    this->setWeight( weight );
}

Armor::Armor( const Armor& other ) : Item( static_cast<Armor> (other) )
{
    this->damage_reduction = other.damage_reduction;
    this->min_strength = other.min_strength;
    this->weight = other.weight;
}

Armor::~Armor()
{
}

#pragma region Setters

void Armor::setDamageReduction(double ratio )
{
    if (ratio < 0.0f)
        this->damage_reduction = 0.0f;
}

void Armor::setMinStrength(double minimum)
{
    if (minimum < 0)
        this->min_strength = 0;
}

void Armor::setWeight(double weight)
{
    if (weight < 0)
        this->weight = 0;
}

#pragma endregion

#pragma region Operator Overloads

ostream& operator<< (ostream& output, const Armor& Armor)
{
    output << "\n======   Armor   =====\n";
    output << "* " << Armor.name << "\n";
    output << "* Damage Reduction: \t" << Armor.damage_reduction << "\n";
    output << "* Strength required: \t" << Armor.min_strength << "\n";
    output << "* Weight: \t" << Armor.weight << "\n";
    return output;  
}

int operator! (const Armor& Armor)
{
    return ( Armor.name.empty() || Armor.name == Armor::DEFAULT_ARMOR_NAME );
}

const Armor &Armor::operator=(const Armor &right)
{
    if (&right != this)
    {
        static_cast<Item> (*this) = static_cast<Item> (right);
        this->damage_reduction = right.damage_reduction;
        this->min_strength = right.min_strength;
        this->weight = right.weight;
    }
    return *this;
}

int Armor::operator== (const Armor& right )
{
    return ( static_cast<Item> (*this) == static_cast<Item> (right) );
}

int Armor::operator!= (const Armor& right)
{
    return !( *this == right );
}

#pragma endregion
