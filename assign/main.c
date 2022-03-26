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
	char **buildind_label = load_building_labels();

	struct building **buildingList = initTownList();
	struct map *newmap = initMap(40,40);
	struct cell *center = newmap->cells + newmap->maxWidth/2 + newmap->maxWidth * newmap->maxHeight/2;
	center->building = *buildingList;
	updateAround(newmap, newmap->maxWidth/2, newmap->maxHeight/2, building_value);
	int i = 0;
	while( i < compt/2)
	{
		fillTown(newmap, buildingList, roof, building_value);
		i += 1;
	}

	//printMatrix(newmap);
	analyseMatrix_print(newmap);

	int *nbreplacement = malloc(sizeof(int));
	*nbreplacement = 0;
	int nbverif = 0;

	while(nbverif < 500)
	{
		replaceTown(newmap, buildingList, roof, building_value, nbreplacement);
		nbverif++;
	}

	printf(" nb replacement : %i \n", *nbreplacement);
	//printMatrix(newmap);
	analyseMatrix_print(newmap);

	while( i < compt)
	{
		fillTown(newmap, buildingList, roof, building_value);
		i += 1;
	}

	//printMatrix(newmap);
	analyseMatrix_print(newmap);

	*nbreplacement = 0;

	while(nbverif < 1000)
	{
		replaceTown(newmap, buildingList, roof, building_value, nbreplacement);
		nbverif++;
	}

	printf(" nb replacement : %i \n", *nbreplacement);
	//printMatrix(newmap);
	analyseMatrix_print(newmap);

	//free :
	free_building_list(building_value);
	free_building_list(buildind_label);
	free(newmap->cells);
	freeList(buildingList);
	free(newmap);
	free(nbreplacement);
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
