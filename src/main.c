#include <stdio.h>

#include "game.h"
#include "move.h"
#include "vector.h"
#include "display.h"
#include "bot.h"
#include <limits.h>

int kingDead(Game *game)
{
    int twoKings = 0;
    for (size_t i = 0; i < 64; i++)
    {
        if (game->board[i].name == KING)
        {
            twoKings++;
        }
    }
    return twoKings == 2;
}

int main()
{
    Game game;
    FEN_to_game(&game, "2kr3r/pp2bppp/2p1bq2/8/4QB2/2PB4/PPP2PPP/3RR1K1 w ____ - 0 1");
    // FEN_to_game(&game, "r1bq1k1r/pppp3p/1b1P1pnp/6B1/2B5/5N1P/PP2QPP1/RN2K2R w ____ - 0 1");
    enum COLOR color = WHITE;
    while (kingDead(&game))
    {
        displayMove(&game, NULL, 4);
        int src;
        int dst;
        Move move;
        alphaBeta(&game, 5, INT_MIN, INT_MAX, 0, WHITE, &src, &dst, 1);
        createMove(&game, src, dst, &move);
        Vector *vector = getMoveFromPiece(&game, src);
        doMovement(&game, &move);
        free_vector(vector);
        color = color == WHITE ? BLACK : WHITE;
    }
    displayMove(&game, NULL, 4);
    
    return 0;
}