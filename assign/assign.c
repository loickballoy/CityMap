#include <stdio.h>
#include <stdlib.h>
#include <time.h> //use time()
#include <unistd.h> //use sleep()
#include <err.h> //use errx()
#include "assign.h"
#include "../banker/need.h"
#include "../geographer/update.c"

#define COLOR_RED "\x1b[31m"
#define COLOR_BLEU "\x1b[34m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_PURPLE "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_ROAD "\x1b[30m"
#define COLOR_RESET "\x1b[0m"

void analyseMatrix(struct map *newmap)
{

	//make an average of all the needs

	int nbbat = 0;

	int stat[NBSTATS] = {0};

	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		for(int i = 0; i < NBSTATS; i++)
			stat[i] += upTest->stats[i];
		nbbat++;
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

	//print the strongest need of each cells of the matrix

	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		int max = upTest->stats[0];
		int type = 0;
		for(int i = 1; i < NBSTATS; i++)
		{
			if(upTest->stats[i] > max)
			{
				max = upTest->stats[i];
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
					printf(COLOR_BLEU "%i ;" COLOR_RESET, upTest->stats[type]);
				else if(type == 1)
					printf(COLOR_GREEN "%i ;" COLOR_RESET, upTest->stats[type]);
				else if(type == 2)
					printf(COLOR_YELLOW "%i ;" COLOR_RESET, upTest->stats[type]);
				else if(type == 3)
					printf(COLOR_PURPLE "%i ;" COLOR_RESET, upTest->stats[type]);
				else if(type == 4)
					printf(COLOR_CYAN "%i ;" COLOR_RESET, upTest->stats[type]);
				else if(type == 5)
					printf(COLOR_RED "%i ;" COLOR_RESET,upTest->stats[type]);
			}
			if(max / 10 >= 10)
			{
				if(type == 0)
					printf(COLOR_BLEU "%i;" COLOR_RESET, upTest->stats[type]);
				else if(type == 1)
					printf(COLOR_GREEN "%i;" COLOR_RESET, upTest->stats[type]);
				else if(type == 2)
					printf(COLOR_YELLOW "%i;" COLOR_RESET, upTest->stats[type]);
				else if(type == 3)
					printf(COLOR_PURPLE "%i;" COLOR_RESET, upTest->stats[type]);
				else if(type == 4)
					printf(COLOR_CYAN "%i;" COLOR_RESET, upTest->stats[type]);
				else if(type == 5)
					printf(COLOR_RED "%i;" COLOR_RESET,upTest->stats[type]);
			}

		}
		if(j%(newmap->maxWidth) == 0)
			printf("\n");
	}

	printf("\n");
	printf(COLOR_BLEU "MOY SECU = %i\n" COLOR_RESET, 0 );
	printf(COLOR_GREEN "MOY JOB = %i\n" COLOR_RESET, 0);
	printf(COLOR_YELLOW "MOY HAB = %i\n" COLOR_RESET, 0);
	printf(COLOR_PURPLE "MOY ECO = %i\n" COLOR_RESET, 0);
	printf(COLOR_CYAN "MOY HEAL = %i\n" COLOR_RESET, 0);
}

void recAnalyseMatrix(struct map *newmap, int *stat)
{

	//make the sum of each needs

	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		for(int i = 0; i < NBSTATS; ++i)
		{
			*(stat+i) += upTest->stats[i];
		}
	}
}

