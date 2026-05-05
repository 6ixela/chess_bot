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
    unsigned int from;
    unsigned int to;
    Piece piece_captured;

} Move;

void undoMovement(Game *game, Move* move);
void doMovement(Game *game, Move* move);
void createMove(Game *game, unsigned int src, unsigned int dst, Move *move);

void initMoveStruct(Move *move, unsigned int from, unsigned int to);

Vector *getMoveFromPiece(Game *game, unsigned int src);
Vector *pawnMove(Game *game, unsigned int src);
Vector *kingMove(Game *game, unsigned int src);
Vector *queenMove(Game *game, unsigned int src);
Vector *rookMove(Game *game, unsigned int move);
Vector *bishopMove(Game *game, unsigned int src);
Vector *knightMove(Game *game, unsigned int src);

// void move(Piece *piece, unsigned int src, unsigned int dst);

#endif /* MOVE_H */