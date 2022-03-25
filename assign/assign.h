#ifndef ASSIGN_H
#define ASSIGN_H

#include "../banker/building.h"

#define RDMRANGE 8

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

void analyseMatrix_print(struct map *newmap);

void recAnalyseMatrix(struct map *newmap, int *stat);

void printMatrixTime(struct map *newmap);

char charType(int type);

void printMatrix(struct map *newmap);

void printMatrixStat(struct map *newmap, int stat);

void stringType(int stat);


struct map *initMap(unsigned int maxH, unsigned int maxW, struct building **buildingList, int compt, int roof);

void rec_initMap(struct map *newMap, unsigned int maxH, unsigned int maxW, struct building **buildingList, int compt, int roof);

void fillTown(struct map *map, struct building **buildingList, int roof, int **building_value);

//void updateNeeds(struct cell *cell, struct map *map, int compt, struct building **buildingList, int nbcompt, int roof);

struct cell *searchGlobalNeed(struct map *map, int *maxstat, int roof, int *a, int *b);

struct cell *generateRandomBuilding(struct map *map, struct building **buildingList, int *maxstat, int *a, int nbcompt);

int maxStat(struct cell *cell, int *stat);

void recUpdate(struct cell *cell, struct map *map, int *stat, int compt, struct building **buildingList, int nbcompt, int roof);

struct building *getBat(int stat, struct building **buildingList);


#endif
