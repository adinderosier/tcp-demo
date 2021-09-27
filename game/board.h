#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

struct Board;

struct Board* create_board();

void free_board(struct Board *board);

bool is_valid_placement(struct Board *board, struct Ship *ship, char *placement);

bool add_ship(struct Board *board, struct Ship *ship, char *placement);

void print_board(struct Board *board);

#endif // BOARD_H