#include <stdio.h>
#include <stdlib.h>
#include "assign.h"
#include "../banker/need.c"

void testInitMap()
{
	struct building **buildingList = initTownList();
	struct map *newmap = initMap(250,250,buildingList);
	struct cell *Fcell = *newmap->cells;
	struct cell *center = Fcell+125+ 125*125;
	printf("%u",(center->building->type->policy));
}

int main(void)
{
	testInitMap();
	printf("hey");
	return 0;
}
