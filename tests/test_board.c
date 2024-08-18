#include <criterion/criterion.h>

#include "board.h"

Test(test_start_board, creation_board) {
    char orginalFen[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    struct board *board = fenToBoard(orginalFen);
    char* getFen = boardToFen(board);
    cr_assert_str_eq(orginalFen, getFen, "Expected %s\nbut got %s", orginalFen, getFen);
}