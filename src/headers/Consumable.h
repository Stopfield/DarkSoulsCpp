#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "Item.h"
#include "Entity.h"

class Entity; // Só pra dizer que entity existe.

class Consumable : public Item
{
    friend ostream& operator<<  ( ostream&, const Consumable& );
    friend int      operator!   ( const Consumable& );
public:

    Consumable  (  );
    Consumable  ( string, string, double = 1.0f );
    Consumable  ( const Consumable& );

    virtual ~Consumable();

    void consume_item( Entity& ) {};    // TODO

    double getHealthFactor() const { return this->health_factor; }
    void setHealthFactor( double );

    const Consumable&   operator=   ( const Consumable& );
    int                 operator==  ( const Consumable& );
    int                 operator!=  ( const Consumable& );

private:
    double health_factor;   // Ratio usado em operações - porcentagem!
};

#endif // CONSUMABLE_H