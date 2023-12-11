#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "Item.h"

using std::ostream;

class Consumable : public Item
{
public:
    Consumable  (  );
    Consumable  ( string, string, double = 1.0f );
    Consumable  ( const Consumable& );
    virtual ~Consumable();

    virtual void use            ( Entity& ) = 0;
    virtual void inflict_effect ( Entity& ) = 0;

    double  getHealthFactor() const { return this->health_factor; }
    void    setHealthFactor( double );

protected:
    double health_factor;   // Ratio usado em operações - porcentagem!
};

#endif // CONSUMABLE_H