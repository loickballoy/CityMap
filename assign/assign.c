#include <stdio.h>
#include <stdlib.h>
#include "assign.h"
#include "../banker/need.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_RESET "\x1b[0m"

void analyseMatrix(struct map *newmap)
{
	int nbbat = 0;
	int secu = 0;
	int hab = 0;
	int job = 0;
	int eco = 0;
	int heal = 0;
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *uptest = newmap->cells + j;
		if(uptest->building != NULL)
		{
			secu += uptest->security;
			hab += uptest->habitation;
			job += uptest->job;
			eco += uptest->economy;
			heal += uptest->health;
			nbbat++;
		}
	}
	printf("MOY SECU = %i\n", secu/nbbat);
	printf("MOY HAB = %i\n", hab/nbbat);
	printf("MOY JOB = %i\n", job/nbbat);
	printf("MOY ECO = %i\n", eco/nbbat);
	printf("MOY HEAL = %i\n", heal/nbbat);
}


void printMatrix(struct map *newmap)
{
	int nbbat = 0;
	printf("HABITATION\n");
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		if(upTest->building == NULL)
			printf("    ;", (upTest->habitation));
		if(upTest->building != NULL)
		{
			nbbat++;
			printf(COLOR_RED "%i  ;" COLOR_RESET,(upTest->building->values->habitation)); 
		}
		if(j%(newmap->maxWidth) == 0){
			printf("\n");
		}
	}
	printf("NBBAT = %i\n", nbbat);
	printf("\n");
}


void printMatrixHab(struct map *newmap)
{
	printf("HABITATION\n");
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
	printf("\n");
}

void printMatrixJob(struct map *newmap)
{
	printf("JOBB\n");
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		if(upTest->job== 0)
			printf("%i  ;", (upTest->job));
		if(upTest->job != 0)
		{
			printf(COLOR_RED "%i ;" COLOR_RESET,(upTest->job)); 
		}
		if(j%(newmap->maxWidth) == 0){
			printf("\n");
		}
	}
	printf("\n");
}

void printMatrixEco(struct map *newmap)
{
	printf("ECONOMY\n");
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		if(upTest->economy == 0)
			printf("%i  ;", (upTest->economy));
		if(upTest->economy != 0)
		{
			printf(COLOR_RED "%i ;" COLOR_RESET,(upTest->economy)); 
		}
		if(j%(newmap->maxWidth) == 0){
			printf("\n");
		}
	}
	printf("\n");
}

void printMatrixHeal(struct map *newmap)
{
	printf("HEALTH\n");
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		if(upTest->health == 0)
			printf("%i  ;", (upTest->health));
		if(upTest->health != 0)
		{
			printf(COLOR_RED "%i ;" COLOR_RESET,(upTest->health)); 
		}
		if(j%(newmap->maxWidth) == 0){
			printf("\n");
		}
	}
	printf("\n");
}



struct map *initMap(unsigned int maxH, unsigned int maxW, struct building **buildingList, int compt)
{
	struct map *newMap = malloc(sizeof(struct map));
	newMap->maxHeight = maxH;
	newMap->maxWidth = maxW;

	printf("%p map pointeur \n",newMap);

	struct cell *cells = malloc(sizeof(struct cell) * maxW * maxH);
	newMap->cells = cells;
	for(int i = 0; i < (int) (maxH*maxW); i++)
	{
		(cells+i)->security = 0;
		(cells+i)->job = 0;
		(cells+i)->habitation = 0;
		(cells+i)->economy = 0;
		(cells+i)->health = 0;
		(cells+i)->building = NULL;
	}

	struct cell *Fcell = newMap->cells;
	struct cell *center = Fcell + maxW/2 + maxW*(maxH/2);

	struct building *Hall = *buildingList;
	center->building = Hall;
	printf("%i habitation stat \n", Hall->values->habitation);
	Hall->x = maxW/2;
	Hall->y = maxH/2;
	updateNeeds(center, newMap, 0, buildingList, compt);


	printf("hey hey iniMap works\n");
	return newMap;
}



