#ifndef UPDATE_H
#define UPDATE_H

struct cell;
struct map;

void updateAround(struct map *map, int x, int y, int **building_value);
char equation(int x, int y, int a, int b, int range);
void attribuate(int x, int y, struct cell *cell, int *value, int a, int b);
int ponderation(int x, int y, int val, int a, int b);

#endif
