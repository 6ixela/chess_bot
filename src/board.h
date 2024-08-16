#ifndef BOARD_H
#define BOARD_H

#include "piece.h"

struct board
{
    struct piece** board; 
};

struct board* createBoard();
struct board* fenToBoard(char *fen);
char* boardToFen(struct board* board);

void freeBoard(struct board* board);

#endif /* BOARD_H */