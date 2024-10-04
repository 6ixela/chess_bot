#include <criterion/criterion.h>

#include "move.h"
Test(test_start_game, test_move)
{
    Game game;
    char full_fen[] =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN_to_game(&game, full_fen);

    cr_assert_eq(game.fullmove_number, 1, "Expected %s\nbut got %s",
                 game.fullmove_number, 1);
    cr_assert_eq(game.halfmove_clock, 0, "Expected %s\nbut got %s",
                 game.halfmove_clock, 0);
    cr_assert_eq(game.turn, WHITE, "Expected %s\nbut got %s", game.turn, WHITE);
}