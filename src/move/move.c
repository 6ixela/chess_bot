#include "piece.h"
#include "move.h"
#include "bitBoard.h"

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

void initMoveStruct(Move *move, unsigned int from, unsigned int to)
{
    Piece piece = {EMPTY, BLACK, 0};
    move->piece_captured = piece;
    move->from = from;
    move->to = to;
}

void doMovement(Game *game, Move* move)
{
    Piece piece = getPieceFromGame(game, move->from);
    Piece target = getPieceFromGame(game, move->to);

    if (target.name != EMPTY && target.color != piece.color)
    {
        move->piece_captured = target;
    }
    else
    {
        move->piece_captured = (Piece){EMPTY, BLACK, 0};
    }

    clearSquare(game, move->from);
    setPieceOnGame(game, move->to, piece);
}

void createMove(Game *game, unsigned int src, unsigned int dst, Move *move)
{
    initMoveStruct(move, src, dst);
    Piece pieceSrc = getPieceFromGame(game, src);
    Piece pieceDst = getPieceFromGame(game, dst);
    if (pieceDst.name == EMPTY)
    {
        move->moveType = MOVEMENT;
    }
    else if (pieceDst.color != pieceSrc.color)
    {
        move->moveType = CAPTURE;
    }
    else
    {
        move->moveType = MOVEMENT;
    }
}

void undoMovement(Game *game, Move* move)
{
    Piece movedPiece = getPieceFromGame(game, move->to);
    clearSquare(game, move->to);
    clearSquare(game, move->from);
    setPieceOnGame(game, move->from, movedPiece);
    setPieceOnGame(game, move->to, move->piece_captured);
}


Vector *getMoveFromPiece(Game *game, unsigned int src)
{
    switch (getPieceFromGame(game, src).name)
    {
    case PAWN:
        return pawnMove(game, src);
    case ROOK:
        return rookMove(game, src);
    case BISHOP:
        return bishopMove(game, src);
    case KING:
        return kingMove(game, src);
    case QUEEN:
        return queenMove(game, src);
    case KNIGHT:
        return knightMove(game, src);
    default:
        return NULL;
    }
}

static int isPushable(int moveBoard120, const Game *game, const Piece *pieceFrom)
{
    if (moveBoard120 == -1)
    {
        return 0;
    }

    Piece pieceDst = getPieceFromGame(game, moveBoard120);
    if (pieceDst.name != EMPTY && pieceFrom->color == pieceDst.color)
    {
        return 0;
    }
    if (pieceDst.name != EMPTY && pieceFrom->color != pieceDst.color)
    {
        return 2;
    }

    return 1;
}

Vector* pawnMove(Game *game, unsigned int src)
{
    const int pawnPossibleMove[] = { 10, 20 };
    const int pawnPossibleAttack[] = { 9, 11 };
    Piece pieceFrom = getPieceFromGame(game, src);
    Vector *vector = init_vector(3);
    int color = pieceFrom.color == WHITE ? -1 : 1;
    int moveBoard64 = board64[src] + (pawnPossibleMove[0] * color);
    int moveBoard120 = board120[moveBoard64];

    if (isPushable(moveBoard120, game, &pieceFrom) == 1)
    {
        push_back(vector, moveBoard120);
    }
    moveBoard64 = board64[src] + (pawnPossibleMove[1] * color);
    moveBoard120 = board120[moveBoard64];
    int pawnPosition = board64[src];
    if (pieceFrom.color == WHITE)
    {
        if (pawnPosition / 10 == 8)
        {
            if (isPushable(moveBoard120, game, &pieceFrom) == 1)
            {
                push_back(vector, moveBoard120);
            }
        }
        
    }
    else
    {
        if (pawnPosition / 10 == 3)
        {
            if (isPushable(moveBoard120, game, &pieceFrom) == 1)
            {
                push_back(vector, moveBoard120);
            }
        }
    }

    for (int i = 0; i < 2; i++)
    {
        int moveBoard64 = board64[src] + (pawnPossibleAttack[i] * color);
        int moveBoard120 = board120[moveBoard64];
        if (isPushable(moveBoard120, game, &pieceFrom))
        {
            Piece pieceDst = getPieceFromGame(game, moveBoard120);
            if (pieceDst.name != EMPTY && pieceFrom.color != pieceDst.color)
            {
                push_back(vector, moveBoard120);
            }
        }
    }
    // TODO en_passant    
    return vector;
}

