#include <stdio.h>
#include <stdlib.h>
#include "assign.h"
#include "../banker/need.c"

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
	struct map *newmap = initMap(250,250,buildingList);

	//printf("%p\n",newmap);

	struct cell *Fcell = newmap->cells;

	//printf("%p Fcell's add\n",(Fcell));
	//printf("%p\n",(Fcell->building));

	struct cell *center = Fcell + newmap->maxHeight/2 + newmap->maxWidth*(newmap->maxWidth/2);

	printf("%p center's add\n",center);
	printf("%p\n",(center->building->type));

	printf("%u\n",(center->building->type->policy));

	printf("-----------------------------------------------------\n");
	
	struct cell *uptest = center - 2;
	printf("%p\n", uptest);
	printf("%u\n",(uptest->building->type->policy));


	freeList(buildingList);
	free(newmap->cells);
	free(newmap);
}

int main(void)
{
	testAssign();
	printf("hey\n");
	return 0;
}
