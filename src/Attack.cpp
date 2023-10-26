#include "Attack.h"

const size_t Attack::DISPLAY_MSG_MAX_SIZE   = 60;
const size_t Attack::NAME_MAX_SIZE          = 10;
const string Attack::DEFAULT_ATTACK_NAME    = "Empty Attack";

Attack::Attack()
{
    this->name = Attack::DEFAULT_ATTACK_NAME;
    this->damageModifier = 1.0f;
    this->staminaCostModifier = 1.0f;
    this->displayMessage = "Empty Attack Message";
}

Attack::Attack( string name,
                double damageModifier,
                double staminaCostModifier,
                string displayMessage )
{
    this->setName(name);
    this->setDamageModifier( damageModifier );
    this->setStaminaCostModifier( staminaCostModifier );
    this->setDisplayMessage( displayMessage );
}

Attack::Attack( Attack& other )
{
    this->name = other.name;
    this->damageModifier = other.damageModifier;
    this->staminaCostModifier = other.staminaCostModifier;
    this->displayMessage = other.displayMessage;
}

Attack::~Attack()
{

}

#pragma region Setters

void Attack::setName( string name )
{
    if (name.empty())
    {
        std::cerr << "ValidationError: Attack name can't be empty!\n";
        return;
    }

    if (name.size() > Attack::NAME_MAX_SIZE)
    {
        std::cerr << "ValidationError: Attack name can't be more than "
            << Attack::NAME_MAX_SIZE << " chars! Getting substring!\n";
        this->name = name.substr(0, Attack::NAME_MAX_SIZE);
        return;
    }

    this->name = name;
}

void Attack::setDamageModifier(double modifier)
{
    if (modifier < 0)
        return;
    this->damageModifier = modifier;
}

void Attack::setStaminaCostModifier( double modifier )
{
    if (modifier < 0)
        return;
    this->staminaCostModifier = modifier;
}

void Attack::setDisplayMessage( string message )
{
    if (message.empty())
    {
        this->displayMessage = "Empty Attack Message";
        return;
    }
    if (message.size() > Attack::DISPLAY_MSG_MAX_SIZE)
    {
        this->displayMessage = message.substr(0, Attack::DISPLAY_MSG_MAX_SIZE);
        return;
    }
    this->displayMessage = message;
}

#pragma endregion

#pragma region OperatorOverloads

ostream& operator<<( ostream& output, const Attack& attack )
{
    output << attack.name << " | Damage: " << attack.damageModifier
        << " | Stamina: " << attack.staminaCostModifier;
    return output;
}

int operator!( const Attack& right )
{
    return (right.name.empty() || right.name == Attack::DEFAULT_ATTACK_NAME);
}

const Attack& Attack::operator=( const Attack& right )
{
    if (&right != this)
    {
        this->name = right.name;
        this->damageModifier = right.damageModifier;
        this->displayMessage = right.displayMessage;
    }
    return *this;
}

int Attack::operator==( const Attack& right )
{
    if (this->name != right.name)
        return 0;
    return 1;
}

int Attack::operator!=( const Attack& right )
{
    if ( !(*this == right) )
        return 1;
    return 0;
}

#pragma endregion