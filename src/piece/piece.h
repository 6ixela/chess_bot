#ifndef PIECE_H
#define PIECE_H

enum NamePiece
{
    EMPTY,
    KNIGHT,
    KING,
    QUEEN,
    PAWN,
    BISHOP,
    ROOK,
};

enum COLOR
{
    BLACK,
    WHITE,
};

typedef struct
{
    enum NamePiece name;
    enum COLOR color;
    int value;
} Piece;

int setPiece(Piece *game, char);

#endif /* PIECE_H */