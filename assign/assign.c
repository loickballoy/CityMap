#include <stdio.h>
#include <stdlib.h>
#include "assign.h"
#include "../banker/need.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_RESET "\x1b[0m"

void printMatrix(struct map *newmap)
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


struct map *initMap(unsigned int maxH, unsigned int maxW, struct building **buildingList)
{
	struct map *newMap = malloc(sizeof(struct map));
	newMap->maxHeight = maxH;
	newMap->maxWidth = maxW;

	printf("%p map pointeur \n",newMap);

	struct cell *cells = malloc(sizeof(struct cell) * maxW * maxH);
	newMap->cells = cells;
	for(int i = 0; i < maxH*maxW; i++)
	{
		(cells+i)->security = 0;
		(cells+i)->job = 0;
		(cells+i)->habitation = 0;
		(cells+i)->economy = 0;
		(cells+i)->health = 0;
	}

	struct cell *Fcell = newMap->cells;
	struct cell *center = Fcell + maxW/2 + maxW*(maxH/2);

	struct building *Hall = *buildingList;
	center->building = Hall;
	Hall->x = maxW/2;
	Hall->y = maxH/2;
	updateNeeds(center, newMap, 0, buildingList);


	printf("hey hey iniMap works\n");
	return newMap;
}

void updateNeeds(struct cell *cell, struct map *map, int compt, struct building **buildingList)
{
	//V tout le temps en cercle pondéré
	//
	
	if(compt == 3){
		printf("hey hey update est fini\n");
		return;
	}

	//arret 
	
	struct cell *deficit;
	int maxdeficit = 0;
	int stats = 0;
	int *stat = &stats;

	int roof = 40;
	unsigned int posX = cell->building->x-((unsigned int)cell->building->type->range);
	unsigned int posY = cell->building->y-((unsigned int)cell->building->type->range);
	printf("%u \n", posY);
	printf("%u \n", cell->building->y);
	printf("%u \n", posX)

	int biasSecu = cell->security;
	int biasJob = cell->job;
	int biasHab = cell->habitation;
	int biasEco = cell->economy;
	int biasHeal = cell->health;


	unsigned int r = (unsigned int)cell->building->type->range; 
	
	struct cell *pos;
	unsigned int i = 0;
	unsigned int n = 0;
	for(n = 0; n < r / 4; n++)
	{
		pos= cell - r/2 + n;
		for(i = 0; i < r / 4 + n; i++)
		{
			struct cell *UpCell = pos+map->maxWidth*i;
			struct cell *DownCell = pos-map->maxWidth*i;
			float ponderation = ((float)(r/2-n+i)/(float)((r)));
			UpCell->habitation += biasHab - (int)(ponderation * (float)biasHab);
			UpCell->economy += biasEco - (int)(ponderation * (float)biasEco);
			UpCell->health += biasHeal -* (int)(ponderation * (float)biasHeal);
			if(UpCell->habitation >= roof && UpCell->habitation > maxdeficit)
			{
				printf("hey hey\n");
				maxdeficit = maxStat(UpCell, stat);
				deficit = UpCell; 
			}

			UpCell->security += biasSecu - (int)(ponderation * (float)biasSecu);
		        UpCell->job += biasJob - (int)(ponderation * (float)biasJob);
			DownCell->habitation += i == 0?0:biasHab -(int) (ponderation * (float)biasHab);
			if(DownCell->habitation >= roof && DownCell->habitation > maxdeficit)
			{
				maxdeficit = maxStat(DownCell, stat);
				deficit = DownCell;
			}

			DownCell->security += i ==0?0:biasSecu - (int)(ponderation * (float)biasSecu);
		        DownCell->job += i ==0?0:biasJob - (int)(ponderation * (float)biasJob);			
		}
	}

	for(; n < r/2 ; n++)
	{
		pos = cell - r/2 + n;
		for(i = 0; i < r/2; i++)
		{
			struct cell *UpCell = pos+map->maxWidth*i;
			struct cell *DownCell = pos-map->maxWidth*i;
			float ponderation = ((float)(r/2-n+i)/(float)(r));
			UpCell->habitation += biasHab -(int) (ponderation * (float)biasHab);
			if(UpCell->habitation >= roof && UpCell->habitation > maxdeficit)
			{
				maxdeficit = maxStat(UpCell, stat);
				deficit = UpCell;
			}

			UpCell->security -= biasSecu - (int) (ponderation * (float)biasSecu);
		        UpCell->job -= biasJob - (int)(ponderation * (float)biasJob);
			DownCell->habitation += i ==0?0:biasHab - (int)(ponderation * (float)biasHab);
			if(DownCell->habitation >= roof && DownCell->habitation > maxdeficit)
			{
				maxdeficit = maxStat(DownCell, stat);

				deficit = DownCell;
			}

			DownCell->security -=i ==0?0: biasSecu - (int)(ponderation * (float)biasSecu);
		        DownCell->job -= i ==0?0:biasJob - (int)(ponderation * (float)biasJob);	
		}
	}
	
	for(; n < (3 *r)/4 ; n++)
	{
		pos = cell + n - r/2;
		for(i = 0; i < r/2; i++)
		{
			if(!(i== 0 && n == r/2))
			{
				struct cell *UpCell = pos+map->maxWidth*i;
				struct cell *DownCell = pos-map->maxWidth*i;
				float ponderation = ((float)(n-r/2+i)/(float)(r));
				UpCell->habitation += biasHab - (int)(ponderation * (float)biasHab);
				if(UpCell->habitation >= roof && UpCell->habitation > maxdeficit)
				{		
					maxdeficit = maxStat(UpCell, stat);

					deficit = UpCell;
				}

				UpCell->security -= biasSecu - (int)(ponderation * (float)biasSecu);
		        	UpCell->job -= biasJob - (int)(ponderation * (float)biasJob);
				DownCell->habitation += i ==0?0:biasHab - (int)(ponderation * (float)biasHab);
				if(DownCell->habitation >= roof && DownCell->habitation > maxdeficit)
				{
					maxdeficit = maxStat(DownCell, stat);

					deficit = DownCell;
				}

				DownCell->security -= i ==0?0:biasSecu - (int)(ponderation * (float)biasSecu);
		        	DownCell->job -= i ==0?0:biasJob - (int)(ponderation * (float)biasJob);	
			}
		}
	}


	int k = 0;
	for(; n <= r; n++)
	{
		pos = cell + n - r/2;
		for(i = 0; i < r/2 - k; i++)
		{
			struct cell *UpCell = pos+map->maxWidth*i;
			struct cell *DownCell = pos-map->maxWidth*i;
			float ponderation = ((float)(n-r/2+i)/(float)(r));
			UpCell->habitation += biasHab - (int)(ponderation * (float)biasHab);
			if(UpCell->habitation >= roof && UpCell->habitation > maxdeficit)
			{
				maxdeficit = maxStat(UpCell, stat);

				deficit = UpCell;
			}

			UpCell->security -= biasSecu - (int)(ponderation * (float)biasSecu);
		        UpCell->job -= biasJob - (int)(ponderation * (float)biasJob);
			DownCell->habitation += i ==0?0:biasHab - (int)(ponderation * (float)biasHab);
			if(DownCell->habitation >= roof && DownCell->habitation > maxdeficit)
			{
				maxdeficit = maxStat(DownCell, stat);

				deficit = DownCell;
			}

			DownCell->security -= i ==0?0:biasSecu - (int)(ponderation * (float)biasSecu);
		        DownCell->job -= i ==0?0:biasJob - (int)(ponderation * (float)biasJob);	

		}
		k++;	

	}
	printf("%i maxdeficit, %i stat\n", maxdeficit, *stat);
	recUpdate(deficit, map, stat, compt, buildingList);

}

