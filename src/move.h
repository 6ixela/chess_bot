#ifndef MOVE_H
#define MOVE_H

#include "piece.h"

typedef unsigned int uint;

void move(struct piece *piece, uint src, uint dst);

#endif /* MOVE_H */