#include "display.h"

#include "stdio.h"

static char inVector(Vector *vector, int value)
{
    if (vector)
    {
        for (size_t i = 0; i < vector->size; i++)
        {
            if (vector->data[i] == value)
            {
                return 1;
            }
        }
    }
    return 0;
}

void displayMove(const Game *game, Vector *vector, u_int src)
{
    size_t cpt = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            u_int index = i * BOARD_SIZE + j;

            if (inVector(vector, index))
            {
                cpt++;
                printf(RED);
            }
            else
            {
                if (index == src)
                {
                    printf(GREEN);
                }
                else
                {
                    printf(RESET);
                }
            }

            switch (game->board[index].name)
            {
            case EMPTY:
                printf(". ");
                break;
            case PAWN:
                printf("%c ", game->board[index].color == WHITE ? 'P' : 'p');
                break;
            case ROOK:
                printf("%c ", game->board[index].color == WHITE ? 'R' : 'r');
                break;
            case KNIGHT:
                printf("%c ", game->board[index].color == WHITE ? 'N' : 'n');
                break;
            case BISHOP:
                printf("%c ", game->board[index].color == WHITE ? 'B' : 'b');
                break;
            case QUEEN:
                printf("%c ", game->board[index].color == WHITE ? 'Q' : 'q');
                break;
            case KING:
                printf("%c ", game->board[index].color == WHITE ? 'K' : 'k');
                break;
            }
        }
        printf(RESET "\n"); // Réinitialiser la couleur à la fin de la ligne
    }
    printf("\n");
    if (vector && cpt != vector->size)
    {
        fprintf(stderr, "Error, too much move\n");
    }
}