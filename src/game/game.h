#ifndef GAME_H
#define GAME_H

#include "piece.h"

typedef struct
{
    piece board[8][8];
    char turn;
    char castling[5];
    char en_passant[3];
    int halfmove_clock;
    int fullmove_number;
} Game;

#endif /* !GAME_H */