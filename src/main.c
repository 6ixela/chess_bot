#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#include "bot.h"
#include "display.h"
#include "game.h"
#include "move.h"

int main(void)
{
    Game game;
    FEN_to_game(&game,
               "r4rk1/ppq2Np1/1n1pb3/2p4p/8/3B2Q1/PPPB2PP/5R1K b KQkq - 0 1");
    game.turn = WHITE;
    while (bothKingsAlive(&game))
    {
        displayMove(&game, NULL, UINT_MAX);

        int src = -1;
        int dst = -1;
        alphaBeta(&game, 7, INT_MIN, INT_MAX, game.turn, &src, &dst, 1);
        if (src < 0 || dst < 0)
        {
            break;
        }

        Move move;
        createMove(&game, src, dst, &move);
        doMovement(&game, &move);
        game.turn = (game.turn == WHITE) ? BLACK : WHITE;
    }
    displayMove(&game, NULL, 4);
    
    return 0;
}