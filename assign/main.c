#include <stdio.h>
#include <stdlib.h>
#include "assign.h"
#include "../banker/need.c"

void testInitMap()
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
	free(buildingList);
	free(newmap);
}

int main(void)
{
	testInitMap();
	printf("hey\n");
	return 0;
}
