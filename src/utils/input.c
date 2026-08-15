#include "input.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool parseAlgebraicMove(const char *notation, int *src, int *dst)
{
    if (!notation || strlen(notation) < 4)
        return false;

    // Parse source square (e.g., "e2")
    char src_file = tolower(notation[0]);
    char src_rank = notation[1];

    // Parse destination square (e.g., "e4")
    char dst_file = tolower(notation[2]);
    char dst_rank = notation[3];

    // Validate files (a-h)
    if (src_file < 'a' || src_file > 'h' || dst_file < 'a' || dst_file > 'h')
        return false;

    // Validate ranks (1-8)
    if (src_rank < '1' || src_rank > '8' || dst_rank < '1' || dst_rank > '8')
        return false;

    // Convert to board indices (0-63)
    // Rank is inverted: rank 8 is index 56-63, rank 1 is index 0-7
    int src_file_idx = src_file - 'a';
    int src_rank_idx = 8 - (src_rank - '0');
    *src = src_rank_idx * 8 + src_file_idx;

    int dst_file_idx = dst_file - 'a';
    int dst_rank_idx = 8 - (dst_rank - '0');
    *dst = dst_rank_idx * 8 + dst_file_idx;

    return *src >= 0 && *src < 64 && *dst >= 0 && *dst < 64;
}

void indexToAlgebraic(int index, char *notation)
{
    if (!notation || index < 0 || index >= 64)
        return;

    int file = index % 8;
    int rank = 8 - (index / 8);

    notation[0] = 'a' + file;
    notation[1] = '0' + rank;
    notation[2] = '\0';
}

char *getUserMoveInput(void)
{
    char *buffer = malloc(256);
    if (!buffer)
        return NULL;

    if (fgets(buffer, 256, stdin) == NULL)
    {
        free(buffer);
        return NULL;
    }

    // Remove trailing newline
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }

    return buffer;
}

void displayPlayerPrompt(int turn)
{
    printf("\n");
    if (turn == 0) // WHITE
    {
        printf("White's turn\n");
    }
    else // BLACK
    {
        printf("Black's turn\n");
    }
    printf("Enter your move (algebraic notation, e.g., e2e4): ");
    fflush(stdout);
}

void displayHelpMessage(void)
{
    printf("\n=== Help ===\n");
    printf("Move format: Algebraic notation (e.g., e2e4, a7a8q)\n");
    printf("Files: a-h (from left to right)\n");
    printf("Ranks: 1-8 (from bottom to top)\n");
    printf("Commands:\n");
    printf("  'help' - Display this help\n");
    printf("  'quit' - End the game\n");
    printf("================\n\n");
}
