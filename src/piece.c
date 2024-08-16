#include "piece.h"

#include <ctype.h>
#include <stdlib.h>

static int checkName(char name)
{
    char n = tolower(name);
    if (n == 'p' || n == 'r' || n == 'n' || n == 'b' ||
        n == 'q' || n == 'k')
    {
        return 1;
    }
    return 0;
}

void determinePiece(char name, struct piece* piece)
{
    char n = tolower(name);
    switch (n)
    {
    case 'p':
        piece->name = PAWN;
        piece->value = 10;
        break;
    case 'r':
        piece->name = ROOK;
        piece->value = 50;
        break;
    case 'n':
        piece->name = KNIGHT;
        piece->value = 30;
        break;
    case 'b':
        piece->name = BISHOP;
        piece->value = 30;
        break;
    case 'q':
        piece->name = QUEEN;
        piece->value = 100;
        break;
    default:
        piece->name = KING;
        piece->value = 1000;
        break;
    }
}

struct piece* createPiece(char name)
{
    if (!checkName(name))
    {
        return NULL;
    }
    
    struct piece* piece = malloc(sizeof(struct piece));
    piece->color = isupper(name) ? 1 : 0;
    determinePiece(name, piece);
    return piece;
}

void freePiece(struct piece* piece)
{
    free(piece);
}