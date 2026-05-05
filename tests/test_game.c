#include <criterion/criterion.h>

#include "game.h"

Test(test_start_game, FEN_to_game)
{
    Game game;
    char full_fen[] =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN_to_game(&game, full_fen);
    char castling[5] = "KQkq";
    char en_passant[3] = "- ";

    cr_assert_str_eq(game.castling, castling, "Expected %s\nbut got %s",
                     game.castling, castling);
    cr_assert_str_eq(game.en_passant, en_passant, "Expected %s\nbut got %s",
                     game.en_passant, en_passant);
    cr_assert_eq(game.fullmove_number, 1, "Expected %s\nbut got %s",
                 game.fullmove_number, 1);
    cr_assert_eq(game.halfmove_clock, 0, "Expected %s\nbut got %s",
                 game.halfmove_clock, 0);
    cr_assert_eq(game.turn, WHITE, "Expected %s\nbut got %s", game.turn, WHITE);
}

Test(test_start_game_black, FEN_to_game)
{
    Game game;
    char full_fen[] =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1";
    FEN_to_game(&game, full_fen);
    char castling[5] = "KQkq";
    char en_passant[3] = "- ";

    cr_assert_str_eq(game.castling, castling, "Expected %s\nbut got %s",
                     game.castling, castling);
    cr_assert_str_eq(game.en_passant, en_passant, "Expected %s\nbut got %s",
                     game.en_passant, en_passant);
    cr_assert_eq(game.fullmove_number, 1, "Expected %s\nbut got %s",
                 game.fullmove_number, 1);
    cr_assert_eq(game.halfmove_clock, 0, "Expected %s\nbut got %s",
                 game.halfmove_clock, 0);
    cr_assert_eq(game.turn, BLACK, "Expected %s\nbut got %s", game.turn, BLACK);
}