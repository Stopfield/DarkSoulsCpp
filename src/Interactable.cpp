#include "Interactable.h"

Interactable::Interactable()
{
    this->before_interaction = 'B';   
    this->after_interaction = 'A';   
}

Interactable::Interactable(char before, char after)
{
    this->setBefore(before);
    this->setAfter(after);
}

Interactable::Interactable(const Interactable& other)
{
    this->before_interaction = other.before_interaction;
    this->after_interaction = other.after_interaction;
}

Interactable::~Interactable()
{
}

void Interactable::interact()
{
    if (this->actual_representation == this->before_interaction)
    {
        this->actual_representation = this->after_interaction;
        return;
    }
    this->actual_representation = this->before_interaction;
}

ostream &operator<<(ostream& output, const Interactable& inter)
{
    output << "Abstract Interactable object: " << inter.before_interaction
        << " -> " << inter.after_interaction << "\n";
    return output; 
}

int operator!(const Interactable& inter)
{
    return ( inter.before_interaction == inter.after_interaction );
}

void Interactable::setBefore(char new_repr)
{
    // Representation tem que ser ASCII legível
    if (new_repr > 32 && new_repr < 127)
    {
        this->before_interaction = new_repr;
        return;
    }
    this->before_interaction = 'B';
}

void Interactable::setAfter(char new_repr)
{
    // Representation tem que ser ASCII legível
    if (new_repr > 32 && new_repr < 127)
    {
        this->after_interaction = new_repr;
        return;
    }
    this->after_interaction = 'A';
}

const Interactable &Interactable::operator=(const Interactable& other)
{
    if (this != &other)
    {
        this->after_interaction = other.after_interaction;
        this->before_interaction = other.before_interaction;
    }
    return *this;
}

int Interactable::operator==(const Interactable& other)
{
    return ( this->before_interaction == other.before_interaction
            && this->after_interaction == other.after_interaction );
}

int Interactable::operator!=(const Interactable& other)
{
    return !( *this == other );
}
