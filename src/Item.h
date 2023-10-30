#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

using std::cout;
using std::string;
using std::ostream;

class Item
{
    friend ostream& operator<<  ( ostream&, const Item& );
    friend int      operator!   ( const Item& );
public:
    Item    ( );
    Item    ( string, string, double );
    Item    ( const Item& );
    ~Item   ( );
    
    inline string getName()         const { return this->name;          }
    inline string getDescription()  const { return this->description;   }
    inline double getHealQuantity() const { return this->healQuantity;  }

    void setName            ( string );
    void setDescription     ( string );
    void setHealQuantity    ( double );

    const Item& operator= ( const Item& );
    int operator== ( const Item& );
    int operator!= ( const Item& );

private:
    const static u_int8_t   MAX_ITEM_STACK;
    const static size_t     MAX_NAME_SIZE;
    const static size_t     MAX_DESCRIPTION_SIZE;
    const static string     DEFAULT_ITEM_NAME;
    const static string     DEFAULT_DESCRIPTION;

    string name;
    string description;
    double healQuantity;
};

#endif