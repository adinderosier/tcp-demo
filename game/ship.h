#ifndef SHIP_H
#define SHIP_H

// forward declaration of struct
struct Ship {};

// struct 'constructor'
struct Ship* create_ship(int len, int orient);
void free_ship(struct Ship *ship);

// getters
int get_size(struct Ship *ship);
int get_orientation(struct Ship *ship);
 
#endif // SHIP_H