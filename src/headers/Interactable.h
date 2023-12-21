#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <string>
#include <iostream>

using std::cout;
using std::string;
using std::ostream;

#include "GameObject.h" 
#include "Entity.h"

enum InteractionFlags {
    DAMAGE, HEAL, SHOW_MESSAGE
};

class Interactable : public GameObject
{
    friend ostream& operator<<  ( ostream&, const Interactable& );
    friend int      operator!   ( const Interactable& );
public:
    Interactable            (  );
    Interactable            ( char, char );
    Interactable            ( const Interactable& );
    virtual ~Interactable   (  );

    bool interact   ( GameObject& ) override;
    void do_something_to_entity( Entity&, InteractionFlags );
    void changeFlag( InteractionFlags );
    
    inline char getRepresentation()     const { return this->actual_representation;    }
    inline char getBefore()     const { return this->before_interaction;    }
    inline char getAfter()      const { return this->after_interaction;     }

    void setBefore          ( char );
    void setAfter           ( char );

    const Interactable& operator=       ( const Interactable& );
    int                 operator==      ( const Interactable& );
    int                 operator!=      ( const Interactable& );

protected:
    char actual_representation;
    char before_interaction;
    char after_interaction;

    double health_factor;
    string message;

    InteractionFlags current_flag;
    Entity* entity_to_afect = nullptr;
};

#endif // INTERACTABLE_H