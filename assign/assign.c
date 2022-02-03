#include <stdio.h>
#include <stdlib.h>
#include "assign.h"

void initMap(unsigned int maxH, unsigned int maxW, struct building **buildingList)
{
	struct map newMap = malloc(sizeof(struct map));
	newMap->maxHeight = maxH;
	newMap->maxWidth = maxW;
	newMap->cells = malloc(maxH * maxW * sizeof(struct cells));

	struct cell *center = newMap->cells + maxH/2 + maxW/2;
	center->building = *buildingList;
}

void updateNeeds(struct cell *cell, struct map *map)
{
	//V1 dispertion en carré
	unsigned int posX = *cell->*building->x-((unsigned int)*cell->*building->*type->range);
	unsigned int posY = *cell->*building->y-((unsigned int)*cell->*building->*type->range);
	for(; posY < ((unsigned int)*cell->*building->*type->range)*2; posY++)
	{
		for(; posX <((unsigned int)*cell->*building->*type->range)*2; posX++)
		{
			//dispertion pondéré avec hausse des besoin d'habitation par cellule 
			struct cell *tempCell = *map->*(cells+(*map->maxHeight*posY + posX));
		}
	}


}