int maxStat(struct cell *cell, int *stat)
{
	int max = cell->security;
	*stat = 0;
	if(cell->job > max)
	{
		max = cell->job;
		*stat = 1;
	}
	if(cell->habitation > max)
	{
		max = cell->habitation;
		*stat = 2;
	}
	if(cell->economy > max)
	{
		max = cell->economy;
		*stat = 3;
	}
	if(cell->health > max)
	{
		max = cell->health;
		*stat = 4;
	}
	return max; 
}

void recUpdate(struct cell *cell, struct map *map, int *stat, int compt, struct building **buildingList)
{
	printMatrix(map);
	if(*stat == 0)
	{
		cell->building = *buildingList+1;
		updateNeeds(cell, map, compt+1, buildingList);
	}
	if(*stat == 1)
	{
		cell->building = *buildingList+14+compt;
		updateNeeds(cell, map, compt+1, buildingList);
	}
	if(*stat == 2)
	{
		cell->building = *buildingList+4+compt;
		updateNeeds(cell, map, compt+1, buildingList);
	}
	if(*stat == 3)
	{
		cell->building = *buildingList+18+compt;
		updateNeeds(cell, map, compt+1, buildingList);		
	}
	else
	{
		cell->building = *buildingList+2;
		updateNeeds(cell, map, compt+1, buildingList);
	}
}
