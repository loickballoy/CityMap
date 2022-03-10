#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void testAssign(int compt, int roof)
{
	//init structs
	struct building **buildingList = initTownList();
	struct map *newmap = initMap(60,60,buildingList, compt, roof);
	
	int *statmin = (int *) malloc( sizeof(int) * NBSTATS);
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
	int rdm = rand() % 100;
	rdm -= 50;
	roof += rdm;
	int broof = roof;

	//produit 100 autre map et regarde laquel est la meilleur

	while(i < 10000)
	{

		int *tempstat = (int *) malloc(sizeof(int) * NBSTATS);

		for(int cal = 0; cal < NBSTATS; ++cal)
			*(tempstat+cal) = 0;

		int tempsum = 0;

		rec_initMap(tempmap,60,60,buildingList,compt,roof);
		recAnalyseMatrix(tempmap, tempstat);
		for(int j = 0; j < NBSTATS; ++j)
			tempsum += *(tempstat+j);
		if(tempsum < minsum)
		{
			printf("hey hey tempsum < minsum : %i\n", roof);
			minsum = tempsum;
			statmin = tempstat;		
			newmap = tempmap;
			broof = roof;
			srand(tempsum);
			rdm = rand() % 100;
			rdm -= 50;
			roof += rdm;
			roof-= 10;
		}
		if(i % 100 == 0)
		{
			srand(tempsum);
			rdm = rand() % 100;
			rdm -= 50;
			roof += rdm; 
		}
		if(roof < -100)
			roof *= -1;
		//printf("minsum = %i || tempsum = %i\n", minsum,tempsum);
		++i;
		/*if(i < 50)
			printf("roof : %i \n",roof);*/
		free(tempstat);
	}
	printf("best roof = %i\n", broof);
	//run the algo 


	//important values
	/*struct cell *Fcell = newmap->cells;
	struct cell *center = Fcell + newmap->maxHeight/2 + newmap->maxWidth*(newmap->maxWidth/2);*/

	//print
	printMatrix(newmap);

	//free

	if(tempmap != newmap)
	{
		free(tempmap->cells);
		free(tempmap);
	}
	free(newmap->cells);
	//if(tempstat != statmin)
		//free(tempstat);
	free(statmin);
	/*if(tempstat)
		free(tempstat);*/
	//free(statmin);

	freeList(buildingList);
	free(newmap);
}

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("You have to pass two arguments: ./main [nbbat] [roof]");
		return 0;
	}
	//init values
	int nbbat = (int) atol (argv[1]);
	int roof = (int) atol (argv[2]);

	//test
	testAssign(nbbat, roof);
	return 0;
}
