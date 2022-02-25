#include <stdio.h>
#include <stdlib.h>
#include <time.h> //use time()
#include <unistd.h> //use sleep()
#include <err.h> //use errx()
#include "assign.h"
#include "../banker/need.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_BLEU "\x1b[34m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_PURPLE "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"

void analyseMatrix(struct map *newmap)
{
	int nbbat = 0;

	int stat[NBSTATS] = {0};

	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *uptest = newmap->cells + j;
		if(uptest->building != NULL)
		{
			for(int i = 0; i < NBSTATS; i++)
				stat[i] += uptest->stats[i];

			nbbat++;
		}
	}
	printf("\n");
	printf(COLOR_BLEU "MOY SECU = %i\n" COLOR_RESET, stat[0]/nbbat);
	printf(COLOR_GREEN "MOY JOB = %i\n" COLOR_RESET, stat[1]/nbbat);
	printf(COLOR_YELLOW "MOY HAB = %i\n" COLOR_RESET, stat[2]/nbbat);
	printf(COLOR_PURPLE "MOY ECO = %i\n" COLOR_RESET, stat[3]/nbbat);
	printf(COLOR_CYAN "MOY HEAL = %i\n" COLOR_RESET, stat[4]/nbbat);
}

void analyseMatrix_print(struct map *newmap)
{
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *uptest = newmap->cells + j;		
		int max = uptest->stats[0];
		int type = 0;
		for(int i = 1; i < NBSTATS; i++)
		{
			if(uptest->stats[i] > max)
			{
				max = uptest->stats[i];
				type = i;
			}
		}
		if(max == 0)
			printf("   ;");
		if(max != 0)
		{
			printf("");
			if(max / 10 < 10)
			{
				if(type == 0)
					printf(COLOR_BLEU "%i ;" COLOR_RESET, uptest->stats[type]);
				else if(type == 1)
					printf(COLOR_GREEN "%i ;" COLOR_RESET, uptest->stats[type]);
				else if(type == 2)
					printf(COLOR_YELLOW "%i ;" COLOR_RESET, uptest->stats[type]);
				else if(type == 3)
					printf(COLOR_PURPLE "%i ;" COLOR_RESET, uptest->stats[type]);
				else if(type == 4)
					printf(COLOR_CYAN "%i ;" COLOR_RESET, uptest->stats[type]);
				else if(type == 5)
					printf(COLOR_RED "%i ;" COLOR_RESET,uptest->stats[type]);
			}
			if(max / 10 >= 10)
			{
				if(type == 0)
					printf(COLOR_BLEU "%i;" COLOR_RESET, uptest->stats[type]);
				else if(type == 1)
					printf(COLOR_GREEN "%i;" COLOR_RESET, uptest->stats[type]);
				else if(type == 2)
					printf(COLOR_YELLOW "%i;" COLOR_RESET, uptest->stats[type]);
				else if(type == 3)
					printf(COLOR_PURPLE "%i;" COLOR_RESET, uptest->stats[type]);
				else if(type == 4)
					printf(COLOR_CYAN "%i;" COLOR_RESET, uptest->stats[type]);
				else if(type == 5)
					printf(COLOR_RED "%i;" COLOR_RESET,uptest->stats[type]);
			}

		}
		if(j%(newmap->maxWidth) == 0)
			printf("\n");
	}
}

void recAnalyseMatrix(struct map *newmap, int *stat)
{
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *uptest = newmap->cells + j;
		if(uptest->building != NULL)
		{
			//printf("hey hey recanalyse !!\n");
			//printf("%i\n",*stat);
			for(int i = 0; i < NBSTATS; ++i)
			{
				*(stat+i) += uptest->stats[i];
				//printf("%i ||\n",*(stat+i));
			}
		}
	}
}

void printMatrixTime(struct map *newmap)
{
	int nbbat = 0;
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		if(upTest->building == NULL)
			printf("  ;");
		if(upTest->building != NULL)
		{
			nbbat++;
			printf("");
			if(upTest->building->type == 0)
				printf(COLOR_BLEU "%c ;" COLOR_RESET, charType(upTest->building->type));
			else if(upTest->building->type == 1)
				printf(COLOR_GREEN "%c ;" COLOR_RESET, charType(upTest->building->type));
			else if(upTest->building->type == 2)
				printf(COLOR_YELLOW "%c ;" COLOR_RESET, charType(upTest->building->type));
			else if(upTest->building->type == 3)
				printf(COLOR_PURPLE "%c ;" COLOR_RESET, charType(upTest->building->type));
			else if(upTest->building->type == 4)
				printf(COLOR_CYAN "%c ;" COLOR_RESET, charType(upTest->building->type));
			else
				printf(COLOR_RED "%c ;" COLOR_RESET,charType(upTest->building->type)); 
		}
		if(j%(newmap->maxWidth) == 0)
		{
			printf("\n");
		}
	}
	printf("NBBAT = %i\n", nbbat);
	printf("\n");
	sleep(1);
	
}

