#ifndef PIECE_H
#define PIECE_H

enum NamePiece {
    KNIGHT,
    KING,
    QUEEN,
    PAWN,
    BISHOP,
    ROOK,
};

struct piece
{
    enum NamePiece name;
    char color; // 0 is for white and 1 for black
    int value;
};

struct piece* createPiece(char name);
void freePiece(struct piece* piece);


#endif /* PIECE_H */