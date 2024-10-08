#ifndef MOVE_H
#define MOVE_H

#include "game.h"
#include "vector.h"

typedef enum {
    MOVEMENT,
    CAPTURE,
    PROMOTION,
    CASTLE,
} MoveType;

typedef struct Move
{
    MoveType moveType;
    u_int from;
    u_int to;
    Piece piece_captured;

} Move;

void initMoveStruct(Move *move, u_int from, u_int to);

Vector *getMoveFromPiece(Game *game, u_int src);
Vector *pawnMove(Game *game, u_int src);
Vector *kingMove(Game *game, u_int src);
Vector *queenMove(Game *game, u_int src);
Vector *rookMove(Game *game, u_int move);
Vector *bishopMove(Game *game, u_int src);
Vector *knightMove(Game *game, u_int src);

// void move(Piece *piece, u_int src, u_int dst);

#endif /* MOVE_H */