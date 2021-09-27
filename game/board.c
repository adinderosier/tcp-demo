#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "ship.h"

#define VERTICAL 0
#define HORIZONTAL 1
#define OCCUPIED 1
#define MAX_DIMEN 10
#define CHAR_OFFSET 'A'
#define INT_OFFSET '1'
#define FIRST 0
#define SECOND 1
#define PLACEMENT_SIZE 3 

struct Board {
	int **grid;
};

struct Board* create_board() {
	struct Board *board = calloc(1, sizeof(struct Board));
	assert(board != NULL);
	board->grid = calloc(MAX_DIMEN, sizeof(int*));
	assert(board->grid != NULL);
	for (int i = 0; i < MAX_DIMEN; ++i) {
		board->grid[i] = calloc(MAX_DIMEN, sizeof(int));
		assert(board->grid[i] != NULL);
	}
	return board;
}

void free_board(struct Board *board) {
	for (int i = 0; i < MAX_DIMEN; ++i) {
		free(board->grid[i]);
	}
	free(board->grid);
	free(board);
}

bool is_valid_placement(struct Board *board, struct Ship *ship, char *placement) {
	int row_index = placement[FIRST] - CHAR_OFFSET;
	int col_index;

	if (strlen(placement) == PLACEMENT_SIZE) {
		col_index = strtol(++placement, NULL, 10) - 1;
	} else {
		col_index = placement[SECOND] - INT_OFFSET;
	}

	if (ship->orientation == VERTICAL) {
		// if the col index is invalid, no need to loop
		if (col_index >= MAX_DIMEN || col_index < 0) {

			printf("col index exceeded, %d, :(\n", col_index);
			return false;
		}

		for (int i = 0; i < ship->size; ++i) {
			// if it's out of bounds
			if (i + row_index >= MAX_DIMEN || i + row_index < 0) {
				printf("row index oob :(\n");
				return false;
			}

			if (board->grid[i + row_index][col_index] == OCCUPIED) {
				printf("occupied :(\n");
				return false;
			}

		}
	}

	else if (ship->orientation == HORIZONTAL) {
		// if the row index is invalid, no need to loop
		if (row_index >= MAX_DIMEN || row_index < 0) {
			return false;
		}

		for (int i = 0; i < ship->size; ++i) {
			// if it's out of bounds

			if (i + col_index >= MAX_DIMEN || i + col_index < 0) {
				return false;
			}
			printf("row_index: %d, i + col_index: %d\n", row_index, i + col_index);
			if (board->grid[row_index][i + col_index] == OCCUPIED) {
				return false;
			}

		}
	}

	else {
		return false;
	}

	printf("valid placement!\n");
	return true;
}

bool add_ship(struct Board *board, struct Ship *ship, char *placement) {
	if (strlen(placement) > PLACEMENT_SIZE || strlen(placement) < PLACEMENT_SIZE - 1) {
		return false;
	}

	printf("placement = %s\n", placement);

	if (is_valid_placement(board, ship, placement)) {
		printf("valid placement! now placing\n");
		int row_index = placement[FIRST] - CHAR_OFFSET;
		int col_index;
		
		if (strlen(placement) == PLACEMENT_SIZE) {
			col_index = strtol(++placement, NULL, 10) - 1;
		} else {
			col_index = placement[SECOND] - INT_OFFSET;
		}

		printf("row index = %d, col index = %d\n", row_index, col_index);

		if (ship->orientation == VERTICAL) {
			printf("we are vertical\n");
			for (int i = 0; i < ship->size; ++i) {
				board->grid[row_index + i][col_index] = OCCUPIED;
			}
		return true;
		}

		else if (ship->orientation == HORIZONTAL) {
			printf("we are horizontal\n");
			for (int i = 0; i < ship->size; ++i) {
				board->grid[row_index][col_index + i] = OCCUPIED;
			}
		return true;
		}
	} 

	return false;
}

void print_board(struct Board *board) {
	for (int i = 0; i < MAX_DIMEN; ++i) {
		for (int j = 0; j < MAX_DIMEN; ++j) {
			if (board->grid[i][j] == 0) {
				printf("- ");
			} else {
				printf("o ");
			}
		}
		printf("\n");
	}
	printf("\n");
}