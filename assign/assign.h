#ifndef ASSIGN_H
#define ASSIGN_H

#include "../banker/building.h"

struct cell{
	struct building *building;
	int security;
	int job;
	int habitation;
	int economy;
	int health;
	int isRoadConnected;	
};

struct map
{
	struct cell *cells;
	int maxHeight;
	int maxWidth;
};

void printMatrix(struct map *newmap);


struct map *initMap(unsigned int maxH, unsigned int maxW, struct building **buildingList);

void updateNeeds(struct cell *cell, struct map *map, int compt, struct building **buildingList);

int maxStat(struct cell *cell, int *stat);

void recUpdate(struct cell *cell, struct map *map, int *stat, int compt, struct building **buildingList);




#endif
