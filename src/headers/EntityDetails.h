#ifndef ENTITY_DETAILS_H
#define ENTITY_DETAILS_H

#include "Item.h"
#include <string>

/* Item dentro de um inventário */
struct InventoryItem
{
    Item* item;          // Item
    short quantity;     // Quantidade do Item
};


/* Parte do corpo do inimigo. Varia de inimigo para inimigo. */
struct BodyPart
{
    string partDescription;     // Nome da parte do corpo. Mostrada na batalha.
    double damageModifier;      // Modificador de dano, em porcentagem
};

#endif