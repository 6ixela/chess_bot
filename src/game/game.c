// parse fen

#include "game.h"

#include <stdlib.h>
#include <string.h>

Game *create_game_from_fen(char *fen)
{
    Game *game = malloc(sizeof(Game));
    game->turn = 'w';
    strcpy(game->castling, "");
    strcpy(game->en_passant, "-");
    game->halfmove_clock = 0;
    game->fullmove_number = 0;
    return game;
}

void free_game(Game *game)
{
    free(game);
}