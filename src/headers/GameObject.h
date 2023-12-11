#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>

using std::ostream;

#include "EssentialStructs.h"

/**
 * Essa classe administra qualquer objeto presente no jogo.
*/
class GameObject
{
public:

    GameObject  (  );
    GameObject  ( Vector2D, char );
    GameObject  ( const GameObject& );
    virtual ~GameObject();

    virtual void interact() = 0;

    void setPosition            ( Vector2D );
    void setRepresentation      ( char );

    Vector2D getPosition()      const    { return this->position == 0 ? Vector2D { 0 } : *this->position;      };
    char getRepresentation()    const    { return this->representation; };
protected:
    Vector2D* position = 0;
    char representation;
};

#endif