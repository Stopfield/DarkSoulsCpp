#ifndef ARMOR_H
#define ARMOR_H

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::ostream;

#include "Item.h"

class Armor : public Item
{
    friend ostream& operator<<  ( ostream&, const Armor& );
    friend int      operator!   (const Armor& );
public:
    Armor();
    Armor( double, double = 0.0, double = 1.0 );
    Armor( const Armor& );
    virtual ~Armor();

    void use( Entity& ) override;

    double getDamageReduction() const { return this->damage_reduction; }
    double getMinStrength()     const { return this->min_strength;     }
    double getWeight()          const { return this->weight;           }

    void setDamageReduction ( double );
    void setMinStrength     ( double );
    void setWeight          ( double );

    const Armor& operator=  ( const Armor& );
    int operator==          ( const Armor& );
    int operator!=          ( const Armor& );

protected:
    const static string DEFAULT_ARMOR_NAME;

    double  damage_reduction;
    double  min_strength;
    double  weight;
};  

#endif // ARMOR_H
