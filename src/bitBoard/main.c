#include "bitBoard.h"

int main(int argc, char const *argv[])
{
    Board board = {0};
    createBoard(NULL, &board);
    set_bit(&board.BPawn, 20);
    printBitBoard(&board);
    return 0;
}
