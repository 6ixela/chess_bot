#include "bot.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "display.h"
#include "move.h"
#include "vector.h"

int evalBoard(const Game *game)
{
    int res = 0;
    // White pieces
    res += __builtin_popcountll(game->bitboard.WPawn) * 10;
    res += __builtin_popcountll(game->bitboard.WKnight) * 30;
    res += __builtin_popcountll(game->bitboard.WBishop) * 30;
    res += __builtin_popcountll(game->bitboard.WRook) * 50;
    res += __builtin_popcountll(game->bitboard.WQueen) * 200;
    res += __builtin_popcountll(game->bitboard.WKing) * 10000;
    // Black pieces (negative)
    res -= __builtin_popcountll(game->bitboard.BPawn) * 10;
    res -= __builtin_popcountll(game->bitboard.BKnight) * 30;
    res -= __builtin_popcountll(game->bitboard.BBishop) * 30;
    res -= __builtin_popcountll(game->bitboard.BRook) * 50;
    res -= __builtin_popcountll(game->bitboard.BQueen) * 200;
    res -= __builtin_popcountll(game->bitboard.BKing) * 10000;
    return res;
}

int alphaBeta(Game *game, int depth, int alpha, int beta,
              enum COLOR isWhite, int *startPos, int *destPos,
              int returnMove)
{
    if (depth == 0)
    {
        return evalBoard(game);
    }

    int best = (isWhite == WHITE) ? INT_MIN : INT_MAX;
    int foundMove = 0;
    int cutoff = 0;

    for (size_t i = 0; i < BOARD_SIZE && !cutoff; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE && !cutoff; j++)
        {
            int src = i * 8 + j;
            Piece piece = game->board[src];
            if (piece.name == EMPTY || piece.color != isWhite)
                continue;

            Vector *vector = getMoveFromPiece(game, src);
            if (vector == NULL)
            {
                continue;
            }

            for (size_t k = 0; k < vector->size; k++)
            {
                int dst = vector->data[k];
                Move move;
                createMove(game, src, dst, &move);
                doMovement(game, &move);

                enum COLOR nextColor = (isWhite == WHITE) ? BLACK : WHITE;
                int val = alphaBeta(game, depth - 1, alpha, beta, nextColor,
                                    NULL, NULL, 0);
                undoMovement(game, &move);
                foundMove = 1;

                if (isWhite == WHITE)
                {
                    if (val > best)
                    {
                        best = val;
                        if (returnMove)
                        {
                            *startPos = src;
                            *destPos = dst;
                        }
                    }
                    if (best > alpha)
                    {
                        alpha = best;
                    }
                    if (beta <= alpha)
                    {
                        cutoff = 1;
                        break;
                    }
                }
                else
                {
                    if (val < best)
                    {
                        best = val;
                        if (returnMove)
                        {
                            *startPos = src;
                            *destPos = dst;
                        }
                    }
                    if (best < beta)
                    {
                        beta = best;
                    }
                    if (beta <= alpha)
                    {
                        cutoff = 1;
                        break;
                    }
                }
            }
            free_vector(vector);
        }
    }

    if (!foundMove)
    {
        return evalBoard(game);
    }

    return best;
}