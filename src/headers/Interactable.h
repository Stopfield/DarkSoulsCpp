#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <string>
#include <iostream>

using std::cout;
using std::string;
using std::ostream;

class Interactable
{
    friend ostream& operator<<  ( ostream&, const Interactable& );
    friend int      operator!   ( const Interactable& );
public:
    Interactable            (  );
    Interactable            ( char, char );
    Interactable            ( const Interactable& );
    virtual ~Interactable   (  );

    void            interact        (  );
    
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
};

#endif // INTERACTABLE_H