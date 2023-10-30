#ifndef ENTITY_DETAILS_H
#define ENTITY_DETAILS_H

#include "Item.h"
#include <string>

/* Direcao na qual a entidade se move */
enum Direction
{
    DOWN,
    UP,
    RIGHT,
    LEFT
};

/* Item dentro de um inventário */
struct InventoryItem
{
    Item item;          // Item
    short quantity;     // Quantidade do Item
};

/* Posicao da Entidade no plano */
struct Vector2D
{
    int x;
    int y;
};

/* Parte do corpo do inimigo. Varia de inimigo para inimigo. */
struct BodyPart
{
    string partDescription;     // Nome da parte do corpo. Mostrada na batalha.
    double damageModifier;      // Modificador de dano, em porcentagem
};

#endif