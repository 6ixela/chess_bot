#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "game.h"

typedef enum {
    MODE_BOT_VS_BOT,
    MODE_PLAYER_VS_BOT_WHITE,
    MODE_PLAYER_VS_BOT_BLACK,
} GameMode;

typedef struct {
    Game game;
    GameMode mode;
    int bot_depth;
    int move_count;
    bool is_game_over;
} GameManager;

GameManager *gameManagerCreate(GameMode mode, const char *fen, int bot_depth);
void gameManagerDestroy(GameManager *manager);

/**
 * Execute a bot move for the given color
 * Returns true if a move was made, false if no legal moves exist
 */
bool gameManagerBotMove(GameManager *manager, enum COLOR color);

/**
 * Execute a player move from source to destination
 * Returns true if move was valid and executed, false otherwise
 */
bool gameManagerPlayerMove(GameManager *manager, int src, int dst);

/**
 * Get the current game state
 */
Game *gameManagerGetGame(GameManager *manager);

/**
 * Check if game is over (both kings alive)
 */
bool gameManagerIsGameOver(GameManager *manager);

/**
 * Print game statistics
 */
void gameManagerPrintStats(GameManager *manager);

#endif /* !GAME_MANAGER_H */
