#include "Item.h"

const u_int8_t  Item::MAX_ITEM_STACK        = 99;
const size_t    Item::MAX_NAME_SIZE         = 20;
const size_t    Item::MAX_DESCRIPTION_SIZE  = 60;
const string    Item::DEFAULT_ITEM_NAME     = "Empty Item";
const string    Item::DEFAULT_DESCRIPTION   = "Nothing";

Item::Item() : Interactable()
{
    this->name = Item::DEFAULT_ITEM_NAME;
    this->description = Item::DEFAULT_DESCRIPTION;
}

Item::Item( string name, string description) : Interactable()
{
    this->setName(name);
    this->setDescription(description);
}

Item::Item( const Item& other ) : Interactable( other )
{
    this->name = other.name;
    this->description = other.description;
}

Item::~Item() {}

#pragma region Setters

void Item::setName(string name)
{
    if (name.empty())
    {
        this->name = Item::DEFAULT_ITEM_NAME;
        return;
    }

    if (name.size() > Item::MAX_NAME_SIZE)
    {
        this->name = name.substr(0, Item::MAX_NAME_SIZE);
        return;
    }

    this->name = name;
}

void Item::setDescription(string description)
{
    if (description.empty())
    {
        this->description = Item::DEFAULT_DESCRIPTION;
        return;
    }

    if (description.size() > Item::MAX_DESCRIPTION_SIZE)
    {
        this->description = description.substr(0, Item::MAX_DESCRIPTION_SIZE);
        return;
    }

    this->description = description;
}

#pragma endregion

#pragma region OperatorOverloads

ostream& operator<< ( ostream& output, const Item& item )
{
    output << item.name << " | " << item.description;
    return output;
}

int operator! ( const Item& right )
{
    return !(right.name.empty() || right.name == Item::DEFAULT_ITEM_NAME);
}

const Item& Item::operator= ( const Item& right )
{
    if (&right != this)
    {
        static_cast<Interactable> (*this) = static_cast<Interactable> (right);
        this->name = right.name;
        this->description = right.description;
    }
    return *this;
}

int Item::operator== ( const Item& right )
{    
    if (this->name == right.name)
        return 1;
    return 0;
}

int Item::operator!= (const Item& right)
{
    return !( *this == right );
}

#pragma endregion