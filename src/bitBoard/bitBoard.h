#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdlib.h>

typedef char err;
typedef size_t U64;
typedef char bool;
typedef struct Board
{
    U64 WPawn;
    U64 BPawn;
    U64 WKing;
    U64 BKing;
    U64 WQueen;
    U64 BQueen;
    U64 WRook;
    U64 BRook;
    U64 WBishop;
    U64 BBishop;
    U64 WKnight;
    U64 BKnight;
} Board;

inline U64 getWhite(Board *board)
{
    return board->WBishop | board->WKing | board->WKnight | board->WPawn | board->WQueen | board->WRook;
}

inline U64 getBlack(Board *board)
{
    return board->BBishop | board->BKing | board->BKnight | board->BPawn | board->BQueen | board->BRook;
}

err createBoard(char *fen, Board *board);
void printBitBoard(Board *board);

void set_bit(U64 *bb, int i);
void clear_bit(U64 *bb, int i);
U64 get_bit(U64 *bb, int i);

// get_pos
// mov east
// move west
// move north
// move south

#endif /* !BITBOARD_H */