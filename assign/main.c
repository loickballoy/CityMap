#include <stdio.h>
#include <stdlib.h>
#include "assign.h"
#include "../banker/need.c"

#define COLOR_RED "\x1b[31m"
#define COLOR_RESET "\x1b[0m"

void freeList(struct building **buildingL)
{
	for(int i = 0; i < 21; i++)
	{
		struct building *buildingF = *(buildingL+i);
		struct buildingType *values = buildingF->values;
		free(buildingF);
		free(values);
	}
	free(buildingL);
}

void testAssign(int compt)
{
	struct building **buildingList = initTownList();
	struct map *newmap = initMap(60,60,buildingList, compt);

	struct cell *Fcell = newmap->cells;

	struct cell *center = Fcell + newmap->maxHeight/2 + newmap->maxWidth*(newmap->maxWidth/2);

	printf("-----------------------------------------------------\n");

	printMatrixHab(newmap);/*
	printf("===========================================================================\n\n =========================================================================================\n");
	printMatrixEco(newmap);
	printf("===========================================================================\n\n =========================================================================================\n");
	printMatrixJob(newmap);
	printf("===========================================================================\n\n =========================================================================================\n");
	printMatrixHeal(newmap);
	printf("===========================================================================\n\n =========================================================================================\n");

	*/printMatrix(newmap);


	freeList(buildingList);
	free(newmap->cells);
	free(newmap);
}

void printMatrice(struct map *newmap)
{
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		if(upTest->building == NULL)
			printf("    ;", (upTest->habitation));
		if(upTest->building != NULL)
		{
			printf(COLOR_RED "%i ;" COLOR_RESET,(upTest->habitation)); 
		}
		if(j%(newmap->maxWidth) == 0){
			printf("\n");
		}
	}	
}

int main(int argc, int **argv)
{
	testAssign(0);
	testAssign(2);
	/*if(argc == 1)
		testAssign(5);
	if(argc != 1)
		testAssign(argv[1]);
	printf("hey\n");*/
	return 0;
}
