#include "bot.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "display.h"
#include "move.h"
#include "vector.h"

int evalBoard(Game *game)
{
    int res = 0;
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE; j++)
        {
            Piece piece = game->board[i * 8 + j];

            if (piece.name == EMPTY)
                continue;
            char color = piece.color == WHITE ? 1 : -1;

            res += piece.value * color;
        }
    }
    return res;
}

int minmax(Game *game, int depth, enum COLOR isWhite, int returnMove,
           int *start, int *dest)
{
    int res;
    if (depth == 0)
    {
        res = evalBoard(game);
    }
    else
    {
        int best = INT_MAX;
        if (isWhite == WHITE)
        {
            best = INT_MIN;
        }
        for (size_t i = 0; i < BOARD_SIZE; i++)
        {
            for (size_t j = 0; j < BOARD_SIZE; j++)
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

                    enum COLOR nextColor = isWhite == WHITE ? BLACK : WHITE;
                    int val = minmax(game, depth - 1, nextColor, 0, NULL, NULL);
                    undoMovement(game, &move);
                    if (isWhite)
                    {
                        if (val > best)
                        {
                            best = val;
                            if (returnMove)
                            {
                                *start = src;
                                *dest = dst;
                            }
                        }
                    }
                    else
                    {
                        if (val < best)
                        {
                            best = val;
                            if (returnMove)
                            {
                                *start = src;
                                *dest = dst;
                            }
                        }
                    }
                }
                free_vector(vector);
            }
        }
        res = best;
    }
    return res;
}

// TODO faire une struct
int alphaBeta(Game *game, int depth, int alpha, int beta, int maximazing,
              enum COLOR isWhite, int *startPos, int *destPos, int returnMove)
{
    int res;
    if (depth == 0)
    {
        res = evalBoard(game);
    }
    else
    {
        int best = INT_MAX;
        if (isWhite == WHITE)
        {
            best = INT_MIN;
        }
        for (size_t i = 0; i < BOARD_SIZE; i++)
        {
            for (size_t j = 0; j < BOARD_SIZE; j++)
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
                for (int k = 0; k < vector->size; k++)
                {
                    int dst = vector->data[k];
                    Move move;
                    createMove(game, src, dst, &move);
                    doMovement(game, &move);

                    enum COLOR nextColor = isWhite == WHITE ? BLACK : WHITE;
                    int val = minmax(game, depth - 1, nextColor, 0, NULL, NULL);
                    undoMovement(game, &move);
                    if (isWhite)
                    {
                        if (val > best)
                        {
                            best = val;
                            if (val > alpha)
                            {
                                alpha = val;
                            }
                            if (beta <= alpha)
                            {
                                return val;
                            }
                            
                            if (returnMove)
                            {
                                *startPos = src;
                                *destPos = dst;
                            }
                        }
                    }
                    else
                    {
                        if (val < best)
                        {
                            best = val;
                            if (val < beta)
                            {
                                beta = val;
                            }
                            if (beta <= alpha)
                            {
                                return val;
                            }
                            if (returnMove)
                            {
                                *startPos = src;
                                *destPos = dst;
                            }
                        }
                    }
                }
                free_vector(vector);
            }
        }
    }
}