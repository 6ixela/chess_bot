#ifndef MOVE_H
#define MOVE_H

#include "game.h"

typedef unsigned int uint;

typedef struct MoveList
{
    Move *move;
    MoveList *next;
} MoveList;


typedef struct Move
{
    uint from;
    uint to;
} Move;

Move *getAllMove(Game *game);
int isValidMove(Game *game, Move *move);

int pawnMove(Game *game, Move *move);
int kingMove(Game *game, Move *move);
int queenMove(Game *game, Move *move);
int rookove(Game *game, Move *move);
int bishopMove(Game *game, Move *move);
int knightMove(Game *game, Move *move);

// void move(Piece *piece, uint src, uint dst);

#endif /* MOVE_H */