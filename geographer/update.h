#ifndef UPDATE_H
#define UPDATE_H

struct cell;
struct map;

//!This functions computes a value to change the needs according to a distance from a cell
int ponderation(int x, int y, int val, int a, int b);

//!Using ponderation we update the values around a cell placed at coordinates x and y
void updateAround(struct map *map, int x, int y, int **building_value);

//!The same as updateAround but reversed no further explaination will be provided
void reverseUpdateAround(struct map *map, int a, int b, int **building_value);

//!Simple inequation that returns an int 0 or 1 casted to a char
char equation(int x, int y, int a, int b, int range);

//!A tool to give a cell a value
void attribuate(int x, int y, struct cell *cell, int *value, int a, int b);

//!The same as attribuate but reversed no further explaination will be provided
void reverseAttribuate(int x, int y, struct cell *cell, int *value, int a, int b);

#endif
