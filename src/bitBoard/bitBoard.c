#include "bitBoard.h"

#include <stdio.h>

static bool isNumber(char c)
{
    char val = c - '0';
    return val > 0 && val <= 8 ? val : 0;
}

static bool isLetter(char c)
{
    return c == 'k' || c == 'K' || c == 'q' || c == 'Q' || c == 'r' || c == 'R'
        || c == 'n' || c == 'N' || c == 'b' || c == 'B' || c == 'p' || c == 'P';
}

static void shiftBitBoard(Board *board, char val)
{
    board->BBishop <<= val;
    board->BKing <<= val;
    board->BKnight <<= val;
    board->BPawn <<= val;
    board->BQueen <<= val;
    board->BRook <<= val;
    board->WBishop <<= val;
    board->WKing <<= val;
    board->WKnight <<= val;
    board->WPawn <<= val;
    board->WQueen <<= val;
    board->WRook <<= val;
}

static void putPiece(Board* board, char pieceName)
{
    switch (pieceName)
    {
    case 'k':
        board->BKing |= 1;
        break;
    case 'K':
        board->WKing |= 1;
        break;
    case 'b':
        board->BBishop |= 1;
        break;
    case 'B':
        board->WBishop |= 1;
        break;
    case 'n':
        board->BKnight |= 1;
        break;
    case 'N':
        board->WKnight |= 1;
        break;
    case 'r':
        board->BRook |= 1;
        break;
    case 'R':
        board->WRook |= 1;
        break;
    case 'q':
        board->BQueen |= 1;
        break;
    case 'Q':
        board->WQueen |= 1;
        break;
    case 'p':
        board->BPawn |= 1;
        break;
    case 'P':
        board->WPawn |= 1;
        break;
    default:
        break;
    }
}

err createBoard(char *fen, Board *board)
{
    if (fen == NULL)
    {
        fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    }
    char check = 0;
    bool wasNumber = 0;
    int count = 0;
    for (size_t i = 0; fen[i] != 0 && fen[i] != ' '; i++)
    {
        char c = fen[i];
        if (c == '/')
        {
            wasNumber = 0;
            check++;
        }
        else
        {
            if (isNumber(c) && wasNumber == 0)
            {
                wasNumber = 1;
                c -= '0';
                shiftBitBoard(board, c);
                count += c;
            }
            else if (isLetter(c))
            {
                wasNumber = 0;
                putPiece(board, c);
                count++;
                if (count != 64)
                {
                    shiftBitBoard(board, 1);
                }
            }
            else
            {
                return -1;
            }
        }
    }

    return check == 8;
}

static void printBoard(char board[])
{
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            printf("%c ", board[i * 8 + j]);
        }
        printf("\n");
    }
    
}

static void putPieceIntoBoard(U64 bitBoardPiece, char board[], char piece)
{
    for (int i = 63; i >= 0; i--)
    {
        if ((bitBoardPiece >> i) & 1)
        {
            board[i] = piece;
        }
    }
}

void printBitBoard(Board *bitBoard)
{
    char board[64] = {0};

    putPieceIntoBoard(bitBoard->BBishop, board, 'b');
    putPieceIntoBoard(bitBoard->BKing, board, 'k');
    putPieceIntoBoard(bitBoard->BKnight, board, 'n');
    putPieceIntoBoard(bitBoard->BPawn, board, 'p');
    putPieceIntoBoard(bitBoard->BQueen, board, 'q');
    putPieceIntoBoard(bitBoard->BRook, board, 'r');
    putPieceIntoBoard(bitBoard->WBishop, board, 'B');
    putPieceIntoBoard(bitBoard->WKing, board, 'K');
    putPieceIntoBoard(bitBoard->WKnight, board, 'N');
    putPieceIntoBoard(bitBoard->WPawn, board, 'P');
    putPieceIntoBoard(bitBoard->WQueen, board, 'Q');
    putPieceIntoBoard(bitBoard->WRook, board, 'R');
    printBoard(board);
}

void set_bit(U64 *bb, int i)
{
    *bb |= 1ull << i;
}

void clear_bit(U64 *bb, int i)
{
    *bb &= ~(1ull << i);
}

U64 get_bit(U64 *bb, int i)
{
    return *bb & (1ull << i);
}