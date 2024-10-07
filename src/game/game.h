#ifndef GAME_H
#define GAME_H

#include "piece.h"

#define BOARD_SIZE 8

typedef struct
{
    Piece board[BOARD_SIZE * BOARD_SIZE];
    char turn;
    char castling[5];
    char en_passant[3];
    int halfmove_clock;
    int fullmove_number;
} Game;


void FEN_to_game(Game *game, const char *fen);

#endif /* !GAME_H */