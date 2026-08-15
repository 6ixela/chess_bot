#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bot.h"
#include "display.h"
#include "game.h"
#include "game_manager.h"
#include "input.h"
#include "move.h"

// Game mode selection
static GameMode selectGameMode(void)
{
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║       Chess Game - Mode Selection       ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    printf("1. Bot vs Bot (watch two bots play)\n");
    printf("2. Player (White) vs Bot\n");
    printf("3. Bot vs Player (Black)\n");
    printf("\nChoose a mode (1-3): ");
    fflush(stdout);

    int choice;
    if (scanf("%d", &choice) != 1)
    {
        return MODE_BOT_VS_BOT;
    }

    switch (choice)
    {
    case 1:
        return MODE_BOT_VS_BOT;
    case 2:
        return MODE_PLAYER_VS_BOT_WHITE;
    case 3:
        return MODE_PLAYER_VS_BOT_BLACK;
    default:
        return MODE_BOT_VS_BOT;
    }
}

// Get difficulty level
static int selectBotDepth(void)
{
    printf("\nChoose bot depth (1-7, default: 5): ");
    fflush(stdout);

    int depth;
    if (scanf("%d", &depth) != 1 || depth < 1 || depth > 7)
    {
        return 5;
    }

    return depth;
}

// Clear input buffer
static void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Play bot vs bot mode
static void playBotVsBot(GameManager *manager)
{
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║       Bot vs Bot - Game in Progress    ║\n");
    printf("╚════════════════════════════════════════╝\n");

    int move_count = 0;
    while (gameManagerIsGameOver(manager) && move_count < 200)
    {
        displayMove(gameManagerGetGame(manager), NULL, UINT_MAX);

        enum COLOR current_color = gameManagerGetGame(manager)->turn;
        if (!gameManagerBotMove(manager, current_color))
        {
            printf("\nNo legal moves available. Game is over.\n");
            break;
        }

        move_count++;
        printf("Move %d played (%s).\n", move_count,
               current_color == WHITE ? "White" : "Black");
    }

    displayMove(gameManagerGetGame(manager), NULL, 4);
    gameManagerPrintStats(manager);
}

// Play player vs bot mode
static void playPlayerVsBot(GameManager *manager)
{
    GameMode mode = manager->mode;
    enum COLOR player_color =
        (mode == MODE_PLAYER_VS_BOT_WHITE) ? WHITE : BLACK;
    enum COLOR bot_color = (mode == MODE_PLAYER_VS_BOT_WHITE) ? BLACK : WHITE;

    printf("\n╔════════════════════════════════════════╗\n");
    printf("║   Player vs Bot - Game in Progress     ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("\nYou play as %s.\n\n",
           player_color == WHITE ? "White" : "Black");

    displayHelpMessage();

    int move_count = 0;
    while (gameManagerIsGameOver(manager) && move_count < 200)
    {
        displayMove(gameManagerGetGame(manager), NULL, UINT_MAX);

        Game *game = gameManagerGetGame(manager);
        enum COLOR current_color = game->turn;

        if (current_color == player_color)
        {
            // Player's turn
            displayPlayerPrompt(player_color);
            bool valid_move = false;

            while (!valid_move)
            {
                char *input = getUserMoveInput();
                if (!input)
                {
                    continue;
                }

                // Check for commands
                if (strcmp(input, "help") == 0)
                {
                    displayHelpMessage();
                    free(input);
                    displayPlayerPrompt(player_color);
                    continue;
                }
                else if (strcmp(input, "quit") == 0)
                {
                    printf("Game abandoned.\n");
                    free(input);
                    return;
                }

                int src = -1;
                int dst = -1;
                if (parseAlgebraicMove(input, &src, &dst))
                {
                    if (gameManagerPlayerMove(manager, src, dst))
                    {
                        valid_move = true;
                        printf("Valid move played: %s -> %s\n", input,
                               input + 2);
                    }
                    else
                    {
                        printf("Invalid move. Try again.\n");
                        displayPlayerPrompt(player_color);
                    }
                }
                else
                {
                    printf("Invalid format. Use algebraic notation "
                           "(e.g., e2e4).\n");
                    displayPlayerPrompt(player_color);
                }

                free(input);
            }
        }
        else
        {
            // Bot's turn
            printf("\nBot is playing... (depth: %d)\n", manager->bot_depth);
            if (!gameManagerBotMove(manager, bot_color))
            {
                printf("\nNo legal moves available. Bot is checkmate.\n");
                break;
            }
        }

        move_count++;
    }

    displayMove(gameManagerGetGame(manager), NULL, 4);
    gameManagerPrintStats(manager);
}

int main(void)
{
    // Select game mode
    GameMode mode = selectGameMode();
    clearInputBuffer();

    // Select difficulty
    int bot_depth = selectBotDepth();
    clearInputBuffer();

    // Create game manager with standard starting position
    const char *fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    GameManager *manager = gameManagerCreate(mode, fen, bot_depth);

    if (!manager)
    {
        printf("Error: failed to create game.\n");
        return 1;
    }

    // Play based on selected mode
    switch (mode)
    {
    case MODE_BOT_VS_BOT:
        playBotVsBot(manager);
        break;
    case MODE_PLAYER_VS_BOT_WHITE:
    case MODE_PLAYER_VS_BOT_BLACK:
        playPlayerVsBot(manager);
        break;
    }

    gameManagerDestroy(manager);
    printf("\nThank you for playing!\n");

    return 0;
}