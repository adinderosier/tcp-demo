#ifndef SHIP_H
#define SHIP_H

struct Ship {
	int size;
	int orientation;
	int player;
};

// struct 'constructor'
struct Ship* create_ship(int len, int orient, int player);
void free_ship(struct Ship *ship);

// getters
int get_size(struct Ship *ship);
int get_orientation(struct Ship *ship);
int get_player(struct Ship *ship);

 
#endif // SHIP_H