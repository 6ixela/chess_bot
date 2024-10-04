#ifndef DISPLAY_H
#define DISPLAY_H

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"

#include "game.h"
#include "vector.h"

void displayMove(const Game *game, Vector *vector);

#endif /* !DISPLAY_H */