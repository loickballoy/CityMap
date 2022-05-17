#ifndef ASSIGN_TOOLS_H
#define ASSIGN_TOOLS_H

#include "../banker/building.h"

#define RDMRANGE 8

struct cell
{

	int type;
	struct building *building;

	int stats[NBSTATS];
	int isRoadConnected;
};

struct map
{
	struct cell *cells;
	int maxHeight;
	int maxWidth;
};

//! Analyses the matrix to make an average of all cells
void analyseMatrix(struct map *newmap);

//! Analyses the matrix and prints the need of each cells in the matrix
void analyseMatrix_print(struct map *newmap);

//! Prints the colored building matrix with a sleep second
void printMatrixTime(struct map *newmap);

//! Returns a symbol from the given type
char charType(int type);

//! Simple print of the colored building matrix
void printMatrix(struct map *newmap);

//! Print the stats of a given matrix
void printMatrixStat(struct map *newmap, int stat);

//! Prints the String variable associated with the type 
void stringType(int stat);

//! Simple getter: the stat -> the building type
int getValue(int i);

//! Simple getter: buildingType -> the according stat (could have been named better)
int getType(int type);

#endif


