#ifndef BOT_H
#define BOT_H

#include "game.h"

int evalBoard(Game *game);
int minmax(Game *game, int depth, enum COLOR isWhite, int returnMove,
           int *start, int *dest);

int alphaBeta(Game *game, int depth, int alpha, int beta, int maximazing,
              enum COLOR isWhite, int *startPos, int *destPos, int returnMove);
#endif /* BOT_H */