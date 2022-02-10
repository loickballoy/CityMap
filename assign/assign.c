#include <stdio.h>
#include <stdlib.h>
#include "assign.h"
#include "../banker/need.h"

struct map *initMap(unsigned int maxH, unsigned int maxW, struct building **buildingList)
{
	struct map *newMap = malloc(sizeof(struct map));
	newMap->maxHeight = maxH;
	newMap->maxWidth = maxW;

	printf("%p map pointeur \n",newMap);

	struct cell *cells = malloc(sizeof(struct cell) * maxW * maxH);
	newMap->cells = cells;

	printf("%p cells pointeur\n",newMap->cells);

	struct cell *Fcell = newMap->cells;

	printf("%p Fcell pointeur\n", Fcell);
	struct cell *center = Fcell + maxW/2 + maxW*(maxH/2);

	printf("%p center pointeur %p \n",center, center->building);
	printf("%p buildingList pointeur\n", *buildingList);

	struct building *Hall = *buildingList;

	printf("%u buildingList policy first\n", Hall->type->policy);
	center->building = Hall;
	updateNeeds(center, newMap);


	printf("hey hey iniMap works\n");
	return newMap;
}

void updateNeeds(struct cell *cell, struct map *map)
{
	//V1 dispertion en carré
	unsigned int posX = cell->building->x-((unsigned int)cell->building->type->range);
	unsigned int posY = cell->building->y-((unsigned int)cell->building->type->range);
	printf("%u \n", posY);
	printf("%u \n", cell->building->y);
	for(; posY < ((unsigned int)cell->building->type->range)*2; posY++)
	{
		for(; posX <((unsigned int)cell->building->type->range)*2; posX++)
		{
			//dispertion pondéré avec hausse des besoin d'habitation par cellule
			struct cell *tempCell = map->cells+(map->maxHeight*posY + posX);
			unsigned int ponderationX = cell->building->x-map->maxWidth * cell->building->y - tempCell->building->x;
			unsigned int ponderationY = cell->building->y-map->maxWidth * cell->building->x - tempCell->building->y;
			unsigned int ponderation = ponderationX+ponderationY;
			ponderation += 0;
			tempCell->habitation += 50 - ponderation;
		}
		posX += map->maxWidth - 2*cell->building->type->range;
	}
}
