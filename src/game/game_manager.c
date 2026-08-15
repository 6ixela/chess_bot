#include "game_manager.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "bot.h"
#include "move.h"

GameManager *gameManagerCreate(GameMode mode, const char *fen, int bot_depth)
{
    GameManager *manager = malloc(sizeof(GameManager));
    if (!manager)
        return NULL;

    FEN_to_game(&manager->game, fen);
    manager->mode = mode;
    manager->bot_depth = bot_depth;
    manager->move_count = 0;
    manager->is_game_over = false;

    return manager;
}

void gameManagerDestroy(GameManager *manager)
{
    if (manager)
        free(manager);
}

bool gameManagerBotMove(GameManager *manager, enum COLOR color)
{
    if (!manager || color != manager->game.turn)
        return false;

    int src = -1;
    int dst = -1;

    alphaBeta(&manager->game, manager->bot_depth, INT_MIN, INT_MAX,
              color, &src, &dst, 1);

    if (src < 0 || dst < 0)
    {
        manager->is_game_over = true;
        return false;
    }

    Move move;
    createMove(&manager->game, src, dst, &move);
    doMovement(&manager->game, &move);
    manager->game.turn = (manager->game.turn == WHITE) ? BLACK : WHITE;
    manager->move_count++;

    return true;
}

bool gameManagerPlayerMove(GameManager *manager, int src, int dst)
{
    if (!manager || src < 0 || src >= 64 || dst < 0 || dst >= 64)
        return false;

    Move move;
    createMove(&manager->game, src, dst, &move);
    doMovement(&manager->game, &move);
    manager->game.turn = (manager->game.turn == WHITE) ? BLACK : WHITE;
    manager->move_count++;

    return true;
}

Game *gameManagerGetGame(GameManager *manager)
{
    return manager ? &manager->game : NULL;
}

bool gameManagerIsGameOver(GameManager *manager)
{
    if (!manager)
        return true;

    return bothKingsAlive(&manager->game);
}

void gameManagerPrintStats(GameManager *manager)
{
    if (!manager)
        return;

    printf("\n=== Game Statistics ===\n");
    printf("Number of moves played: %d\n", manager->move_count);
    printf("Game mode: ");
    switch (manager->mode)
    {
    case MODE_BOT_VS_BOT:
        printf("Bot vs Bot (depth: %d)\n", manager->bot_depth);
        break;
    case MODE_PLAYER_VS_BOT_WHITE:
        printf("Player (white) vs Bot (depth: %d)\n", manager->bot_depth);
        break;
    case MODE_PLAYER_VS_BOT_BLACK:
        printf("Bot (depth: %d) vs Player (black)\n", manager->bot_depth);
        break;
    }
    printf("Game over: %s\n", manager->is_game_over ? "Yes" : "No");
}
