#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

using std::cout;
using std::string;
using std::ostream;

#include "GameObject.h"

class Item : public GameObject
{
    friend ostream& operator<<  ( ostream&, const Item& );
    friend int      operator!   ( const Item& );
public:
    Item            ( );
    Item            ( string, string );
    Item            ( const Item& );
    virtual ~Item   ( );
    
    inline string getName()         const { return this->name;          }
    inline string getDescription()  const { return this->description;   }

    void setName            ( string );
    void setDescription     ( string );

    const Item& operator=   ( const Item& );
    int         operator==  ( const Item& );
    int         operator!=  ( const Item& );

protected:
    const static u_int8_t   MAX_ITEM_STACK;
    const static size_t     MAX_NAME_SIZE;
    const static size_t     MAX_DESCRIPTION_SIZE;
    const static string     DEFAULT_ITEM_NAME;
    const static string     DEFAULT_DESCRIPTION;

    string name;
    string description;
};

#endif // ITEM_H