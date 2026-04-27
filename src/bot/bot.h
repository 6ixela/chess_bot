#ifndef BOT_H
#define BOT_H

#include "game.h"

int evalBoard(const Game *game);

int alphaBeta(Game *game, int depth, int alpha, int beta,
              enum COLOR isWhite, int *startPos, int *destPos,
              int returnMove);
#endif /* BOT_H */