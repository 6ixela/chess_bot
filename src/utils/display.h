#ifndef DISPLAY_H
#define DISPLAY_H

#define RESET "\033[0m"
#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_BLUE "\033[34m"
#define ANSI_WHITE "\033[97m"
#define ANSI_BG_RED "\033[41m"
#define ANSI_BG_GREEN "\033[42m"
#define CYAN "\033[36m"

#include "game.h"
#include "vector.h"

void displayMove(const Game *game, Vector *vector, unsigned int src);

#endif /* !DISPLAY_H */