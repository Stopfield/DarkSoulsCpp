
#include "GameObject.h"

GameObject::GameObject()
{
    this->position = 0;
    this->representation = 'O';
}

GameObject::GameObject(Vector2D pos, char representation)
{
    this->setPosition( pos );
    this->setRepresentation( representation );
}

GameObject::GameObject(const GameObject& other)
{
    if (other.position != 0)
        this->position = new Vector2D { other.position->x, other.position->y };
    this->representation = other.representation;
}

GameObject::~GameObject()
{
    if (this->position != 0)
        delete this->position;
}

void GameObject::setPosition(Vector2D new_pos)
{
    int new_x = new_pos.x;
    int new_y = new_pos.y;

    if (new_pos.x < 0)
        new_x = 0;

    if (new_pos.y < 0)
        new_y = 0;
    
    if (this->position == nullptr)
    {
        Vector2D* new_vector_2d = new Vector2D { new_x, new_y };
        this->position = new_vector_2d;
        return;
    }

    this->position->x = new_x; 
    this->position->y = new_y; 
}

void GameObject::setRepresentation(char new_repr)
{
    // Representation tem que ser ASCII legível
    if (new_repr > 32 && new_repr < 127)
    {
        this->representation = new_repr;
        return;
    }
    this->representation = 'O';
}


