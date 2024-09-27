#include <criterion/criterion.h>

#include "game.h"
#include "bot.h"

Test(test_start_board, eval_board) {
    Game game;
    char full_fen[] =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN_to_game(&game, full_fen);
    int eval = evalBoard(&game);
    cr_assert_eq(eval, 0, "Expected 0 but got %d", eval);
}

Test(test_white_rook, eval_board) {
    Game game;
    char full_fen[] =
        "r7/8/8/8/8/8/8/8 w KQkq - 0 1";
    FEN_to_game(&game, full_fen);
    int eval = evalBoard(&game);
    cr_assert_eq(eval, 50, "Expected 50 but got %d", eval);
}

Test(test_white_bishop, eval_board) {
    Game game;
    char full_fen[] =
        "b7/8/8/8/8/8/8/8 w KQkq - 0 1";
    FEN_to_game(&game, full_fen);
    int eval = evalBoard(&game);
    cr_assert_eq(eval, 30, "Expected 30 but got %d", eval);
}

Test(test_white_queen, eval_board) {
    Game game;
    char full_fen[] =
        "q7/8/8/8/8/8/8/8 w KQkq - 0 1";
    FEN_to_game(&game, full_fen);
    int eval = evalBoard(&game);
    cr_assert_eq(eval, 200, "Expected 200 but got %d", eval);
}

Test(test_white_king, eval_board) {
    Game game;
    char full_fen[] =
        "k7/8/8/8/8/8/8/8 w KQkq - 0 1";
    FEN_to_game(&game, full_fen);
    int eval = evalBoard(&game);
    cr_assert_eq(eval, 1000, "Expected 1000 but got %d", eval);
}

Test(test_black_rook, eval_board) {
    Game game;
    char full_fen[] =
        "R7/8/8/8/8/8/8/8 w KQkq - 0 1";
    FEN_to_game(&game, full_fen);
    int eval = evalBoard(&game);
    cr_assert_eq(eval, -50, "Expected -50 but got %d", eval);
}

Test(test_black_bishop, eval_board) {
    Game game;
    char full_fen[] =
        "B7/8/8/8/8/8/8/8 w KQkq - 0 1";
    FEN_to_game(&game, full_fen);
    int eval = evalBoard(&game);
    cr_assert_eq(eval, -30, "Expected -30 but got %d", eval);
}