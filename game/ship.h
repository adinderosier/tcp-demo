#ifndef SHIP_H
#define SHIP_H

#define VERT 0
#define HORIZ 1

// forward declaration of struct
struct Ship {};

// struct 'constructor'
struct Ship* create_ship(int len, int orient, int *locs);

// getters
int get_size(struct Ship *ship);
int get_orientation(struct Ship *ship);
int* get_locations(struct Ship *ship);
 
#endif // SHIP_H