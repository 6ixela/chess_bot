#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

/**
 * Parse algebraic chess notation (e.g., "e2e4") to board indices
 * Returns true if valid, false otherwise
 * src and dst are set to the corresponding square indices (0-63)
 */
bool parseAlgebraicMove(const char *notation, int *src, int *dst);

/**
 * Convert board index (0-63) to algebraic notation (e.g., "e2")
 */
void indexToAlgebraic(int index, char *notation);

/**
 * Get user input for a move in algebraic notation
 * Returns the input string (allocated by this function)
 */
char *getUserMoveInput(void);

/**
 * Display the current player's turn and request input
 */
void displayPlayerPrompt(int turn);

/**
 * Display available commands for the player
 */
void displayHelpMessage(void);

#endif /* !INPUT_H */
