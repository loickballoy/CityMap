#include <stdio.h>
#include <stdlib.h>
//#include <criterion/criterion.h>
#include "read.h"
#include "write.h"
#include "building.h"
#include "need.h"


void testSelect()
{
	unsigned int *result = select(0);
	printf("TestHall [");
	for (int i = 0; i < 7; i++)
	{
		printf("%u,",*(result));
	}
}

void testNewBuild()
{
	struct building *result = build(0);
	struct buildingType *type = result->type;
	printf("%u", type->policy);
	free(result);
	free(type);
}

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

void testTownList()
{
	struct building **buildingL = initTownList();
	struct building *buildingF = *(buildingL+17);
	struct buildingType *type = buildingF->type;
	printf("%u", type->job);
	freeList(buildingL);
}

int main(void)
{
	testTownList();	
	return 0;
}