void updateNeeds(struct cell *cell, struct map *map, int compt, struct building **buildingList, int nbcompt)
{
	//V tout le temps en cercle pondéré
	//
	
	if(compt == nbcompt){
		printf("hey hey update est fini\n");
		return;
	}

	//arret
	
	
	struct cell *deficit;
	int maxdeficit = 0;
	int stats = 0;
	int *stat = &stats;
	int maxiStat= 0;
	int *maxStats = &maxiStat;

	int roof = 40;
	/*unsigned int posX = cell->building->x-((unsigned int)cell->building->values->range);
	unsigned int posY = cell->building->y-((unsigned int)cell->building->values->range);
	printf("%u \n", posY);
	printf("%u \n", cell->building->y);
	printf("%u \n", posX);*/

	int biasSecu = cell->building->values->security;
	int biasJob = cell->building->values->job;
	int biasHab = cell->building->values->habitation;
	int biasEco = cell->building->values->economy;
	int biasHeal = cell->building->values->health;

	//printf("%i Secu, %i Job, %i Hab, %i Eco, %i Heal\n",biasSecu,biasJob,biasHab,biasEco,biasHeal);

	int maxTemp = 0;

	unsigned int r = (unsigned int)cell->building->values->range; 
	
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
			UpCell->health += biasHeal - (int)(ponderation * (float)biasHeal);
			UpCell->security += biasSecu - (int)(ponderation * (float)biasSecu);
		        UpCell->job += biasJob - (int)(ponderation * (float)biasJob);
			maxTemp = maxStat(UpCell, stat);

			//le fait de calculer toujours les up avant les down fait que les premiers besoins a etre satisfait seront les besoins des cellules up

			if(maxTemp>= roof && maxTemp > maxdeficit && UpCell->building == NULL)
			{
				maxdeficit = maxTemp;
				*maxStats = *stat;
				deficit = UpCell; 
			}



			DownCell->habitation += i == 0?0:biasHab -(int) (ponderation * (float)biasHab);
			DownCell->economy += i == 0?0:biasEco -(int) (ponderation * (float)biasEco);
			DownCell->health += i == 0?0:biasHeal -(int) (ponderation * (float)biasHeal);
			DownCell->security += i ==0?0:biasSecu - (int)(ponderation * (float)biasSecu);
		        DownCell->job += i ==0?0:biasJob - (int)(ponderation * (float)biasJob);	
			maxTemp = maxStat(DownCell, stat);

			if(maxTemp  >= roof && maxTemp > maxdeficit && DownCell->building == NULL)
			{
				maxdeficit = maxTemp;
				*maxStats = *stat;
				deficit = DownCell;
			}

		}
	}

	for(; n < r/2 ; n++)
	{
		pos = cell - r/2 + n;
		for(i = 0; i < r/2; i++)
		{
			
			struct cell *UpCell = pos+map->maxWidth*i;
			struct cell *DownCell = pos-map->maxWidth*i;
			float ponderation = ((float)(r/2-n+i)/(float)((r)));
			UpCell->habitation += biasHab - (int)(ponderation * (float)biasHab);
			UpCell->economy += biasEco - (int)(ponderation * (float)biasEco);
			UpCell->health += biasHeal - (int)(ponderation * (float)biasHeal);
			UpCell->security += biasSecu - (int)(ponderation * (float)biasSecu);
		        UpCell->job += biasJob - (int)(ponderation * (float)biasJob);
			maxTemp = maxStat(UpCell, stat);

			if(maxTemp>= roof && maxTemp > maxdeficit &&  UpCell->building == NULL)
			{
				maxdeficit = maxTemp;
				*maxStats = *stat;
				deficit = UpCell; 
			}


			DownCell->habitation += i == 0?0:biasHab -(int) (ponderation * (float)biasHab);
			DownCell->economy += i == 0?0:biasEco -(int) (ponderation * (float)biasEco);
			DownCell->health += i == 0?0:biasHeal -(int) (ponderation * (float)biasHeal);
			DownCell->security += i ==0?0:biasSecu - (int)(ponderation * (float)biasSecu);
		        DownCell->job += i ==0?0:biasJob - (int)(ponderation * (float)biasJob);	
			maxTemp = maxStat(DownCell, stat);

			if(maxTemp  >= roof && maxTemp > maxdeficit && DownCell->building == NULL)
			{
				maxdeficit = maxTemp;
				*maxStats = *stat;
				deficit = DownCell;
			}
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
				float ponderation = ((float)(n-r/2+i)/(float)((r)));
				UpCell->habitation += biasHab - (int)(ponderation * (float)biasHab);
				UpCell->economy += biasEco - (int)(ponderation * (float)biasEco);
				UpCell->health += biasHeal - (int)(ponderation * (float)biasHeal);
				UpCell->security += biasSecu - (int)(ponderation * (float)biasSecu);
				UpCell->job += biasJob - (int)(ponderation * (float)biasJob);
				maxTemp = maxStat(UpCell, stat);

				if(maxTemp>= roof && maxTemp > maxdeficit && UpCell->building == NULL)
				{
					maxdeficit = maxTemp;
					*maxStats = *stat;
					deficit = UpCell; 
				}


				DownCell->habitation += i == 0?0:biasHab -(int) (ponderation * (float)biasHab);
				DownCell->economy += i == 0?0:biasEco -(int) (ponderation * (float)biasEco);
				DownCell->health += i == 0?0:biasHeal -(int) (ponderation * (float)biasHeal);
				DownCell->security += i ==0?0:biasSecu - (int)(ponderation * (float)biasSecu);
				DownCell->job += i ==0?0:biasJob - (int)(ponderation * (float)biasJob);	
				maxTemp = maxStat(DownCell, stat);

				if(maxTemp  >= roof && maxTemp > maxdeficit && DownCell->building == NULL)
				{
					maxdeficit = maxTemp;
					*maxStats = *stat;
					deficit = DownCell;
				}
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
			float ponderation = ((float)(n-r/2+i)/(float)((r)));
			UpCell->habitation += biasHab - (int)(ponderation * (float)biasHab);
			UpCell->economy += biasEco - (int)(ponderation * (float)biasEco);
			UpCell->health += biasHeal - (int)(ponderation * (float)biasHeal);
			UpCell->security += biasSecu - (int)(ponderation * (float)biasSecu);
			UpCell->job += biasJob - (int)(ponderation * (float)biasJob);
			maxTemp = maxStat(UpCell, stat);

			if(maxTemp>= roof && maxTemp > maxdeficit && UpCell->building == NULL)
			{
				maxdeficit = maxTemp;
				*maxStats = *stat;
				deficit = UpCell; 
			}


			DownCell->habitation += i == 0?0:biasHab -(int) (ponderation * (float)biasHab);
			DownCell->economy += i == 0?0:biasEco -(int) (ponderation * (float)biasEco);
			DownCell->health += i == 0?0:biasHeal -(int) (ponderation * (float)biasHeal);
			DownCell->security += i ==0?0:biasSecu - (int)(ponderation * (float)biasSecu);
			DownCell->job += i ==0?0:biasJob - (int)(ponderation * (float)biasJob);	
			maxTemp = maxStat(DownCell, stat);

			if(maxTemp  >= roof && maxTemp > maxdeficit && DownCell->building == NULL)
			{
				maxdeficit = maxTemp;
				*maxStats = *stat;
				deficit = DownCell;
			}
		}
		k++;	

	}
	if(compt%50 == 0)
	{
		printMatrix(map);
		analyseMatrix(map);
	}
	//printf("%i maxdeficit, %i stat\n", maxdeficit, *maxStats);
	recUpdate(deficit, map, maxStats, compt, buildingList, nbcompt);

}

