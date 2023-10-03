#include "Item.h"

Item::Item()
    : name("Empty Item"), description("Nothing"), healQuantity(0.0f)
{
}

Item::Item( string name, string description, double healQuantity)
{
    this->setName(name);
    this->setDescription(description);
    this->setHealQuantity(healQuantity);
}

Item::~Item() {}

inline void Item::setName(string name)
{
    if (name.empty())
    {
        this->name = "Empty Item";
        return;
    }

    if (name.size() > Item::MAX_NAME_SIZE)
    {
        this->name = name.substr(0, Item::MAX_NAME_SIZE);
        return;
    }

    this->name = name;
}

inline void Item::setDescription(string description)
{
    if (description.empty())
    {
        this->description = "Nothings";
        return;
    }

    if (description.size() > Item::MAX_DESCRIPTION_SIZE)
    {
        this->description = description.substr(0, Item::MAX_DESCRIPTION_SIZE);
        return;
    }

    this->description = description;
}

inline void Item::setHealQuantity(double healQuantity)
{
    if (healQuantity <= 0)
    {
        this->healQuantity = 0;
        return;
    }
    this->healQuantity = healQuantity;
}