void printMatrixTime(struct map *newmap)//print la matricd en couleur avec une pose de 1sec a la fin
{

	//print the colored building matrix with a second of stop

	int nbbat = 0;
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		if(upTest->type == -1)
			printf("  ;");
		if(upTest != NULL)
		{
			nbbat++;
			printf("");
			if(upTest->type == 0)
				printf(COLOR_BLEU "%c ;" COLOR_RESET, charType(upTest->type));
			else if(upTest->type == 1)
				printf(COLOR_GREEN "%c ;" COLOR_RESET, charType(upTest->type));
			else if(upTest->type == 2)
				printf(COLOR_YELLOW "%c ;" COLOR_RESET, charType(upTest->type));
			else if(upTest->type == 3)
				printf(COLOR_PURPLE "%c ;" COLOR_RESET, charType(upTest->type));
			else if(upTest->type == 4)
				printf(COLOR_CYAN "%c ;" COLOR_RESET, charType(upTest->type));
			else
				printf(COLOR_RED "%c ;" COLOR_RESET,charType(upTest->type));
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

char charType(int type)//renvoie le symbole associé au type
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
	if(type == 6)
		return 'R';
	errx(EXIT_FAILURE, "charType(): Type undifined");
}


void printMatrix(struct map *newmap)
{

	//print colored building matrix

	int nbbat = 0;
	int nbroad = 0;
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
			if(j%(newmap->maxWidth) == 0)
				printf("\n");
			struct cell *upTest = newmap->cells + j;
			if(upTest->type == -1)
				printf("  ;");
			else
			{
				if(upTest->type != 6)
					nbbat++;
				if(upTest->type == 6)
					nbroad++;
				if(upTest->type == 0)
					printf(COLOR_BLEU "%c ;" COLOR_RESET, charType(upTest->type));
				else if(upTest->type == 1)
					printf(COLOR_GREEN "%c ;" COLOR_RESET, charType(upTest->type));
				else if(upTest->type == 2)
					printf(COLOR_YELLOW "%c ;" COLOR_RESET, charType(upTest->type));
				else if(upTest->type == 3)
					printf(COLOR_PURPLE "%c ;" COLOR_RESET, charType(upTest->type));
				else if(upTest->type == 4)
					printf(COLOR_CYAN "%c ;" COLOR_RESET, charType(upTest->type));
				else if(upTest->type == 5)
					printf(COLOR_RED "%c ;" COLOR_RESET,charType(upTest->type));
				else
					printf(COLOR_ROAD "%c ;" COLOR_RESET,charType(upTest->type));
			}
	}
	printf("\nNBBAT = %i\n", nbbat);
	printf("NBROAD = %i\n", nbroad);
	printf("\n");
}


void printMatrixStat(struct map *newmap, int stat)
{

	//print the stat's natrix

	stringType(stat);
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		if(upTest->stats[stat] == 0)
			printf("%i ;", (upTest->stats[stat]));
		if(upTest->stats[stat] != 0)
		{
			if(upTest->stats[stat] < 0)
				printf(COLOR_RED "%i;" COLOR_RESET,(upTest->stats[stat]));
			else if(upTest->stats[stat] < 10)
				printf(COLOR_RED "%i ;" COLOR_RESET,(upTest->stats[stat]));
			else if(upTest->stats[stat] < 100)
				printf(COLOR_RED "%i;" COLOR_RESET,(upTest->stats[stat]));
			else
				printf(COLOR_RED "%i;" COLOR_RESET,(upTest->stats[stat]));
		}
		if(j%(newmap->maxWidth) == 0)
			printf("\n");
	}
	printf("\n");
}

