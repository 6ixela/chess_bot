#include "piece.h"

#include <ctype.h>
#include <stdlib.h>

static int checkName(char name)
{
    char n = tolower(name);
    if (n == 'p' || n == 'r' || n == 'n' || n == 'b' || n == 'q' || n == 'k')
    {
        return 1;
    }
    return 0;
}

static void determinePiece(Piece *piece, char namePiece)
{
    char n = tolower(namePiece);
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
        piece->value = 200;
        break;
    default:
        piece->name = KING;
        piece->value = 10000;
        break;
    }
}

int setPiece(Piece *piece, char namePiece)
{

    if (!checkName(namePiece))
    {
        return 0;
    }

    piece->color = isupper(namePiece) ? WHITE : BLACK;
    determinePiece(piece, namePiece);
    return 1;
}