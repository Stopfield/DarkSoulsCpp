#ifndef OFFENSIVE_CONSUMABLE_H
#define OFFENSIVE_CONSUMABLE_H

#include "Consumable.h"
#include "Entity.h"

using std::ostream;

class OffensiveConsumable : public Consumable
{
    friend ostream& operator<<  ( ostream&, const OffensiveConsumable& );
    friend int      operator!   ( const OffensiveConsumable& );
public:
    OffensiveConsumable  (  );
    OffensiveConsumable  ( string, string, double, double = 1.0f );
    OffensiveConsumable  ( const OffensiveConsumable& );
    virtual ~OffensiveConsumable();

    void use            ( Entity& ) override;
    void inflict_effect ( Entity& ) override;

    void    setDamageModifier   ( double );
    double  getDamageModifier   (  ) const { return this->damage; };

    const OffensiveConsumable&  operator=   ( const OffensiveConsumable& );
    int                         operator==  ( const OffensiveConsumable& );
    int                         operator!=  ( const OffensiveConsumable& );

protected:
    double damage;   // Ratio usado em operações 
};

#endif // OFFENSIVE_CONSUMABLE_H