int  maxStat(struct cell *cell, int *stat)
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


void recUpdate(struct cell *cell, struct map *map, int *stat, int compt, struct building **buildingList, int nbcompt)
{
	//printMatrixHab(map);
	printf("%i stat to put, %i compt\n",*stat, compt);

	//cell->building = getBat(*stat, buildingList);

	if(*stat == 0)
	{
		cell->building = *(buildingList+1);
		cell->security = 0;
		updateNeeds(cell, map, compt+1, buildingList, nbcompt);
	}
	else if(*stat == 1)
	{
		cell->building = *(buildingList+14);
		cell->job = 0;
		updateNeeds(cell, map, compt+1, buildingList, nbcompt);
	}
	else if(*stat == 2)
	{
		cell->building = *(buildingList+4);
		cell->habitation = 0;
		updateNeeds(cell, map, compt+1, buildingList, nbcompt);
	}
	else if(*stat == 3)
	{
		cell->building = *(buildingList+18);
		cell->economy = 0;
		updateNeeds(cell, map, compt+1, buildingList, nbcompt);		
	}
	else
	{
		cell->building = *(buildingList+2);
		cell->health = 0;
		updateNeeds(cell, map, compt+1, buildingList, nbcompt);
	}
}

struct building *getBat(int stat, struct building **buildingList)
{
	struct building *bat = *buildingList+1;
	while (bat && (bat->type != stat+1 && !bat->placed))
	{
		bat += 1;
	}
	bat->placed = 1;
	return bat;
}
