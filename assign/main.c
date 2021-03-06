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


struct map *testAssign(int compt, int roof)
{
	//init structs
	int **building_value = load_building_value();
	char **buildind_label = load_building_labels();
	int *buildingList = initTownList3(compt, 1);
	int *_buildingList = initTownList3(compt, 1);
	int i = 0;
	int nbbat = 0;
	while(i < 6)
	{
		nbbat += *(buildingList+i);
		i++;
	}
	int truc = 50 + compt/2000;
	truc += truc%2;
	struct map *newmap = initMap(truc, truc);

	struct map *testmap = initMap(truc, truc);

	int nb_sub = buildingList[6];
	struct cell **Subways = generateRandomSubway(newmap, buildingList, building_value);
	printMatrix(newmap);
	generateRdmRoads(newmap, nb_sub, Subways);

	//init first bat

	struct cell *center = newmap->cells + newmap->maxWidth/2 +newmap->maxWidth * newmap->maxHeight/2;
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

	printMatrix(newmap);
	int _ty = ty;
	*testmap = *newmap;
	printMatrix(testmap);

	for(int n = 0; n < nbbat - 1 && ty != -10; n++)
	{
		ty = fillTown(newmap, buildingList, roof, building_value);
		_ty = fillTown(testmap, _buildingList, roof, building_value);


		if (minMaxMap(newmap, testmap) == testmap)
		{

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

	printf("number of police stations = %i\n", numCom);

	printMatrix(newmap);
	analyseMatrix(newmap);

	//start replacement
	int *nbreplacement = malloc(sizeof(int));
	*nbreplacement = 0;
	for(int n = 0; n < nbbat*2; n++)
	{
		replaceTown(newmap, buildingList, roof, building_value, nbreplacement);
	}

	printMatrix(newmap);
	analyseMatrix(newmap);

	//free
	free(nbreplacement);
	//free(newmap->cells);      // axel
	//free(newmap);             // axel
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
}*/
