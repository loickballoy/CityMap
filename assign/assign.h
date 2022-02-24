#ifndef ASSIGN_H
#define ASSIGN_H

#include "../banker/building.h"

#define RDMRANGE 12

struct cell
{
	struct building *building;

	int stats[NBSTATS];
	/*int security;
	int job;
	int habitation;
	int economy;
	int health;*/

	int isRoadConnected;	
};

struct map
{
	struct cell *cells;
	int maxHeight;
	int maxWidth;
};

void analyseMatrix(struct map *newmap);

void printMatrixTime(struct map *newmap);

char charType(int type);

void printMatrix(struct map *newmap);

void printMatrixStat(struct map *newmap, int stat);

void stringType(int stat);


struct map *initMap(unsigned int maxH, unsigned int maxW, struct building **buildingList, int compt, int roof);

void updateNeeds(struct cell *cell, struct map *map, int compt, struct building **buildingList, int nbcompt, int roof);

struct cell *generateRandomBuilding(struct map *map, struct building **buildingList, int *maxstat, int nbcompt);

int maxStat(struct cell *cell, int *stat);

void recUpdate(struct cell *cell, struct map *map, int *stat, int compt, struct building **buildingList, int nbcompt, int roof);

struct building *getBat(int stat, struct building **buildingList);


#endif
