#ifndef ASSIGN_H
#define ASSIGN_H

#include "../banker/building.h"

#define RDMRANGE 8

struct cell
{

	int type;
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

struct map *minMaxMap(struct map *newMap, struct map *testMap);

void printMatrixTime(struct map *newmap);

char charType(int type);

void printMatrix(struct map *newmap);

void printMatrixStat(struct map *newmap, int stat);

void stringType(int stat);


struct map *initMap(unsigned int maxH, unsigned int maxW);

int fillTown(struct map *map, int *buildingList, int roof, int **building_value);

void replaceTown(struct map *map, int *buildingList, int roof, int **building_value, int *nbreplacement);

int gateValue(int i);

int gateType(int type);

struct cell *replaceGlobalNeed(struct map *map, int *buildingList ,int *maxstat,int roof, int *a);

struct cell *searchGlobalNeed(struct map *map, int *buildingList, int *maxstat, int roof, int *a);

struct cell *generateRandomBuilding(struct map *map, int *buildingList, int *maxstat, int *a, int nbcompt);

int maxStat(struct cell *cell, int *stat);

struct building *getBat(int stat, struct building **buildingList);


#endif
