#ifndef MOVE_H
#define MOVE_H

#include "game.h"
#include "vector.h"

typedef unsigned int u_int;
typedef unsigned char uchar;

typedef struct Move
{
    u_int from;
    u_int to;
} Move;

typedef struct MoveList
{
    Move *move;
    struct MoveList *next;
} MoveList;

Move *getAllMove(Game *game);
int isValidMove(Game *game, Move *move);

Vector *pawnMove(Game *game, u_int src);
Vector *kingMove(Game *game, u_int src);
Vector *queenMove(Game *game, u_int src);
Vector *rookMove(Game *game, u_int move);
Vector *bishopMove(Game *game, u_int src);
Vector *knightMove(Game *game, u_int src);

// void move(Piece *piece, u_int src, u_int dst);

#endif /* MOVE_H */