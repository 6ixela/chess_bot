#include "bot.h"

#include <stdlib.h>

int evalBoard(Game *game)
{
    
    int res = 0;
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE; j++)
        {
            Piece piece = game->board[i * 8 + j];

            if (piece.name == EMPTY)
                continue;
            char color = piece.color == WHITE ? -1 : 1;

            res += piece.value * color;
        }
    }
    return res;
}