char charType(int type)
{
	if(type == 0)
		return 'M';
	if(type == 1)
		return 'P';
	if(type == 2)
		return 'O';
	if(type == 3)
		return 'C';
	if(type == 4)
		return 'S';
	if(type == 5)
		return 'H';
	errx(EXIT_FAILURE, "charType(): Type undifined");
}


void printMatrix(struct map *newmap)
{
	int nbbat = 0;
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		if(upTest->building == NULL)
			printf("  ;");
		if(upTest->building != NULL)
		{
			nbbat++;
			printf("");
			if(upTest->building->type == 0)
				printf(COLOR_BLEU "%c ;" COLOR_RESET, charType(upTest->building->type));
			else if(upTest->building->type == 1)
				printf(COLOR_GREEN "%c ;" COLOR_RESET, charType(upTest->building->type));
			else if(upTest->building->type == 2)
				printf(COLOR_YELLOW "%c ;" COLOR_RESET, charType(upTest->building->type));
			else if(upTest->building->type == 3)
				printf(COLOR_PURPLE "%c ;" COLOR_RESET, charType(upTest->building->type));
			else if(upTest->building->type == 4)
				printf(COLOR_CYAN "%c ;" COLOR_RESET, charType(upTest->building->type));
			else
				printf(COLOR_RED "%c ;" COLOR_RESET,charType(upTest->building->type)); 
		}
		if(j%(newmap->maxWidth) == 0){
			printf("\n");
		}
	}
	printf("NBBAT = %i\n", nbbat);
	printf("\n");
}

void printMatrixStat(struct map *newmap, int stat)
{
	stringType(stat);
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		if(upTest->stats[stat] == 0)
			printf("%i  ;", (upTest->stats[stat]));
		if(upTest->stats[stat] != 0)
			printf(COLOR_RED "%i ;" COLOR_RESET,(upTest->stats[stat])); 
		if(j%(newmap->maxWidth) == 0)
			printf("\n");
	}
	printf("\n");
}

void stringType(int stat)
{
	if(stat == 0)
	{
		printf("SECURITY :");
		return;
	}
	if(stat == 1)
	{
		printf("JOB :");
		return;
	}
	if(stat == 2)
	{
		printf("HABITATION :");
		return;
	}
	if(stat == 3)
	{
		printf("ECONOMY :");
		return;
	}
	if(stat == 4)
	{
		printf("HEALTH :");
		return;
	}
	errx(EXIT_FAILURE,"stringType(): not a type");
}

struct map *initMap(unsigned int maxH, unsigned int maxW, struct building **buildingList, int compt, int roof)
{
	struct map *newMap = malloc(sizeof(struct map));
	newMap->maxHeight = maxH;
	newMap->maxWidth = maxW;

	printf("%p map pointeur \n",newMap);

	struct cell *cells = malloc(sizeof(struct cell) * maxW * maxH);
	newMap->cells = cells;
	for(int i = 0; i < (int) (maxH*maxW); i++)
	{
		for(int j = 0; j < NBSTATS; j++)
			(cells+i)->stats[j] = 0;

		(cells+i)->building = NULL;
	}

	struct cell *Fcell = newMap->cells;
	struct cell *center = Fcell + maxW/2 + maxW*(maxH/2);

	struct building *Hall = *buildingList;
	center->building = Hall;

	//printf("%i habitation stat \n", Hall->values->habitation);

	Hall->x = maxW/2;
	Hall->y = maxH/2;

	updateNeeds(center, newMap, 0, buildingList, compt, roof);

	printf("hey hey iniMap works\n");
	return newMap;
}

void rec_initMap(struct map *newMap, unsigned int maxH, unsigned int maxW, struct building **buildingList, int compt, int roof)
{
	newMap->maxHeight = maxH;
	newMap->maxWidth = maxW;

	for(int i = 0; i < (int) (maxH*maxW); i++)
	{
		for(int j = 0; j < NBSTATS; j++)
			((newMap->cells)+i)->stats[j] = 0;

		((newMap->cells)+i)->building = NULL;
	}

	struct cell *Fcell = newMap->cells;
	struct cell *center = Fcell + maxW/2 + maxW*(maxH/2);

	struct building *Hall = *buildingList;
	center->building = Hall;

	//printf("%i habitation stat \n", Hall->values->habitation);

	Hall->x = maxW/2;
	Hall->y = maxH/2;

	updateNeeds(center, newMap, 0, buildingList, compt, roof);
}





