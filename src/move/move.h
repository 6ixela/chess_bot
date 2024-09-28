#ifndef MOVE_H
#define MOVE_H

#include "game.h"
#include "vector.h"

typedef unsigned int uint;

typedef struct Move
{
    uint from;
    uint to;
} Move;

typedef struct MoveList
{
    Move *move;
    struct MoveList *next;
} MoveList;

Move *getAllMove(Game *game);
int isValidMove(Game *game, Move *move);

Vector *pawnMove(Game *game, Move *move);
Vector *kingMove(Game *game, uint src);
Vector *queenMove(Game *game, Move *move);
Vector *rookMove(Game *game, Move *move);
Vector *bishopMove(Game *game, Move *move);
Vector *knightMove(Game *game, Move *move);

// void move(Piece *piece, uint src, uint dst);

#endif /* MOVE_H */