void stringType(int stat)
{

	//Return the type's string

	if(stat == 0)
	{
		printf("POLITIC :");
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
	if(stat == 5)
	{
		printf("SECURITY :");
		return;
	}
	errx(EXIT_FAILURE,"stringType(): not a type");
}

struct map *initMap(unsigned int maxH, unsigned int maxW)
{
	/*Map Initialisation*/

	struct map *newMap = malloc(sizeof(struct map));
	newMap->maxHeight = maxH;
	newMap->maxWidth = maxW;

	struct cell *cells = malloc(sizeof(struct cell) * maxW * maxH);
	newMap->cells = cells;
	for(int i = 0; i < (int) (maxH*maxW); i++)
	{
		for(int j = 0; j < NBSTATS; j++)
			(cells+i)->stats[j] = 0;

		(cells+i)->type = -1;
	}
	return newMap;
}

void fillTown(struct map *map, struct building **buildingList, int roof, int **building_value)
{

	//fill the map with a building at a free place (the most interresting one)

	int *a = malloc(sizeof(int));
	int *b = malloc(sizeof(int));
	*a = 0;
	*b = 12;
	int maxStats = 0;
	struct cell *cell = searchGlobalNeed(map, &maxStats,roof, a);
	if(*a == 0)//if(there is no vital need) then generate random
	{
		printf("hey random\n ");
		cell = generateRandomBuilding(map, buildingList, &maxStats, a, 0);
		if(*a == 0)
			errx(1,"There is no possibility to place a building randomly | assign.c: FillTown()\n");
	}
	//printf("maxstat = %i || maxstat = %i \n", maxStats, cell->stats[maxStats]);

	if(maxStats == 1)
	{
		//cell->building = *(buildingList+14);
		cell->type = 2;//OFFICE
		cell->stats[1] = 0;
	}
	else if(maxStats == 2)
	{
		//cell->building  = *(buildingList+4);
		cell->type = 1;//PROPERTY
		cell->stats[2] = 0;
	}
	else if(maxStats == 3)
	{
		//cell->building  = *(buildingList+18);
		cell->type = 4;//SHOP
		cell->stats[3] = 0;
	}
	else if(maxStats == 4)
	{
		//cell->building  = *(buildingList+2);
		cell->type = 5;//HOSPITAL
		cell->stats[4]= 0;
	}
	else
	{
		//cell->building  = *(buildingList+2);
		cell->type = 3;//COMMISSARY
		cell->stats[4]= 0;
	}
	int temp = *a;
	*a = temp % map->maxWidth;//set de a
	*b = temp / map->maxWidth;//set de b
	updateAround(map, *a, *b, building_value);
	if(!cell->isRoadConnected)//you have to connect it
	{
		roadToConnect(map, *a, *b);
	}
	cleanWay(map);

	free(a);
	free(b);
}

void replaceTown(struct map *map, struct building **buildingList, int roof, int **building_value, int *nbreplacement)
{

	//Replace some building by others to make the town better

	int *a = malloc(sizeof(int));
	int *b = malloc(sizeof(int));
	*a = 0;
	*b = 12;
	int maxStats = 0;
	struct cell *cell = replaceGlobalNeed(map, &maxStats,roof, a);
	if(*a == 0)//if(there is no vital need) then generate random
	{
		free(a);
		free(b);
		return;
	}

	int temp = *a;
	*a = temp % map->maxWidth;//set de a
	*b = temp / map->maxWidth;//set de b
	reverseUpdateAround(map, *a, *b, building_value);

	if(maxStats == 0)
	{
		cell->building  = *(buildingList+1);
		cell->stats[0] = 0;
	}
	else if(maxStats == 1)
	{
		cell->building  = *(buildingList+14);
		cell->stats[1] = 0;
	}
	else if(maxStats == 2)
	{
		cell->building  = *(buildingList+4);
		cell->stats[2] = 0;
	}
	else if(maxStats == 3)
	{
		cell->building  = *(buildingList+18);
		cell->stats[3] = 0;
	}
	else
	{
		cell->building  = *(buildingList+2);
		cell->stats[4]= 0;
	}
	*nbreplacement += 1;
	updateAround(map, *a, *b, building_value);
	free(a);
	free(b);
}

struct cell *replaceGlobalNeed(struct map *map, int *maxstat,int roof, int *a)
{

	//Research the max need to replace in all the map

	int maxneed = 0.9*(float)roof;
	struct cell *result = NULL;
	*a = 0;
	//result = result + map->maxWidth/2 + map->maxWidth*(map->maxHeight/2);
	for(int j = 0; j < map->maxWidth * map->maxHeight; j++)
	{
		struct cell *upTest = map->cells + j;
		if(upTest->type > 0 && upTest->type < 6 )
		{
			for(int i = 0; i < NBSTATS; i++)
			{
				if(upTest->stats[i] > maxneed)
				{
					*a = j;
					maxneed = upTest->stats[i];
					*maxstat = i;
					result = upTest;
				}
			}
		}
	}
	return result;
}

struct cell *searchGlobalNeed(struct map *map, int *maxstat,int roof, int *a)
{

	//Research the max need in all the map only at free place

	int maxneed = roof;
	struct cell *result = NULL;
	*a = 0;
	//result = map->cells + map->maxWidth/2 + map->maxWidth*(map->maxHeight/2);
	for(int j = 0; j < map->maxWidth * map->maxHeight; j++)
	{
		struct cell *upTest = map->cells + j;
		if(upTest->type == -1)
		{
			for(int i = 0; i < NBSTATS; i++)
			{
				if(upTest->stats[i] > maxneed)
				{
					//printf("search : stats[%i] = %i || maxneed = %i  || a = %i\n", i ,upTest->stats[i],maxneed, *a);
					*a = j;
					maxneed = upTest->stats[i];
					*maxstat = i;
					result = upTest;
				}
			}
		}
	}
	return result;
}

struct cell *generateRandomBuilding(struct map *map, struct building **buildingList, int *maxstat, int *a, int nbcompt)
{

	//Generate a building at a free place between the center and RDMRANGE

	int range = RDMRANGE;
	*maxstat = rand()%3 +1;
	struct cell *tempcell = map->cells + map->maxWidth/2 + map->maxHeight*(map->maxHeight/2);//center
	srand(time(0)* rand());
	int rdm = rand();
	int compt = 0;
	int rdmW = 0;
	int rdmH = 0;
	while(compt < 10000)
	{
		tempcell = map->cells + map->maxWidth/2 + map->maxHeight*(map->maxHeight/2);
		srand(rdm + nbcompt+time(0));
		rdm = rand();
		rdmW = rdm % (2*range) - range;
		srand(rdm);
		rdmH = rand() % (2*range) - range;

		tempcell += rdmW + (map->maxWidth*rdmH);
		if(tempcell->type == -1)
			break;
		compt++;
	}
	*a = tempcell - map->cells ;
	return tempcell;
}

int  maxStat(struct cell *cell, int *stat)//renvoie le type et le nombre du besoin max d'une cell
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

/*
struct building *getBat(int stat, struct building **buildingList)
{
	struct building *bat = *buildingList+1;
	while (bat && (bat->type != stat+1 && !bat->placed))
	{
		bat += 1;
	}
	bat->placed = 1;
	return bat;
}*/

/*
void updateNeeds(struct cell *cell, struct map *map, int compt, struct building **buildingList, int nbcompt, int roof)
{
	//V1 tout le temps en cercle pondéré
	//

	if(compt == nbcompt-1)
	{
		//analyseMatrix_print(map);
		//analyseMatrix(map);
		//printf("hey hey update est fini\n");
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
		bias[i] = cell->values->stats[i];

	int maxTemp = 0;

	unsigned int r = (unsigned int) cell->values->range;

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
			if(maxTemp>= roof && maxTemp > maxdeficit && UpCell == NULL)
			{
				maxdeficit = maxTemp;
				*maxStats = *stat;
				deficit = UpCell;
			}

			maxTemp = maxStat(DownCell, stat);
			if(maxTemp  >= roof && maxTemp > maxdeficit && DownCell == NULL)
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
			if(maxTemp>= roof && maxTemp > maxdeficit &&  UpCell == NULL)
			{
				maxdeficit = maxTemp;
				*maxStats = *stat;
				deficit = UpCell;
			}

			maxTemp = maxStat(DownCell, stat);
			if(maxTemp  >= roof && maxTemp > maxdeficit && DownCell == NULL)
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
				if(maxTemp>= roof && maxTemp > maxdeficit && UpCell == NULL)
				{
					maxdeficit = maxTemp;
					*maxStats = *stat;
					deficit = UpCell;
				}

				maxTemp = maxStat(DownCell, stat);
				if(maxTemp  >= roof && maxTemp > maxdeficit && DownCell == NULL)
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
			if(maxTemp>= roof && maxTemp > maxdeficit && UpCell == NULL)
			{
				maxdeficit = maxTemp;
				*maxStats = *stat;
				deficit = UpCell;
			}

			maxTemp = maxStat(DownCell, stat);
			if(maxTemp  >= roof && maxTemp > maxdeficit && DownCell == NULL)
			{
				maxdeficit = maxTemp;
				*maxStats = *stat;
				deficit = DownCell;
			}
		}
		k++;
	}

	if(compt%10 == 0)
	{
		printMatrixTime(map);
		analyseMatrix(map);
	}

	if(maxdeficit == 0)
	{
		printf("hey search!!\n");
		deficit = searchGlobalNeed(map,maxStats,roof);
		if(deficit == NULL)
		{
			printf("hey random!!\n");
			deficit = generateRandomBuilding(map,buildingList,maxStats, compt);
		}
	}

	recUpdate(deficit, map, maxStats, compt, buildingList, nbcompt, roof);
}
*/