void updateNeeds(struct cell *cell, struct map *map, int compt, struct building **buildingList, int nbcompt, int roof)
{
	//V1 tout le temps en cercle pondéré
	//
	
	if(compt == nbcompt-1)
	{
		analyseMatrix_print(map);
		analyseMatrix(map);
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

	int bias[NBSTATS];
	for(int i = 0; i < NBSTATS; i++)
		bias[i] = cell->building->values->stats[i];

	int maxTemp = 0;

	unsigned int r = (unsigned int) cell->building->values->range; 
	
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

			for(int j = 0; j < NBSTATS; j++)
				UpCell->stats[j] += (int)(ponderation * (float)bias[j]);

			for(int j = 0; j < NBSTATS; j++)
				DownCell->stats[j] += i == 0?0:bias[j] - (int)(ponderation * (float)bias[j]);

			maxTemp = maxStat(UpCell, stat);
			if(maxTemp>= roof && maxTemp > maxdeficit && UpCell->building == NULL)
			{
				maxdeficit = maxTemp;
				*maxStats = *stat;
				deficit = UpCell; 
			}
		
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

			for(int j = 0; j < NBSTATS; j++)
				UpCell->stats[j] += (int)(ponderation * (float)bias[j]);

			for(int j = 0; j < NBSTATS; j++)
				DownCell->stats[j] += i == 0?0:bias[j] - (int)(ponderation * (float)bias[j]);

			maxTemp = maxStat(UpCell, stat);
			if(maxTemp>= roof && maxTemp > maxdeficit &&  UpCell->building == NULL)
			{
				maxdeficit = maxTemp;
				*maxStats = *stat;
				deficit = UpCell; 
			}

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

				for(int j = 0; j < NBSTATS; j++)
					UpCell->stats[j] += (int)(ponderation * (float)bias[j]);

				for(int j = 0; j < NBSTATS; j++)
					DownCell->stats[j] += i == 0?0:bias[j] - (int)(ponderation * (float)bias[j]);

				maxTemp = maxStat(UpCell, stat);
				if(maxTemp>= roof && maxTemp > maxdeficit && UpCell->building == NULL)
				{
					maxdeficit = maxTemp;
					*maxStats = *stat;
					deficit = UpCell; 
				}

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

			for(int j = 0; j < NBSTATS; j++)
				UpCell->stats[j] += (int)(ponderation * (float)bias[j]);

			for(int j = 0; j < NBSTATS; j++)
				DownCell->stats[j] += i == 0?0:bias[j] - (int)(ponderation * (float)bias[j]);

			maxTemp = maxStat(UpCell, stat);
			if(maxTemp>= roof && maxTemp > maxdeficit && UpCell->building == NULL)
			{
				maxdeficit = maxTemp;
				*maxStats = *stat;
				deficit = UpCell; 
			}

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

	/*if(compt%10 == 0)
	{
		printMatrixTime(map);
		analyseMatrix(map);
	}*/

	if(maxdeficit == 0)
	{
		//printf("hey random!!\n");
		deficit = generateRandomBuilding(map,buildingList,maxStats, compt);
	}

	recUpdate(deficit, map, maxStats, compt, buildingList, nbcompt, roof);
}

struct cell *generateRandomBuilding(struct map *map, struct building **buildingList, int *maxstat, int nbcompt)
{
	int range = RDMRANGE + nbcompt/(5+(nbcompt/3));
	//printf("compt :: %i range :: %i \n", nbcompt, range);
	//printf("compt :: %i ||\n ", nbcompt);

	*maxstat = rand() % 6;	
	//printf("max stat = %i \n", *maxstat);

	struct cell *tempcell = map->cells;
	srand(time(0)* rand());
	int rdm = rand();
	while(1)
	{
		srand(rdm + nbcompt+time(0));
		rdm = rand();
		int rdmW = rdm % (2*range) - range;
		srand(rdm);
		int rdmH = rand() % (2*range) - range;
		//printf("%i rdmW, %i rdmH\n", rdmW, rdmH);

		tempcell = map->cells + map->maxWidth/2 + map->maxHeight*(map->maxHeight/2)+rdmW+ (map->maxWidth*rdmH);
		if(tempcell->building == NULL)
			break;
	}
	return tempcell;
}

int  maxStat(struct cell *cell, int *stat)
{
	int max = cell->stats[0];
	*stat = 0;
	for(int i = 1; i < NBSTATS; i++)
	{
		if(cell->stats[i] > max)
		{
			max = cell->stats[i];
			*stat = i;
		}
	}

	return max;
}

void recUpdate(struct cell *cell, struct map *map, int *stat, int compt, struct building **buildingList, int nbcompt, int roof)
{
	//printf("%i stat to put, %i compt\n",*stat, compt);
	//cell->building = getBat(*stat, buildingList);

	if(*stat == 0)
	{
		cell->building = *(buildingList+1);
		cell->stats[0] = 0;
		updateNeeds(cell, map, compt+1, buildingList, nbcompt, roof);
	}
	else if(*stat == 1)
	{
		cell->building = *(buildingList+14);
		cell->stats[1] = 0;
		updateNeeds(cell, map, compt+1, buildingList, nbcompt, roof);
	}
	else if(*stat == 2)
	{
		cell->building = *(buildingList+4);
		cell->stats[2] = 0;
		updateNeeds(cell, map, compt+1, buildingList, nbcompt, roof);
	}
	else if(*stat == 3)
	{
		cell->building = *(buildingList+18);
		cell->stats[3] = 0;
		updateNeeds(cell, map, compt+1, buildingList, nbcompt, roof);		
	}
	else
	{
		cell->building = *(buildingList+2);
		cell->stats[4]= 0;
		updateNeeds(cell, map, compt+1, buildingList, nbcompt, roof);
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
