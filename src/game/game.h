#ifndef GAME_H
#define GAME_H

#include "bitBoard.h"
#include "piece.h"

#define BOARD_SIZE 8

typedef struct
{
    Board bitboard;
    enum COLOR turn;
    char castling[5];
    char en_passant[3];
    int halfmove_clock;
    int fullmove_number;
} Game;

void FEN_to_game(Game *game, const char *fen);
bool bothKingsAlive(const Game *game);

Piece getPieceFromGame(const Game *game, int sq64);
void setPieceOnGame(Game *game, int sq64, Piece piece);
void clearSquare(Game *game, int sq64);

#endif /* !GAME_H */