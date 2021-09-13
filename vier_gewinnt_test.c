// Copyright 2019 Leon Steinbach

#include <assert.h>
#include "vier_gewinnt.h"

int main(int argc, char** argv) {
    // This function tests the functions of the file vier_gewinnt.c.

    // Test winning_move function.
    int matrix_1[ROWS][COLUMNS] = {
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0 }
    };

    int matrix_2[ROWS][COLUMNS] = {
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0 },
        { 0, 0, 0, 0, 1, 2, 0 },
        { 0, 0, 0, 1, 1, 1, 0 },
        { 0, 0, 1, 2, 2, 2, 0 }
    };

    int matrix_3[ROWS][COLUMNS] = {
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0 }
    };

    assert(winning_move(matrix_1, 1) == false &&
           winning_move(matrix_1, 2) == false);
    assert(winning_move(matrix_2, 1) == true &&
           winning_move(matrix_2, 2) == false);
    assert(winning_move(matrix_3, 1) == true &&
           winning_move(matrix_3, 2) == false);

    // Test is_full function.
    int matrix_4[ROWS][COLUMNS] = {
        { 1, 2, 1, 2, 2, 1, 1 },
        { 2, 1, 1, 1, 2, 1, 2 },
        { 1, 2, 2, 2, 1, 1, 2 },
        { 2, 2, 1, 2, 1, 2, 1 },
        { 1, 2, 1, 2, 1, 1, 1 },
        { 2, 1, 1, 1, 2, 2, 2 }
    };

    int matrix_5[ROWS][COLUMNS] = {
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0 },
        { 0, 0, 0, 0, 1, 2, 0 },
        { 0, 0, 0, 1, 1, 1, 0 },
        { 0, 0, 1, 2, 2, 2, 0 }
    };

    assert(is_full(matrix_4) == true);  // Matrix 4 is full.
    assert(is_full(matrix_5) == false);  // Matrix 5 is not full.

    // Test is_game_over function.
    // Must be correct, if winning_move function
    // and is_full function are correct.
    assert(is_game_over(matrix_1, 1) == 0 &&  // Matrix 1 (game not over).
           is_game_over(matrix_1, 2) == 0);
    assert(is_game_over(matrix_2, 1) == 1 &&  // Matrix 2 (player 1 won).
           is_game_over(matrix_2, 2) == 0);
    assert(is_game_over(matrix_3, 1) == 1 &&  // Matrix 3 (player 1 won).
           is_game_over(matrix_3, 2) == 0);
    assert(is_game_over(matrix_4, 1) == 2 &&  // Matrix 4 (played a draw).
           is_game_over(matrix_4, 2) == 2);

    // Test drop_in_column function.
    int matrix_6[ROWS][COLUMNS] = {
        { 0, 0, 2, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 2, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 2, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0 }
    };

    // Should be successful (Matrix 1, column 2).
    assert(matrix_1[2][2] == 0);  // Before.
    assert(drop_in_column(matrix_1, 2, 1) == true);  // Drop in column 2.
    assert(matrix_1[2][2] == 1);  // After.

    // Should not be successful (Matrix 6, column 2).
    assert(matrix_6[0][2] == 2);  // Before.
    assert(drop_in_column(matrix_6, 2, 1) == false);  // Drop in column 2.
    assert(matrix_6[0][2] == 2);  // After.

    return 0;
}
