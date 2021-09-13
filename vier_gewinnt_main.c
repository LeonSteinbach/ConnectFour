// Copyright 2019 Leon Steinbach

#include "vier_gewinnt.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    int player = 1;  // Start with player 1.
    int game_state = 0;  // Game not over yet.

    int matrix[ROWS][COLUMNS] = {{ 0 }};  // Initialize the matrix.

    if (argc == 2) {  // Argument has been specified.
        // Display the help text.
        if (strcmp(argv[1], "--help") == 0) {
            // Handle the input (play / exit).
            char action[10];
            do {
                system("clear");  // Clear the console.

                printf("       -- HELP --\nEnter a column to drop your ");
                printf("coins.\nConnect 4 of your coins (all directions ");
                printf("possible) to win the game.\n\nTo resume an old ");
                printf("game, start the program with the command './4 ");
                printf("<filename.txt>'.\n\nType 'save <filename.txt>' to ");
                printf("save the bord to a file.\nType 'load ");
                printf("<filename.txt>' to load a bord from a file.\n\n");
                printf("Arguments\n\n --help\n\nType 'start' to start the ");
                printf("game, 'exit' to exit the game.\n > ");

                gets(action);
                if (strcmp(action, "exit") == 0) {
                    return 0;
                }
            } while (strcmp(action, "start") != 0  &&
                strcmp(action, "exit") != 0);

        } else {
            // Load a game from the specified file.
            if (!load_matrix(matrix, &player, argv[1])) {
                printf("File '%s' not found!\n", argv[1]);
                return 1;  // File error.
            }

            // Calculate the game state of the loaded bord.
            int game_state_1 = is_game_over(matrix, 1);
            int game_state_2 = is_game_over(matrix, 2);
            if (game_state_1 == 1) {
                printf("Player O won!\n");
                return 0;
            } else if (game_state_2 == 1) {
                printf("Player X won!\n");
                return 0;
            } else if (game_state_1 == 2 && game_state_2 == 2) {
                printf("You played a draw!\n");
                return 0;
            }
        }
    }

    system("clear");  // Clear the console.
    print_matrix(matrix);  // Print the bord.

    while (true) {  // Main loop.
        printf("Player %c 's turn!\n", (player == 1) ? 'O' : 'X');
        printf("Enter a column or a command.\n");
        printf("Commands: load <filename.txt>\n");
        printf("          save <filename.txt>.\n > ");

        // Input of the column or command.
        char input[55];
        gets(input);
        int column = atoi(input);

        // Get the filenmae from the input.
        // (only used if the user typed the load command).
        char filename[50];
        for (int i = 5; i < 55; i++) {
            filename[i - 5] = input[i];
        }
        bool file_not_found = false;

        // Handle the command (load / save).
        if (strncmp("save ", input, 5) == 0) {  // Entered save command.
            if (save_matrix(matrix, input) == true) {
                return 0;
            }
        } else if (strncmp("load ", input, 5) == 0) {  // Entered load command.
            if (!load_matrix(matrix, &player, filename)) {
                file_not_found = true;
            }
        }

        system("clear");  // Clear the console.

        // Drop a piece in the column entered by the player.
        bool drop = drop_in_column(matrix, column-1, player);

        print_matrix(matrix);  // Print the bord.

        if (file_not_found == true) {
            // The file to load was not found.
            printf("File '%s' not found!\n", filename);
        } else if (drop == false) {
            // False input or the column is full.
            printf("Unable to drop in column %d.\n", column);
        } else {
            // Check if the game is over after this drop.
            game_state = is_game_over(matrix, player);
            if (game_state == 1) {
                // The player made a winning move.
                printf("Player %c won!\n", (player == 1) ? 'O' : 'X');
                break;
            } else if (game_state == 2) {
                // The bord is full and no player won.
                printf("You played a draw!\n");
                break;
            }

            // Change the player.
            player = (player == 1) ? 2 : 1;
        }
    }
    return 0;
}
