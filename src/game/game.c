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
            for (int k = 0; k < empty; k++)
            {
                game->board[pos].name = EMPTY;
                pos++;
            }
        }
        else
        {
            setPiece(&game->board[pos], fen[i]);
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
    // Now set bitboard
    createBoard((char *)fen, &game->bitboard);
}

bool bothKingsAlive(const Game *game)
{
    int kingCount = 0;
    for (size_t i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
    {
        if (game->board[i].name == KING)
        {
            kingCount++;
        }
    }
    return kingCount == 2;
}
