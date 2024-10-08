#include <criterion/criterion.h>

#include "move.h"
#include "game.h" 

Test(test_start_game, test_move)
{
    Game game;
    char full_fen[] =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    FEN_to_game(&game, full_fen);
    size_t valueMove[64] = { 0, 2, 0, 0, 0, 0, 2, 0,
                         2, 2, 2, 2, 2, 2, 2, 2,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         2, 2, 2, 2, 2, 2, 2, 2,
                         0, 2, 0, 0, 0, 0, 2, 0 };
    for (u_int i = 0; i < 64; i++)
    {
        Vector *vector = getMoveFromPiece(&game, i);
        if (vector)
        {
            cr_assert_eq(valueMove[i], vector->size, "Expected %li\nBut got %li\nIndex: %i",
                         valueMove[i], vector->size, i);
        }
        free_vector(vector);
    }
}