Vector* kingMove(Game *game, unsigned int src)
{
    const size_t LEN_POSSIBLE_MOVE_KING = 8;
    const int kingPossibleMove[] = { 1, 9, 10, 11, -1, -9, -10, -11 };
    Vector *vector = init_vector(8);
    if (!vector)
    {
        return NULL;
    }
    Piece pieceFrom = getPieceFromGame(game, src);

    for (size_t i = 0; i < LEN_POSSIBLE_MOVE_KING; i++)
    {
        int moveBoard64 = board64[src] + kingPossibleMove[i];
        int moveBoard120 = board120[moveBoard64];
        if (isPushable(moveBoard120, game, &pieceFrom))
        {
            push_back(vector, moveBoard120);
        }
    }

    return vector;
}

Vector* rookMove(Game *game, unsigned int src)
{
    const int rookPossibleMove[] = { 1, 10, -1, -10 };
    Vector *vector = init_vector(8);
    if (!vector)
    {
        return NULL;
    }
    Piece pieceFrom = getPieceFromGame(game, src);

    int i = 1;
    unsigned char noMorePossibleMove = 0x0f;
    while (noMorePossibleMove)
    {
        unsigned char tmp = 0x01;
        for (size_t j = 0; j < 4; j++)
        {
            if (noMorePossibleMove & tmp)
            {
                int moveBoard64 = board64[src] + (rookPossibleMove[j] * i);
                int moveBoard120 = board120[moveBoard64];
                int pieceFront;
                if (!(pieceFront = isPushable(moveBoard120, game, &pieceFrom)))
                {
                    noMorePossibleMove -= tmp;
                }
                else
                {
                    if (pieceFront == 2)
                    {
                        noMorePossibleMove -= tmp;
                    }
                    push_back(vector, moveBoard120);
                }
            }
            tmp = tmp << 1;
        }
        i++;
    }
    return vector;
}


Vector* bishopMove(Game *game, unsigned int src)
{
    const int bishopPossibleMove[] = { 9, 11, -9, -11 };
    Vector *vector = init_vector(8);
    if (!vector)
    {
        return NULL;
    }
    Piece pieceFrom = getPieceFromGame(game, src);

    int i = 1;
    unsigned char noMorePossibleMove = 0x0f;
    while (noMorePossibleMove)
    {
        unsigned char tmp = 0x01;
        for (size_t j = 0; j < 4; j++)
        {
            if (noMorePossibleMove & tmp)
            {
                int moveBoard64 = board64[src] + (bishopPossibleMove[j] * i);
                int moveBoard120 = board120[moveBoard64];
                int pieceFront;
                if (!(pieceFront = isPushable(moveBoard120, game, &pieceFrom)))
                {
                    noMorePossibleMove -= tmp;
                }
                else
                {
                    if (pieceFront == 2)
                    {
                        noMorePossibleMove -= tmp;
                    }
                    push_back(vector, moveBoard120);
                }
            }
            tmp = tmp << 1;
        }
        i++;
    }
    return vector;
}
Vector* knightMove(Game *game, unsigned int src)
{
    const int knightPossibleMove[] = { 12, 21, 19, 8, -12, -21, -19, -8 };
    const size_t LEN_POSSIBLE_MOVE_KNIGHT = 8;
    Vector *vector = init_vector(8);
    if (!vector)
    {
        return NULL;
    }
    Piece pieceFrom = getPieceFromGame(game, src);

    for (size_t i = 0; i < LEN_POSSIBLE_MOVE_KNIGHT; i++)
    {
        int moveBoard64 = board64[src] + knightPossibleMove[i];
        int moveBoard120 = board120[moveBoard64];
        if (isPushable(moveBoard120, game, &pieceFrom))
        {
            push_back(vector, moveBoard120);
        }
    }
    return vector;
}
Vector* queenMove(Game *game, unsigned int src)
{
    Vector *vec = concat_vectors(bishopMove(game, src), rookMove(game, src));
    return vec;
}
