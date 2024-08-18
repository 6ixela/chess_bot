#include <criterion/criterion.h>

#include "board.h"
#include "bot.h"

Test(test_start_board, eval_board) {
    struct board *board = fenToBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    int eval = evalBoard(board);
    cr_assert_eq(eval, 0, "Expected 5 but got %d", eval);
}

Test(test_white_rook, eval_board) {
    struct board *board = fenToBoard("r7/8/8/8/8/8/8/8");
    int eval = evalBoard(board);
    cr_assert_eq(eval, 50, "Expected 5 but got %d", eval);
}

Test(test_white_bishop, eval_board) {
    struct board *board = fenToBoard("b7/8/8/8/8/8/8/8");
    int eval = evalBoard(board);
    cr_assert_eq(eval, 30, "Expected 5 but got %d", eval);
}

Test(test_white_queen, eval_board) {
    struct board *board = fenToBoard("q7/8/8/8/8/8/8/8");
    int eval = evalBoard(board);
    cr_assert_eq(eval, 200, "Expected 5 but got %d", eval);
}

Test(test_white_king, eval_board) {
    struct board *board = fenToBoard("k7/8/8/8/8/8/8/8");
    int eval = evalBoard(board);
    cr_assert_eq(eval, 1000, "Expected 5 but got %d", eval);
}

Test(test_black_rook, eval_board) {
    struct board *board = fenToBoard("R7/8/8/8/8/8/8/8");
    int eval = evalBoard(board);
    cr_assert_eq(eval, -50, "Expected 5 but got %d", eval);
}

Test(test_black_bishop, eval_board) {
    struct board *board = fenToBoard("B7/8/8/8/8/8/8/8");
    int eval = evalBoard(board);
    cr_assert_eq(eval, -30, "Expected 5 but got %d", eval);
}