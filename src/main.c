/*
char *recupPiece(struct piece *p);

void printMove(struct piece *p)
{
    for (size_t i = 0; (int)i < p->nbMoves; i++)
    {
        printf("move %ld = %i\n", i, p->possibleMoves[i]);
    }
}

void print_chess(struct piece **tab)
{
    printf("_________________\n");
    for(size_t i = 0; i < 8; i++)
    {
        printf("|");
        for (size_t j = 0; j < 8; j++)
        {
            char *p = recupPiece(tab[i * 8 + j]);
            if (tab[i * 8 + j] != NULL && !tab[i * 8 + j]->isWhite)
            {
                printf("\033[0;32m");
                printf("%s", p);
                printf("\033[0m");
                printf("|");
            }
            else
                printf("%s|", p);
        }
        printf("\n");
    }
    printf("_________________\n");
}

char *recupPiece(struct piece *p)
{
    char *res = " ";
    if(p == NULL)
        res = " ";
    else
    {
        if(p->name == 'p')
            res = "♙";
        else if (p->name == 'n')
            res = "♘";
        else if (p->name == 'b')
            res = "♗";
        else if (p->name == 'r')
            res = "♖";
        else if (p->name == 'q')
            res = "♕";
        else if(p->name == 'k')
            res = "♔";
    }
    return res;
}

//rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
*/

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