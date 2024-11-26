#include "board.h"

void init_board(Board *board) {
    board->white_pawns   = 0x000000000000FF00ULL;
    board->white_knights = 0x0000000000000042ULL;
    board->white_bishops = 0x0000000000000024ULL;
    board->white_rooks   = 0x0000000000000081ULL;
    board->white_queens  = 0x0000000000000008ULL;
    board->white_king    = 0x0000000000000010ULL;
    board->black_pawns   = 0x00FF000000000000ULL;
    board->black_knights = 0x4200000000000000ULL;
    board->black_bishops = 0x2400000000000000ULL;
    board->black_rooks   = 0x8100000000000000ULL;
    board->black_queens  = 0x0800000000000000ULL;
    board->black_king    = 0x1000000000000000ULL;
}

Bitboard get_all_white_pieces(const Board *board) {
    return board->white_pawns | board->white_knights | board->white_bishops |
           board->white_rooks | board->white_queens | board->white_king;
}

Bitboard get_all_black_pieces(const Board *board) {
    return board->black_pawns | board->black_knights | board->black_bishops |
           board->black_rooks | board->black_queens | board->black_king;
}

Bitboard get_all_pieces(const Board *board) {
    return get_all_white_pieces(board) | get_all_black_pieces(board);
}