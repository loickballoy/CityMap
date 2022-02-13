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
void analyseMatrix(struct map *newmap);
void printMatrix(struct map *newmap);
void printMatrixHab(struct map *newmap);
void printMatrixJob(struct map *newmap);
void printMatrixEco(struct map *newmap);
void printMatrixHeal(struct map *newmap);



struct map *initMap(unsigned int maxH, unsigned int maxW, struct building **buildingList, int compt);

void updateNeeds(struct cell *cell, struct map *map, int compt, struct building **buildingList, int nbcompt);

int maxStat(struct cell *cell, int *stat);

void recUpdate(struct cell *cell, struct map *map, int *stat, int compt, struct building **buildingList, int nbcompt);




#endif
