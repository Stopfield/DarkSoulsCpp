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

bool Interactable::interact( GameObject& other )
{
    if (this->actual_representation == this->before_interaction)
    {
        this->actual_representation = this->after_interaction;
        this->do_something_to_entity( *this->entity_to_afect, this->current_flag );
        return true;
    }
    this->actual_representation = this->before_interaction;
    this->do_something_to_entity( *this->entity_to_afect, this->current_flag );
    return true;
}

/**
 * Dependendo da flag passada, o interactable faz alguma coisa
*/
void Interactable::do_something_to_entity(Entity& ent, InteractionFlags flag)
{
    switch (flag)
    {
    case DAMAGE:
        ent.receiveDamage( health_factor );
        std::cout << message << "\n";
        break;
    
    case HEAL:
        ent.heal( health_factor );
        std::cout << message << "\n";
        break;

    case SHOW_MESSAGE:
        std::cout << "O objeto diz: \"" << message << "\"\n";
        break;
    }
}

/* Não precisa de checagem, o tipo InteractionFlags só garante um conjunto de valores */
void Interactable::changeFlag(InteractionFlags new_flag)
{
    this->current_flag = new_flag;
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
        GameObject::operator=(other);
        this->after_interaction = other.after_interaction;
        this->before_interaction = other.before_interaction;
    }
    return *this;
}

int Interactable::operator==(const Interactable& other)
{
    return ( GameObject::operator==(other)
            && this->before_interaction == other.before_interaction
            && this->after_interaction == other.after_interaction );
}

int Interactable::operator!=(const Interactable& other)
{
    return !( *this == other );
}
