#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "assign.h"
#include "../banker/need.c"
#include "../loader/read.c"
#include "../geographer/update.h"


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

void testAssign(int compt, int roof)
{
	//init structs
	int **building_value = load_building_value();

	struct building **buildingList = initTownList();
	struct map *newmap = initMap(60,60,buildingList, compt, roof);
	struct cell *center = newmap->cells + newmap->maxWidth/2 + newmap->maxWidth * newmap->maxHeight/2;
	center->building = *buildingList;
	updateAround(newmap, newmap->maxWidth/2, newmap->maxHeight/2, building_value);
	printMatrix(newmap);
	int i = 0;
	while( i < compt)
	{
		fillTown(newmap, buildingList, roof, building_value);
		i += 1;
	} 
	/*int *statmin = (int *) malloc( sizeof(int) * NBSTATS);
	for(int cal = 0; cal < NBSTATS; ++cal)
			*(statmin+cal) = 0;
	//printf("%i | \n", NBSTATS);
	//printf("hey hey cest le calloc : %i \n", *statmin);
	//printf("hey hye \n ");

	int minsum = 0;

	recAnalyseMatrix(newmap,statmin);
	for(int n = 0; n < NBSTATS; ++n)
		minsum += *(statmin + n);

	int i = 0;
	struct map *tempmap = malloc(sizeof(struct map));
	struct cell *tempcells = malloc(sizeof(struct cell) * 60 * 60);
	tempmap->cells = tempcells;

	srand(time(0));
	int rdm = rand() % 20;
	rdm -= 10;
	roof += rdm;
	int broof = roof;

	//produit 100 autre map et regarde laquel est la meilleur

	while(i < 1000)
	{

		int *tempstat = (int *) malloc(sizeof(int) * NBSTATS);

		for(int cal = 0; cal < NBSTATS; ++cal)
			*(tempstat+cal) = 0;

		int tempsum = 0;

		rec_initMap(tempmap,60,60,buildingList,compt,roof);
		recAnalyseMatrix(tempmap, tempstat);
		for(int j = 0; j < NBSTATS; ++j)
		{
			tempsum += *(tempstat+j);
			//printf("tempstat(%i) : %i  ||",j,*(tempstat+j));
		}
		//printf("tempsum = %i\n",tempsum);
		if(tempsum <= minsum)
		{
			printf("hey hey tempsum < minsum : %i\n", roof);
			minsum = tempsum;
			statmin = tempstat;
			newmap = tempmap;
			broof = roof;
			srand(time(0));
			rdm = rand() % 20;
			rdm -= 10;
			roof += rdm;
			roof-= 5;
		}
		if(i % 50 == 0)
		{
			srand(i);
			rdm = rand() % 20;
			rdm -= 10;
			roof += rdm;
		}
		if(roof < -100)
			roof *= -1;
		//printf("minsum = %i || tempsum = %i\n", minsum,tempsum);
		++i;
		//if(i < 50)
		//printf("roof : %i | tempsum: %i \n",roof, tempsum);
		free(tempstat);
	}
	printf("best roof = %i\n", broof);
	//run the algo


	//important values
	*struct cell *Fcell = newmap->cells;
	struct cell *center = Fcell + newmap->maxHeight/2 + newmap->maxWidth*(newmap->maxWidth/2);*/

	//print
	//printMatrix(newmap);
	/*printMatrixStat(newmap, 1);
	printMatrixStat(newmap, 2);
	printMatrixStat(newmap, 3);
	printMatrixStat(newmap, 4);*/

	//free*/

	/*if(tempmap != newmap)
	{
		free(tempmap->cells);
		free(tempmap);
	}*/
	printMatrixStat(newmap, 2);
	free(newmap->cells);
	//if(tempstat != statmin)
		//free(tempstat);
	//free(statmin);
	/*if(tempstat)
		free(tempstat);*/
	//free(statmin);

	freeList(buildingList);
	free(building_value);
	free(newmap);
}

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("You have to pass two arguments: ./main [nbbat] [roof] \n");
		return 0;
	}
	//init values
	int nbbat = (int) atol (argv[1]);
	int roof = (int) atol (argv[2]);

	//test
	testAssign(nbbat, roof);
	return 0;
}
