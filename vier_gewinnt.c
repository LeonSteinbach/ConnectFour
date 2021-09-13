// Copyright 2019 Leon Steinbach

#include "vier_gewinnt.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

void print_matrix(int matrix[ROWS][COLUMNS]) {
    // This function prints the bord in a readable way.

    printf("╔");
    for (int i = 1; i < COLUMNS * 2 + 2; i++) {
        printf("═");
    }
    printf("╗\n║ ");
    for (int i = 1; i < COLUMNS+1; i++) {
        printf("%d ", i);
    }
    printf("║\n");
    for (int y = 0; y < ROWS; y++) {
        printf("║│");
        for (int x = 0; x < COLUMNS; x++) {
            if (matrix[y][x] == 1) {
                printf("O");
            } else if (matrix[y][x] == 2) {
                printf("X");
            } else {
                printf(" ");
            }
            if (x < COLUMNS-1) {
                printf("│");
            }
        }
        printf("│║\n");
    }
    printf("╚");
    for (int i = 1; i < COLUMNS * 2 + 2; i++) {
        printf("═");
    }
    printf("╝\n");
}

int is_game_over(int matrix[ROWS][COLUMNS], int player) {
    // This function calculates if the game is over.
    // The game is over when eather one player won (returns 1),
    // or the bord is full and no player won (returns 2).
    // Else, the game is not over yet (returns 0).

    bool won = winning_move(matrix, player);
    if (won == true) {
        return 1;  // Winning move.
    }
    if (is_full(matrix) == true) {
        return 2;  // A draw.
    }
    return 0;  // Game isn't over yet.
}

bool winning_move(int matrix[ROWS][COLUMNS], int player) {
    // Checks the bord for a winning move (4 connected in a row).
    // Returns, if the given player has made a winning move.

    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLUMNS; x++) {
            if (x < 4) {
                // Check all rows.
                if (matrix[y][x] == player && matrix[y][x+1] == player &&
                    matrix[y][x+2] == player && matrix[y][x+3] == player) {
                    return true;
                }
            }
            if (y < 4) {
                // Check all columns.
                if (matrix[y][x] == player && matrix[y+1][x] == player &&
                    matrix[y+2][x] == player && matrix[y+3][x] == player) {
                    return true;
                }
            }
            if (x < COLUMNS-3 && y < ROWS-3) {
                // Check all diagonals from top left to bottom right.
                if (matrix[y][x] == player && matrix[y+1][x+1] == player &&
                    matrix[y+2][x+2] == player && matrix[y+3][x+3] == player) {
                    return true;
                }
            }
            if (x >= 3 && y < ROWS-3) {
                // Check all diagonals from bottom left to top right.
                if (matrix[y][x] == player && matrix[y+1][x-1] == player &&
                    matrix[y+2][x-2] == player && matrix[y+3][x-3] == player) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool is_full(int matrix[ROWS][COLUMNS]) {
    // Returns, if the bord is full.

    for (int x = 0; x < COLUMNS; x++) {
        if (matrix[0][x] == 0) {
            return false;
        }
    }
    return true;
}

bool drop_in_column(int matrix[ROWS][COLUMNS], int column, int player) {
    // This function drops a coin in a column and returns if it was successful.

    // Handle invariants.
    // If the entered column is out of range.
    if (column >= COLUMNS || column < 0) {
        return false;
    }
    // If the entered column is already full.
    if (matrix[0][column] > 0) {
        return false;
    }

    // Drop the coin ontop of the topmost coin in this column.
    int row = 0;
    while (row < ROWS && matrix[row][column] == 0) {
        row++;
    }
    row--;

    // Set the field to the player.
    matrix[row][column] = player;

    return true;  // Successful.
}

bool load_matrix(int matrix[ROWS][COLUMNS], int* player, char* filename) {
    // This function loads a bord from a given file
    // and sets it to the current bord.

    FILE* file;
    int temp;
    int i = 0;

    // Difference between O's and X's in the bord.
    // Is used to determine which player continues the game.
    int player_ai = 0;

    file = fopen(filename, "r");
    if (file != NULL) {
        // Read all characters of the file.
        while (i < ROWS * COLUMNS && (temp = fgetc(file)) != EOF) {
            int digit;  // Which player to set to the bord at this position.
            if ((int)temp == 48) {  // Empty field.
                digit = 0;
            } else if ((int)temp == 49) {
                digit = 1;
                player_ai++;  // Counted one O.
            } else if ((int)temp == 50) {
                digit = 2;
                player_ai--;  // Counted one X.
            } else {
                // A false character in the game file was found.
                printf("%d is a false character!\n", temp);
            }

            // Conversion from 1D file array to 2D matrix.
            matrix[(int)ceil(i / COLUMNS)][i % COLUMNS] = digit;
            i++;  // Increase counter of letters.
        }
        fclose(file);  // Close the file.

        // Set the player which continues to play.
        if (player_ai == 0) {
            *player = 1;
        } else if (player_ai == 1) {
            *player = 2;
        } else {
            // One player had more turns than allowed.
            // The file must have been changed manually.
            printf("Corrupted game file!\n");
            return false;
        }
        return true;  // Successful.
    }
    return false;  // File error.
}

bool save_matrix(int matrix[ROWS][COLUMNS], char* input) {
    // This function saves the current board to a given file.

    // Get the filename from the input.
    char filename[50];
    for (int i = 5; i < 55; i++) {
        filename[i - 5] = input[i];
    }

    FILE* file;
    file = fopen(filename, "w");

    if (file == NULL) {
        // File error.
        printf("Could not save!\n");
        return false;
    } else {
        // Write matrix to file.
        for (int y = 0; y < ROWS; y++) {
            for (int x = 0; x < COLUMNS; x++) {
                fputc(matrix[y][x] + 48, file);
            }
        }
        fclose(file);  // Close the file.
    }

    printf("Saved!\n");

    return true;  // Successful.
}
