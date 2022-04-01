#ifndef ROAD_H
#define ROAD_H

void square(struct map *map, int x, int y, int len, int *a, int *b);

void roadToConnect(struct map *map, int x, int y);

void cleanWay(struct map *map);

int isGoodWay(struct map *map, int x, int y);

#endif
