// Copyright 2019 Leon Steinbach

#ifndef VIER_GEWINNT_H_
#define VIER_GEWINNT_H_

#include <stdbool.h>

#define COLUMNS 7
#define ROWS 6

void print_matrix();

int is_game_over(int matrix[ROWS][COLUMNS], int player);

bool winning_move(int matrix[ROWS][COLUMNS], int player);

bool is_full(int matrix[ROWS][COLUMNS]);

bool drop_in_column(int matrix[ROWS][COLUMNS], int column, int player);

bool load_matrix(int matrix[ROWS][COLUMNS], int* player, char* filename);

bool save_matrix(int matrix[ROWS][COLUMNS], char* input);

#endif  // VIER_GEWINNT_H_
