// for debugging purposes, driver function
#include "ship.h"
#include "board.h"

#define VERTICAL 0
#define HORIZONTAL 1

#define P1 1
#define P2 2

int main(int argc, char **argv) {
	struct Board *board = create_board();
	print_board(board);
	struct Ship *ship = create_ship(3, VERTICAL, P1);
	struct Ship *ship_two = create_ship(5, HORIZONTAL, P1); 
	add_ship(board, ship, "A10");
	add_ship(board, ship_two, "J1");
	print_board(board);
	free_ship(ship);
	free_ship(ship_two);
	free_board(board);
	return 0;
}