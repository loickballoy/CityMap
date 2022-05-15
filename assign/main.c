#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "assign.h"
#include "../banker/need.c"
#include "../loader/read.c"
#include "../geographer/update.h"
#include "../geographer/road.c"


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

/*void fill_and_replace(struct map *newmap, struct building **buildingList, int roof, int **building_value, int compt, int verif, int c)
{
	int i = 0;
	while( i < compt)
	{
		fillTown(newmap, buildingList, roof, building_value);
		i += 1;
	}

	int *nbreplacement = malloc(sizeof(int));
	*nbreplacement = 0;
	int nbverif = 0;
	if(c > 6)
	{
		while(nbverif < verif)
		{
			replaceTown(newmap, buildingList, roof, building_value, nbreplacement);
			nbverif++;
		}
		printf("nbreplacement : %i", *nbreplacement);
	}

	free(nbreplacement);
}*/

struct map *testAssign(int compt, int roof)
{
	//init structs
	int **building_value = load_building_value();
	char **buildind_label = load_building_labels();
	//struct building **buildingList2 = initTownList();
	int *buildingList = initTownList3(compt, 1);
	int *_buildingList = initTownList3(compt, 1);
	int i = 0;
	int nbbat = 0;
	while(i < 6)
	{
		printf("%u \n", *(buildingList+i));
		nbbat += *(buildingList+i);
		i++;
	}
	struct map *newmap = initMap(40,40);
	struct map *testmap = initMap(40,40);
	printf("nb_sub = %i; \n", buildingList[6]);
	struct cell **Subways = generateRandomSubway(newmap, buildingList);

	//init first bat
	struct cell *center = newmap->cells + newmap->maxWidth/2 + newmap->maxWidth * newmap->maxHeight/2;
	center->type = 0;
	(center+1)->type = 6;
	(center-1)->type = 6;
	updateAround(newmap, newmap->maxWidth/2, newmap->maxHeight/2, building_value);

	//start the filling
	
	int numOff = 0;
	int numPro = 0;
	int numSho = 0;
	int numHos = 0;
	int numCom = 0;
	int ty = fillTown(newmap, buildingList, roof, building_value);
	printf("first gen \n");
	printMatrix(newmap);
	int _ty = ty;
	*testmap = *newmap;
	printMatrix(testmap);
	printf("test first gen  \n");
	for(int n = 0; n < nbbat - 1 && ty != -10; n++)
	{ 
		ty = fillTown(newmap, buildingList, roof, building_value);
		_ty = fillTown(testmap, _buildingList, roof, building_value);
		//printMatrix(newmap);

		if (minMaxMap(newmap, testmap) == testmap)
		{
			printf("a new map has been chosen\n");
			*newmap = *testmap;
			*buildingList = *_buildingList;
			ty = _ty;
		}

		else
		{
			*testmap = *newmap;
			*_buildingList = *buildingList;
		}
		
		if (ty == 1)
			numPro += 1;
		else if (ty == 2)
			numOff += 1;
		else if (ty == 3)
			numCom += 1;
		else if (ty == 4)
			numSho += 1;
		else
			numHos += 1;
	}
	printf("number of offices = %i\n", numOff);

	printf("number of properties = %i\n", numPro);

	printf("number of shops = %i\n", numSho);

	printf("number of hospitals = %i\n", numHos);

	printf("number of bavures = %i\n", numCom);

	printMatrix(newmap);
	analyseMatrix(newmap);

	//start replacement
	int *nbreplacement = malloc(sizeof(int));
	*nbreplacement = 0;
	for(int n = 0; n < nbbat*2; n++)
	{
		replaceTown(newmap, buildingList, roof, building_value, nbreplacement);
	}
	printf("nbreplacement : %i\n", *nbreplacement);
	printMatrix(newmap);
	analyseMatrix(newmap);

	//free
	free(nbreplacement);
	//free(newmap->cells);       axel
	//free(newmap);              axel
	//freeList(buildingList2);
	free_building_list((void **)building_value);
	free_building_list((void **)buildind_label);
	free(buildingList);
	return newmap;
}
/*

int main(int argc, char **argv)
{
	//init time
	float temps;
  clock_t t1, t2;
  t1 = clock();

  // Ton programme
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

	//calcule de temps
	t2 = clock();
  temps = (float)(t2-t1)/CLOCKS_PER_SEC;
  printf("temps = %f\n", temps);
	return 0;
}
*/
