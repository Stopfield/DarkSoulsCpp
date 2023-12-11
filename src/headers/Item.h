#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

using std::cout;
using std::string;
using std::ostream;

class Entity;

class Item
{
public:
    Item            ( );
    Item            ( string, string );
    Item            ( const Item& );
    virtual ~Item   ( );

    virtual void use( Entity& ) = 0;

    inline string getName()         const { return this->name;          }
    inline string getDescription()  const { return this->description;   }

    void setName            ( string );
    void setDescription     ( string );

protected:
    const static u_int8_t   MAX_ITEM_STACK;
    const static size_t     MAX_NAME_SIZE;
    const static size_t     MAX_DESCRIPTION_SIZE;
    const static string     DEFAULT_ITEM_NAME;
    const static string     DEFAULT_DESCRIPTION;

    string name;
    string description;
};

#endif