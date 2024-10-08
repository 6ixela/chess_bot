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

void initMoveStruct(Move *move, u_int from, u_int to)
{
    Piece piece = {EMPTY, BLACK, 0};
    move->piece_captured = piece;
    move->from = from;
    move->to = to;
}

inline static void clearPiece(Piece* piece)
{
    piece->name = EMPTY;
    piece->color = BLACK;
    piece->value = 0;
}

void doMovement(Game *game, Move* move)
{
    Piece piece = game->board[move->from];
    Piece arrive = game->board[move->to];

    if (arrive.name != EMPTY && arrive.color != piece.color)
    {
        move->piece_captured = arrive;
        clearPiece(&arrive);
    }
    
    game->board[move->from] = arrive;
    game->board[move->to] = piece;
}

void undoMovement(Game *game, Move* move)
{
    Piece piece = game->board[move->to];
    
    if (move->moveType == CAPTURE || move->moveType == MOVEMENT)
    {
        game->board[move->to] = move->piece_captured;
    }
    else if (move->moveType == CASTLE)
    {
        game->board[move->to] = game->board[move->from];
    }
    else
    {
        piece.name = PAWN;
        piece.value = 10;
    }
    game->board[move->from] = piece;
}


Vector *getMoveFromPiece(Game *game, u_int src)
{
    switch (game->board[src].name)
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
    case EMPTY:
        return NULL;
    }
    return NULL;
}

static char isPushable(const int moveBoard120, Game *game, Piece *pieceFrom)
{
    if (moveBoard120 == -1)
    {
        return 0;
    }
    Piece pieceDst = game->board[moveBoard120];
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

Vector* pawnMove(Game *game, u_int src)
{
    const char pawnPossibleMove[] = { 10, 20 };
    const char pawnPossibleAttack[] = { 9, 11 };
    Piece pieceFrom = game->board[src];
    Vector *vector = init_vector(3);
    const char color = pieceFrom.color == WHITE ? -1 : 1;
    char moveBoard64 = board64[src] + (pawnPossibleMove[0] * color);
    char moveBoard120 = board120[moveBoard64];

    if (isPushable(moveBoard120, game, &pieceFrom))
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
            if (isPushable(moveBoard120, game, &pieceFrom))
            {
                push_back(vector, moveBoard120);
            }
        }
        
    }
    else
    {
        if (pawnPosition / 10 == 3)
        {
            if (isPushable(moveBoard120, game, &pieceFrom))
            {
                push_back(vector, moveBoard120);
            }
        }
    }

    for (char i = 0; i < 2; i++)
    {
        const char moveBoard64 = board64[src] + (pawnPossibleAttack[i] * color);
        const char moveBoard120 = board120[moveBoard64];
        if (isPushable(moveBoard120, game, &pieceFrom))
        {
            if (game->board[moveBoard120].name != EMPTY && pieceFrom.color != game->board[moveBoard120].color)
            {
                push_back(vector, moveBoard120);
            }            
        } 
    }
    // TODO en_passant    
    return vector;
}

static void parseCastling(char castling[], enum COLOR color, Vector *vector)
{
    char i = color == WHITE ? 0 : 2;   
    if (castling[0] == 'K')
    {
        /* code */
    }
     
    // +1, +2 vide
    // -1, -2, -3 vide
}

Vector* kingMove(Game *game, u_int src)
{
    const size_t LEN_POSSIBLE_MOVE_KING = 8;
    const char kingPossibleMove[] = { 1, 9, 10, 11, -1, -9, -10, -11 };
    Vector *vector = init_vector(8);
    if (!vector)
    {
        return NULL;
    }
    Piece pieceFrom = game->board[src];

    for (size_t i = 0; i < LEN_POSSIBLE_MOVE_KING; i++)
    {
        const char moveBoard64 = board64[src] + kingPossibleMove[i];
        const char moveBoard120 = board120[moveBoard64];
        if (isPushable(moveBoard120, game, &pieceFrom))
        {
            push_back(vector, moveBoard120);
        }        
    }

    parseCastling(game->castling, pieceFrom.color, vector);
    return vector;
}

Vector* rookMove(Game *game, u_int src)
{
    const char rookPossibleMove[] = { 1, 10, -1, -10 };
    Vector *vector = init_vector(8);
    if (!vector)
    {
        return NULL;
    }
    Piece pieceFrom = game->board[src];

    char i = 1;
    u_char noMorePossibleMove = 0x0f;
    while (noMorePossibleMove)
    {
        u_char tmp = 0x01;
        for (size_t j = 0; j < 4; j++)
        {
            if (noMorePossibleMove & tmp)
            {
                const char moveBoard64 = board64[src] + (rookPossibleMove[j] * i);
                const char moveBoard120 = board120[moveBoard64];
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


Vector* bishopMove(Game *game, u_int src)
{
    const char bishopPossibleMove[] = { 9, 11, -9, -11 };
    Vector *vector = init_vector(8);
    if (!vector)
    {
        return NULL;
    }
    Piece pieceFrom = game->board[src];

    char i = 1;
    u_char noMorePossibleMove = 0x0f;
    while (noMorePossibleMove)
    {
        u_char tmp = 0x01;
        for (size_t j = 0; j < 4; j++)
        {
            if (noMorePossibleMove & tmp)
            {
                const char moveBoard64 = board64[src] + (bishopPossibleMove[j] * i);
                const char moveBoard120 = board120[moveBoard64];
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
Vector* knightMove(Game *game, u_int src)
{
    const char knightPossibleMove[] = { 12, 21, 19, 8, -12, -21, -19, -8 };
    const size_t LEN_POSSIBLE_MOVE_KNIGHT = 8;
    Vector *vector = init_vector(8);
    if (!vector)
    {
        return NULL;
    }
    Piece pieceFrom = game->board[src];

    for (size_t i = 0; i < LEN_POSSIBLE_MOVE_KNIGHT; i++)
    {
        const char moveBoard64 = board64[src] + knightPossibleMove[i];
        const char moveBoard120 = board120[moveBoard64];
        if (isPushable(moveBoard120, game, &pieceFrom))
        {
            push_back(vector, moveBoard120);
        }
    }
    return vector;
}
Vector* queenMove(Game *game, u_int src)
{
    Vector *vec = concat_vectors(bishopMove(game, src), rookMove(game, src));
    return vec;
}
