#ifndef ESSENTIAL_STRUCTS_H
#define ESSENTIAL_STRUCTS_H

/* Posicao da Entidade no plano */
struct Vector2D
{
    int x;
    int y;
};

/* Direcao na qual a entidade se move */
enum Direction
{
    DOWN,
    UP,
    RIGHT,
    LEFT
};

#endif