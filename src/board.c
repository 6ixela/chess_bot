// bouger les pieces

#include "board.h"
#include "piece.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

struct board* fenToBoard(char *fen)
{
    struct piece **board = malloc(64 * sizeof(struct piece *));
    size_t iBoard = 0;
    size_t i = 0;
    while(fen[i] != 0)
    {
        char letter = fen[i];
        // if i got a number
        if(letter - '0' >= 0 && letter - '0' <= 9)
        {
            for (size_t j = 0; j < (size_t)letter - '0'; j++)
            {
                board[iBoard] = NULL;
                iBoard++;
            }
        }
        else
        {
            char c = letter;
            int isWhite = 0;
            if(isupper(c))
            {
                isWhite = 1;
                c = tolower(c);
            }
            switch (c)
            {
            case 'r':
                board[iBoard] = createPiece('r');
                break;
            case 'k':
                board[iBoard] = createPiece('k');
                break;
            case 'q':
                board[iBoard] = createPiece('q');
                break;
            case 'n':
                board[iBoard] = createPiece('n');
                break;
            case 'b':
                board[iBoard] = createPiece('b');
                break;
            case 'p':
                board[iBoard] = createPiece('p');
                break;
            case '/':
                i++;
                continue;
            default:
                printf("erreur notation fen : %c at i = %ld\n", c, i);
                return NULL;
            }
            board[iBoard]->color = isWhite;
            iBoard++;
        }

        i++;
    }
    struct board* b = malloc(sizeof(struct board));
    b->board = board;
    return b;
}

struct board* createBoard()
{
    return fenToBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

static int countNull(struct board* board, size_t i, size_t* j)
{
    int counted = 0;
    while (*j < 8 && !board->board[i * 8 + *j])
    {
        *j += 1;
        counted += 1;
    }
    return counted;
}

char getName(struct piece *piece)
{
    enum NamePiece namePiece = piece->name;
    char name;
    switch (namePiece)
    {
    case PAWN:
        name = 'p';
        break;
    case ROOK:
        name = 'r';
        break;
    case QUEEN:
        name = 'q';
        break;
    case KING:
        name = 'k';
        break;
    case KNIGHT:
        name = 'n';
        break;
    case BISHOP:
        name = 'b';
        break;
    }
    name = piece->color ? toupper(name) : name;
    return name;
}

char* boardToFen(struct board* board)
{
    char* fen = calloc(72, sizeof(char));
    int i_str = 0;
    for (size_t i = 0; i < 8; i++)
    {
        size_t j = 0;
        for (; j < 8; j++)
        {
            if (board->board[i * 8 + j] == NULL)
            {
                fen[i_str] = '0' + countNull(board, i, &j);
            }
            else
            {
                fen[i_str] = getName(board->board[i * 8 + j]);
            }
            i_str++;
        }
        fen[i_str] = '/';
        i_str++;
    }
    fen[i_str - 1] = 0;
    return fen;
}

void freeBoard(struct board* board)
{
    if (!board || !board->board)
    {
        return;
    }
    
    for (size_t i = 0; i < 64; i++)
    {
        struct piece* p = board->board[i];
        if (p)
        {
            freePiece(p);
        }
    }
    free(board->board);
    free(board);
}