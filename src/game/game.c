// parse fen

#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Example FEN: "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
 */

/*
typedef struct
{
    Piece board[BOARD_SIZE * BOARD_SIZE];
    Board bitboard;
    enum COLOR turn;
    char castling[5];
    char en_passant[3];
    int halfmove_clock;
    int fullmove_number;
} Game;
*/

static inline bool valid_square(int sq64)
{
    return sq64 >= 0 && sq64 < BOARD_SIZE * BOARD_SIZE;
}

static void clearSquareBits(Board *board, int sq64)
{
    if (!valid_square(sq64))
    {
        return;
    }
    U64 mask = ~(1ull << sq64);
    board->WPawn &= mask;
    board->BPawn &= mask;
    board->WKing &= mask;
    board->BKing &= mask;
    board->WQueen &= mask;
    board->BQueen &= mask;
    board->WRook &= mask;
    board->BRook &= mask;
    board->WBishop &= mask;
    board->BBishop &= mask;
    board->WKnight &= mask;
    board->BKnight &= mask;
}

void clearSquare(Game *game, int sq64)
{
    clearSquareBits(&game->bitboard, sq64);
}

void setPieceOnGame(Game *game, int sq64, Piece piece)
{
    if (!valid_square(sq64))
    {
        return;
    }

    clearSquare(game, sq64);
    if (piece.name == EMPTY)
    {
        return;
    }

    U64 bit = 1ull << sq64;
    switch (piece.name)
    {
    case PAWN:
        if (piece.color == WHITE)
        {
            game->bitboard.WPawn |= bit;
        }
        else
        {
            game->bitboard.BPawn |= bit;
        }
        break;
    case ROOK:
        if (piece.color == WHITE)
        {
            game->bitboard.WRook |= bit;
        }
        else
        {
            game->bitboard.BRook |= bit;
        }
        break;
    case BISHOP:
        if (piece.color == WHITE)
        {
            game->bitboard.WBishop |= bit;
        }
        else
        {
            game->bitboard.BBishop |= bit;
        }
        break;
    case KNIGHT:
        if (piece.color == WHITE)
        {
            game->bitboard.WKnight |= bit;
        }
        else
        {
            game->bitboard.BKnight |= bit;
        }
        break;
    case QUEEN:
        if (piece.color == WHITE)
        {
            game->bitboard.WQueen |= bit;
        }
        else
        {
            game->bitboard.BQueen |= bit;
        }
        break;
    case KING:
        if (piece.color == WHITE)
        {
            game->bitboard.WKing |= bit;
        }
        else
        {
            game->bitboard.BKing |= bit;
        }
        break;
    default:
        break;
    }
}

Piece getPieceFromGame(const Game *game, int sq64)
{
    Piece piece = {EMPTY, BLACK, 0};
    if (!valid_square(sq64))
    {
        return piece;
    }

    U64 mask = 1ull << sq64;
    if (game->bitboard.WPawn & mask)
    {
        return (Piece){PAWN, WHITE, 0};
    }
    if (game->bitboard.BPawn & mask)
    {
        return (Piece){PAWN, BLACK, 0};
    }
    if (game->bitboard.WRook & mask)
    {
        return (Piece){ROOK, WHITE, 0};
    }
    if (game->bitboard.BRook & mask)
    {
        return (Piece){ROOK, BLACK, 0};
    }
    if (game->bitboard.WBishop & mask)
    {
        return (Piece){BISHOP, WHITE, 0};
    }
    if (game->bitboard.BBishop & mask)
    {
        return (Piece){BISHOP, BLACK, 0};
    }
    if (game->bitboard.WKnight & mask)
    {
        return (Piece){KNIGHT, WHITE, 0};
    }
    if (game->bitboard.BKnight & mask)
    {
        return (Piece){KNIGHT, BLACK, 0};
    }
    if (game->bitboard.WQueen & mask)
    {
        return (Piece){QUEEN, WHITE, 0};
    }
    if (game->bitboard.BQueen & mask)
    {
        return (Piece){QUEEN, BLACK, 0};
    }
    if (game->bitboard.WKing & mask)
    {
        return (Piece){KING, WHITE, 0};
    }
    if (game->bitboard.BKing & mask)
    {
        return (Piece){KING, BLACK, 0};
    }

    return piece;
}

void FEN_to_game(Game *game, const char *fen)
{
    memset(game, 0, sizeof(Game));
    int pos = 0; // position on board, 0 = a8, 63 = h1
    int i = 0;
    // Parse board
    while (fen[i] != ' ')
    {
        if (fen[i] == '/')
        {
            // Skip, ranks are handled by pos increment
        }
        else if (fen[i] >= '1' && fen[i] <= '8')
        {
            int empty = fen[i] - '0';
            pos += empty;
        }
        else
        {
            Piece piece = {EMPTY, BLACK, 0};
            setPiece(&piece, fen[i]);
            setPieceOnGame(game, pos, piece);
            pos++;
        }
        i++;
    }
    i++; // skip space
    // Turn
    game->turn = (fen[i] == 'w') ? WHITE : BLACK;
    i += 2; // skip turn and space
    // Castling
    int j = 0;
    while (fen[i] != ' ')
    {
        game->castling[j++] = fen[i++];
    }
    game->castling[j] = '\0';
    i++; // skip space
    // En passant
    if (fen[i] == '-')
    {
        strcpy(game->en_passant, "-");
        i++;
    }
    else
    {
        game->en_passant[0] = fen[i++];
        game->en_passant[1] = fen[i++];
        game->en_passant[2] = '\0';
    }
    i++; // skip space
    // Halfmove clock
    game->halfmove_clock = atoi(&fen[i]);
    while (fen[i] != ' ') i++;
    i++; // skip space
    // Fullmove number
    game->fullmove_number = atoi(&fen[i]);
}

bool bothKingsAlive(const Game *game)
{
    return __builtin_popcountll(game->bitboard.WKing) == 1 &&
           __builtin_popcountll(game->bitboard.BKing) == 1;
}
