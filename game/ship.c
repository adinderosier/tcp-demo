#include <stdlib.h>
#include <assert.h>
#include "ship.h"

struct Ship {
	int size;
	int orientation;
};

struct Ship* create_ship(int len, int orient) {
	Ship *ship = calloc(sizeof(struct Ship), 1);
	assert(ship != NULL);

	ship->size = len;
	ship->orientation = orient;
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