#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

using std::cout;
using std::string;

/* HEALING ITEM - Mudar para herança e overload depois! */

class Item
{
public:
    Item();
    Item( string, string, double );
    ~Item();
    
    inline string getName()         const { return this->name;          }
    inline string getDescription()  const { return this->description;   }
    inline double getHealQuantity() const { return this->healQuantity;  }

    void setName            ( string );
    void setDescription     ( string );
    void setHealQuantity    ( double );
private:
    const static u_int8_t MAX_ITEM_STACK;
    const static size_t MAX_NAME_SIZE = 20;
    const static size_t MAX_DESCRIPTION_SIZE = 60;

    string name;
    string description;
    double healQuantity;
};

#endif