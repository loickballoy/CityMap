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
		struct buildingType *type = buildingF->type;
		free(buildingF);
		free(type);
	}
	free(buildingL);
}

void testAssign()
{
	struct building **buildingList = initTownList();
	struct map *newmap = initMap(60,60,buildingList);

	//printf("%p\n",newmap);

	struct cell *Fcell = newmap->cells;

	//printf("%p Fcell's add\n",(Fcell));
	//printf("%p\n",(Fcell->building));

	struct cell *center = Fcell + newmap->maxHeight/2 + newmap->maxWidth*(newmap->maxWidth/2);

	printf("%p center's add\n",center);
	printf("%p\n",(center->building->type));

	printf("%u\n",(center->building->type->policy));

	printf("-----------------------------------------------------\n");

	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		if(upTest->habitation == 0)
			printf("%i  ;", (upTest->habitation));
		if(upTest->habitation != 0)
		{
			printf(COLOR_RED "%i ;" COLOR_RESET,(upTest->habitation)); 
		}
		if(j%(newmap->maxWidth) == 0){
			printf("\n");
		}
	}	
	/*
	struct cell *uptest = center - 2;
	printf("%p\n", uptest);
	printf("%i\n",(uptest->habitation));
	printf("%i\n",(uptest->job));
	printf("%i\n",(uptest->habitation));*/

	freeList(buildingList);
	free(newmap->cells);
	free(newmap);
}

void printMatrice(struct map *newmap)
{
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		if(upTest->habitation == 0)
			printf("%i  ;", (upTest->habitation));
		if(upTest->habitation != 0)
		{
			printf(COLOR_RED "%i ;" COLOR_RESET,(upTest->habitation)); 
		}
		if(j%(newmap->maxWidth) == 0){
			printf("\n");
		}
	}	
}

int main(void)
{
	testAssign();
	printf("hey\n");
	return 0;
}
