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



int main()
{
    Game game;
    FEN_to_game(&game, "8/8/8/3PBP2/3RqQ2/3RQB2/8/8 w KQkq - 0 1");
    Vector *vector = queenMove(&game, 36);
    print_vector(vector);
    displayMove(&game, vector, 36);
    free_vector(vector);
    return 0;
}