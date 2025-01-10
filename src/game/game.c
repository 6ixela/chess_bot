// parse fen

#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Example FEN: "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
 */
void initializeGame(Game *game)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            game->board[i * 8 + j].name = EMPTY;
            game->board[i * 8 + j].color = WHITE; // Valeur par défaut
            game->board[i * 8 + j].color = 0;
        }
    }
    game->turn = WHITE;
    strcpy(game->castling, "KQkq");
    game->en_passant[0] = '\0';
    game->halfmove_clock = 0;
    game->fullmove_number = 1;
}

void FEN_to_game(Game *game, const char *fen)
{
    // TODO complete if uncomplete FEN
    initializeGame(game);
    int row = 0;
    int col = 0;
    const char *c = fen;
    for (; *c != ' '; c++)
    {
        if (*c >= '1' && *c <= '8')
        {
            int emptySquares = *c - '0';
            col += emptySquares;
        }
        else if (*c == '/')
        {
            row++;
            col = 0;
        }
        else
        {
            setPiece(&(game->board[row * 8 + col]), *c);
            col++;
        }
    }
    while (*c && *c == ' ')
        c++;
    game->turn = (*(c++) == 'w') ? WHITE : BLACK;

    while (*c && *c == ' ')
        c++;
    strncpy(game->castling, c, 4);
    game->castling[4] = '\0';
    c+=4;

    while (*c && *c == ' ')
        c++;
    strncpy(game->en_passant, c, 2);
    game->en_passant[2] = '\0';
    c+=2;

    while (*c && *c == ' ')
        c++;
    game->halfmove_clock = atoi(c);
    
    while (*c && *c != ' ')
        c++;
    game->fullmove_number = atoi(c);
}