#ifndef RESTORATIVE_CONSUMABLE_H
#define RESTORATIVE_CONSUMABLE_H

#include "Consumable.h"
#include "Entity.h"

using std::ostream;

class RestorativeConsumable : public Consumable
{
    friend ostream& operator<<  ( ostream&, const RestorativeConsumable& );
    friend int      operator!   ( const RestorativeConsumable& );
public:
    RestorativeConsumable  (  );
    RestorativeConsumable  ( string, string, double, double = 1.0f );
    RestorativeConsumable  ( const RestorativeConsumable& );
    virtual ~RestorativeConsumable();

    void use            ( Entity& ) override;
    void inflict_effect ( Entity& ) override;

    void    setRestorativeModifier   ( double );
    double  setRestorativeModifier   (  ) const { return this->restorative_modifier; };

    const RestorativeConsumable&    operator=   ( const RestorativeConsumable& );
    int                             operator==  ( const RestorativeConsumable& );
    int                             operator!=  ( const RestorativeConsumable& );

protected:
    double restorative_modifier;   // Ratio usado em operações 
};

#endif // RESTORATIVE_CONSUMABLE_H