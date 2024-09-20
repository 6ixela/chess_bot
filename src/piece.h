#ifndef PIECE_H
#define PIECE_H

enum NamePiece
{
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
    enum COLOR color; // 0 is for white and 1 for black
    int value;
} piece;

struct piece *createPiece(char name);
void freePiece(struct piece *piece);

#endif /* PIECE_H */