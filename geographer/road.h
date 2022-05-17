#ifndef ROAD_H
#define ROAD_H

//!A tool to find the closest road
void square(struct map *map, int x, int y, int len, int *a, int *b);

//!creates a road between to cells with their coordinates given
void createWay(struct map* map, int x, int y, int a, int b);

//!Uses square to connect roads together
void roadToConnect(struct map *map, int x, int y);

//!Removes eventual useless or extra roads
void cleanWay(struct map *map);

//!Checks if a road connects to the rest
int isGoodWay(struct map *map, int x, int y);

#endif
