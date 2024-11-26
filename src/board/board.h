#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

#define BOARD_SIZE 8

typedef uint64_t Bitboard;

typedef struct {
    Bitboard white_pawns;
    Bitboard white_knights;
    Bitboard white_bishops;
    Bitboard white_rooks;
    Bitboard white_queens;
    Bitboard white_king;
    Bitboard black_pawns;
    Bitboard black_knights;
    Bitboard black_bishops;
    Bitboard black_rooks;
    Bitboard black_queens;
    Bitboard black_king;
} Board;

void init_board(Board *board);
Bitboard get_all_white_pieces(const Board *board);
Bitboard get_all_black_pieces(const Board *board);
Bitboard get_all_pieces(const Board *board);

#endif /* BOARD_H */