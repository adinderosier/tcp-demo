#include <stdlib.h>
#include <assert.h>
#include "ship.h"

struct Ship* create_ship(int size, int orientation, int player) {
	struct Ship *ship = calloc(1, sizeof(struct Ship));
	assert(ship != NULL);

	ship->size = size;
	ship->orientation = orientation;
	ship->player = player;
	return ship;
}

void free_ship(struct Ship *ship) {
	free(ship);
}

int get_size(struct Ship *ship) {
	return ship->size;
}

int get_orientation(struct Ship *ship) {
	return ship->orientation;
}

int get_player(struct Ship *ship) {
	return ship->player;
}