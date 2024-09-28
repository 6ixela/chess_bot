#include "move.h"

int board64[64] = { 21, 22, 23, 24, 25, 26, 27, 28,
                    31, 32, 33, 34, 35, 36, 37, 38,
                    41, 42, 43, 44, 45, 46, 47, 48, 
                    51, 52, 53, 54, 55, 56, 57, 58, 
                    61, 62, 63, 64, 65, 66, 67, 68, 
                    71, 72, 73, 74, 75, 76, 77, 78,
                    81, 82, 83, 84, 85, 86, 87, 88,
                    91, 92, 93, 94, 95, 96, 97, 98 };

int board120[120] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
                      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                      -1, 0,  1,  2,  3,  4,  5,  6, 7,  -1,
                      -1, 8,  9,  10, 11, 12, 13, 14, 15, -1,
                      -1, 16, 17, 18, 19, 20, 21, 22, 23, -1,
                      -1, 24, 25, 26, 27, 28, 29, 30, 31, -1,
                      -1, 32, 33, 34, 35, 36, 37, 38, 39, -1,
                      -1, 40, 41, 42, 43, 44, 45, 46, 47, -1,
                      -1, 48, 49, 50, 51, 52, 53, 54, 55, -1,
                      -1, 56, 57, 58, 59, 60, 61, 62, 63, -1,
                      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

/*static void swap(Game *game, Move *move)
{
}*/

/*int isValidMove(Game *game, uint src, uint dst)
{
    Move move = { src, dst };
    switch (game->board[src].name)
    {
    case PAWN:
        return pawnMove(&game, &move);
    case ROOK:
        return rookMove(&game, &move);
    case BISHOP:
        return bishopMove(&game, &move);
    case KING:
        return kingMove(&game, &move);
    case QUEEN:
        return queenMove(&game, &move);
    case KNIGHT:
        return knightMove(&game, &move);
    }
}*/

Vector* pawnMove(Game *game, Move *move)
{
    int pawnPossibleMove[] = { 10, 20 };
    Piece piece = game->board[move->from];
    int sign = piece.color == WHITE ? 1 : -1;
    Vector *vector = init_vector(8);
    if (!vector)
    {
        return NULL;
    }
    

    return vector;

}

Vector* kingMove(Game *game, uint src)
{
    const size_t LEN_POSSIBLE_MOVE_KING = 8;
    int kingPossibleMove[] = { 1, 9, 10, 11, -1, -9, -10, -11 };
    Vector *vector = init_vector(8);
    if (!vector)
    {
        return NULL;
    }
    Piece pieceFrom = game->board[src];

    for (size_t i = 0; i < LEN_POSSIBLE_MOVE_KING; i++)
    {
        // check si le nouveau placement est ok
        const int moveBoard64 = board64[src] + kingPossibleMove[i];
        const int moveBoard120 = board120[moveBoard64];
        if (moveBoard120 == -1)
        {
            continue;
        }

        // check si la place est vide ou piece enemie.
        Piece pieceDst = game->board[moveBoard120];
        if (pieceDst.name != EMPTY && pieceFrom.color == pieceDst.color)
        {
            continue;
        }

        // si ok push
        push_back(vector, moveBoard120);
    }
    return vector;
}

Vector* rookove(Game *game, Move *move)
{
    int rookPossibleMove[] = { 1, 10, -1, -10 };
    return 8;
}
Vector* bishopMove(Game *game, Move *move)
{
    int bishopPossibleMove[] = { 9, 11, -9, -11 };
    return 8;
}
Vector* knightMove(Game *game, Move *move)
{
    int knightPossibleMove[] = { 12, 21, 19, 8, -12, -21, -19, -8 };
    return 8;
}
Vector* queenMove(Game *game, Move *move)
{
    return bishopMove(game, move) || rookove(game, move);
}
