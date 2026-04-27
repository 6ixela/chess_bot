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

void displayMove(const Game *game, Vector *vector, unsigned int src)
{
    size_t cpt = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            unsigned int index = i * BOARD_SIZE + j;

            const char *fg_color = NULL;
            const char *bg_color = RESET;

            if (inVector(vector, index))
            {
                cpt++;
                bg_color = ANSI_BG_RED;
            }
            else if (index == src)
            {
                bg_color = ANSI_BG_GREEN;
            }

            if (game->board[index].name != EMPTY)
            {
                fg_color = game->board[index].color == WHITE ? ANSI_WHITE : ANSI_BLUE;
            }

            printf("%s", bg_color);
            if (fg_color)
            {
                printf("%s", fg_color);
            }

            switch (game->board[index].name)
            {
            case EMPTY:
                printf(". ");
                break;
            case PAWN:
                printf("%s ", game->board[index].color == WHITE ? "♙" : "♟");
                break;
            case ROOK:
                printf("%s ", game->board[index].color == WHITE ? "♖" : "♜");
                break;
            case KNIGHT:
                printf("%s ", game->board[index].color == WHITE ? "♘" : "♞");
                break;
            case BISHOP:
                printf("%s ", game->board[index].color == WHITE ? "♗" : "♝");
                break;
            case QUEEN:
                printf("%s ", game->board[index].color == WHITE ? "♕" : "♛");
                break;
            case KING:
                printf("%s ", game->board[index].color == WHITE ? "♔" : "♚");
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