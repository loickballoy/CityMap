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

void testAssign(int compt, int roof)
{
	//init structs
	struct building **buildingList = initTownList();
	struct map *newmap = initMap(60,60,buildingList, compt, roof);

	//run the algo 


	//important values
	/*struct cell *Fcell = newmap->cells;
	struct cell *center = Fcell + newmap->maxHeight/2 + newmap->maxWidth*(newmap->maxWidth/2);*/

	//print
	printMatrix(newmap);

	//free
	freeList(buildingList);
	free(newmap->cells);
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
