#include <stdio.h>
#include <stdlib.h>
#include <time.h> //use time()
#include <unistd.h> //use sleep()
#include <err.h> //use errx()
#include "assign.h"
#include "assign_tools.h"
#include "../banker/need.h"
#include "../geographer/update.c"
#include "../loader/loadtools.c"
#include "../geographer/road.h"

struct map *minMaxMap(struct map *newMap, struct map *testMap)
{
	int nbbat = 0;

	int stat[NBSTATS] = {0};

	for(int j = 0; j < newMap->maxWidth * newMap->maxHeight; j++)
	{
		struct cell *upTest = newMap->cells + j;
		for(int i = 0; i < NBSTATS; i++)
			stat[i] += upTest->stats[i];
		nbbat++;
	}

	int M_sec = stat[0]/nbbat;
	int M_job = stat[1]/nbbat;
	int M_hab = stat[2]/nbbat;
	int M_eco = stat[3]/nbbat;
	int M_hea = stat[4]/nbbat;
	int moy = (M_sec + M_job + M_hab + M_eco + M_hea)/5;

	nbbat = 0;

	int _stat[NBSTATS] = {0};

	for(int j = 0; j < testMap->maxWidth * testMap->maxHeight; j++)
	{
		struct cell *upTest = testMap->cells + j;
		for(int i = 0; i < NBSTATS; i++)
			_stat[i] += upTest->stats[i];
		nbbat++;
	}

	int _M_sec = _stat[0]/nbbat;
	int _M_job = _stat[1]/nbbat;
	int _M_hab = _stat[2]/nbbat;
	int _M_eco = _stat[3]/nbbat;
	int _M_hea = _stat[4]/nbbat;
	int _moy = (_M_sec + _M_job + _M_hab + _M_eco + _M_hea)/5;

	return (moy < _moy)?testMap:newMap;

}



struct map *initMap(unsigned int maxH, unsigned int maxW)
{
	//!Map Initialisation

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

int fillTown(struct map *map, int *buildingList, int roof, int **building_value)
{

	//!fill the map by placing buildings at free spaces (the most interresting part of our algorithm)

	int *a = malloc(sizeof(int));
	int *b = malloc(sizeof(int));
	*a = 0;
	*b = 12;
	int maxStats = 0;
	struct cell *cell = searchGlobalNeed(map, buildingList, &maxStats,roof, a);
	
	if(*a == 0 && buildingList[1] > 0 && buildingList[2] > 0 && buildingList[4] > 0)//if(there is no vital need) then generate random
	{
		
		cell = generateRandomBuilding(map, buildingList, &maxStats, a, 0);
		if(*a == 0)
			errx(1,"There is no possibility to place a building randomly | assign.c: FillTown()\n");
	}
	else
	{
		cell = searchGlobalNeed(map, buildingList, &maxStats, 0, a);
	}

	if (!cell)
	{
		free(a);
		free(b);
		return -10;
	}
	
	int t;
	int r = buildingList[getValue(maxStats)];
	if(maxStats == 1 && r > 0)
	{
		//cell->building = *(buildingList+14);
		cell->type = 2;//OFFICE
		cell->stats[1] = 0;
		buildingList[getValue(maxStats)] -= 1;
		
		t = 2;	
	}
	else if(maxStats == 2 && r > 0)
	{
		//cell->building  = *(buildingList+4);
		cell->type = 1;//PROPERTY
		cell->stats[2] = 0;
		buildingList[getValue(maxStats)] -= 1;
		
		t = 1;	
	}

	else if(maxStats == 3 && r > 0)
	{
		//cell->building  = *(buildingList+18);
		cell->type = 4;//SHOP
		cell->stats[3] = 0;
		buildingList[getValue(maxStats)] -= 1;
		
		t = 4;
	
	}

	else if(maxStats == 4 && r > 0)
	{
		//cell->building  = *(buildingList+2);
		cell->type = 5;//HOSPITAL
		cell->stats[4]= 0;
		buildingList[getValue(maxStats)] -= 1;
		
		t = 5;
	
	}
	else if (maxStats == 0 && r > 0)
	{
		//cell->building  = *(buildingList+2);
		cell->type = 3;//COMMISSARY
		cell->stats[5]= 0;
		buildingList[getValue(maxStats)] -= 1;
		
		t = 3;	
	}
	else
	{
		errx(1,"Undefined  | assign.c: FillTown()\n");
	}
	int temp = *a;
	*a = temp % map->maxWidth;//setting a value
	*b = temp / map->maxWidth;//setting b value
	updateAround(map, *a, *b, building_value);

	if(!cell->isRoadConnected)//you have to connect it
	{
		roadToConnect(map, *a, *b);
	}
	cleanWay(map);

	//free
	free(a);
	free(b);

	return t;
}

void replaceTown(struct map *map, int *buildingList, int roof, int **building_value, int *nbreplacement)
{

	//Replace some buildings by others to make the town better

	int *a = malloc(sizeof(int));
	int *b = malloc(sizeof(int));
	*a = 0;
	*b = 12;
	int maxStats = 0;
	struct cell *cell = replaceGlobalNeed(map, buildingList, &maxStats,roof, a);
	if(*a == 0)
	{
		free(a);
		free(b);
		return;
	}

	int temp = *a;
	*a = temp % map->maxWidth;//setting a value
	*b = temp / map->maxWidth;//setting b value
	
	reverseUpdateAround(map, *a, *b, building_value);

	buildingList[cell->type] += 1;
	if(maxStats == 1)
	{
		//cell->building = *(buildingList+14);
		cell->type = 2;//OFFICE
		cell->stats[1] = 0;
		buildingList[getValue(maxStats)] -= 1;
	}
	else if(maxStats == 2)
	{
		//cell->building  = *(buildingList+4);
		cell->type = 1;//PROPERTY
		cell->stats[2] = 0;
		buildingList[getValue(maxStats)] -= 1;
	}
	else if(maxStats == 3)
	{
		//cell->building  = *(buildingList+18);
		cell->type = 4;//SHOP
		cell->stats[3] = 0;
		buildingList[getValue(maxStats)] -= 1;
	}
	else if(maxStats == 4)
	{
		//cell->building  = *(buildingList+2);
		cell->type = 5;//HOSPITAL
		cell->stats[4]= 0;
		buildingList[getValue(maxStats)] -= 1;
	}
	else
	{
		//cell->building  = *(buildingList+2);
		cell->type = 3;//COMMISSARY
		cell->stats[5]= 0;
		buildingList[getValue(maxStats)] -= 1;
	}

	*nbreplacement += 1;
	updateAround(map, *a, *b, building_value);

	//free
	free(a);
	free(b);
}



struct cell *replaceGlobalNeed(struct map *map, int *buildingList, int *maxstat,int roof, int *a)
{

	//Research the max need to replace in all the map

	int maxneed = 0.6*(float)roof;
	struct cell *result = NULL;
	*a = 0;
	
	for(int j = 0; j < map->maxWidth * map->maxHeight; j++)
	{
		struct cell *upTest = map->cells + j;
		if(upTest->type > 0 && upTest->type < 6)
		{
			for(int i = 0; i < NBSTATS; i++)
			{
				
				if(upTest->stats[i] > maxneed && buildingList[getValue(i)] != 0)
				{
					if(getType(upTest->type) != i)
					{
						*a = j;
						maxneed = upTest->stats[i];
						*maxstat = i;
						result = upTest;
					}
				}
			}
		}
	}
	return result;
}



struct cell *searchGlobalNeed(struct map *map, int *buildingList, int *maxstat,int roof, int *a)
{

	//Research the max need in all the map only at free place

	int maxneed = roof;
	struct cell *result = NULL;
	*a = 0;
	
	for(int j = 0; j < map->maxWidth * map->maxHeight; j++)
	{
		struct cell *upTest = map->cells + j;
		if(upTest->type == -1)
		{
			for(int i = 0; i < NBSTATS; i++)
			{
				
				if(upTest->stats[i] > maxneed && buildingList[getValue(i)] > 0)//implement un and buildinglist stat == 0
				{
					*a = j;
					maxneed = upTest->stats[i];
					*maxstat = i;
					result = upTest;
				}
			}
		}
		else if (upTest->type > 0 && upTest->type > 6 && upTest->stats[getValue(upTest->type)] > maxneed)
		{
			*a = j;
			maxneed = upTest->stats[upTest->type + 6];
			*maxstat = upTest->type + 6;
			result = upTest;

		}
	}
	
	return result;
}

struct cell *generateRandomBuilding(struct map *map, int *buildingList, int *maxstat, int *a, int nbcompt)
{

	//Generate a building at a free place between the center and RDMRANGE

	int range = RDMRANGE;
	
	*maxstat = rand()%3 +1;
	
	int compt = 0;
	while (buildingList[getValue(*maxstat)] > 0 && compt < 1000)
	{
		*maxstat = rand()%3 +1;
		int rndm = rand();
		srand(rndm + nbcompt+time(0));
		compt += 1;
	}
	
	struct cell *tempcell = map->cells + map->maxWidth/2 + map->maxHeight*(map->maxHeight/2);//center
	srand(time(0)* rand());
	int rdm = rand();
	compt = 0;
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

void subwaySquare(struct map *map, int len, int *a, int *b)
{
  //finds the most optimal space for a new subway

  *a = 0;
  *b = 0;
  int x = map->maxWidth / 2;
  int y = map->maxHeight / 2; 
  
  int startx = x-len/2 < 0 ? 0 : x-len/2;
  int starty = y-len/2 < 0 ? 0 : y-len/2;
  struct cell* tempcell = map->cells + (startx + starty * map->maxWidth);
  int endx = (x + len/2) >= map->maxWidth ? map->maxWidth-1 : x + len/2;
  int endy = (y + len/2) >= map->maxHeight ? map->maxHeight-1 : (y + len/2);


  for(int i = 0; i <= endx-startx; i++)
  {
    
    if((tempcell + i)->stats[1] == 0)
    {
      *a = startx+i;
      *b = starty;
      return;
    }
  }
  for(int j = 0; j <= endy-starty; j++)
  {
    if((tempcell + j * map->maxWidth)->stats[1] == 0)
    {
      *a = startx;
      *b = starty+j;
      return;
    }
  }


  tempcell = map->cells + (startx + (endy * map->maxWidth));
  for(int i = 0; i <= endx-startx; i++)
  {
    if((tempcell + i)->stats[1] == 0)
    {
      *a = startx+i;
      *b = endy;
      return;
    }
  }

  tempcell = map->cells + (endx + (starty * map->maxWidth));
  for(int j = 0; j <= endy-starty; j++)
  {
    if((tempcell + j * map->maxWidth)->stats[1] == 0)
    {
      *a = endx;
      *b = starty+j;
      return;
    }
  }
  return;
}

struct cell **generateRandomSubway(struct map *map, int *buildingList, int **building_value)
{
	//Randomly places Subways on the map
	struct cell **Nodes = calloc(buildingList[6], sizeof(struct cell *));
	struct cell *tmp = NULL;
	int range = RDMRANGE;
	srand(time(0)* rand());	
	int compt = 0;
	int rdm = rand();
	int rdmW = 0;
	int rdmH = 0;
	while(buildingList[6] > buildingList[6] / 2)
	{
		while(compt < 10000)
		{
			tmp = map->cells + map->maxWidth/2 + map->maxHeight*(map->maxHeight/2);
			srand(rdm + time(0));
			rdm = rand();
			rdmW = rdm % (4*range) - 2*range;
			srand(rdm);
			rdmH = rand() % (4*range) - 2*range;
			tmp += rdmW + (map->maxWidth * rdmH);
			if(tmp->type == -1)
				break;
			compt++;
		}
		tmp->type = 7;
		buildingList[6] -= 1;
		*(Nodes + buildingList[6])= tmp;
		updateAround(map, (*(Nodes +buildingList[6]) - map->cells) % map->maxHeight, (*(Nodes +buildingList[6]) - map->cells) / map->maxHeight,building_value);
		
	}
	while (buildingList[6] > 0)
	{
		int a, b = 0;
		int far = 0;
		while(a == 0)//find the nearest free adress
  		{
    			subwaySquare(map, 3+far*2, &a, &b);
    			far++;
  		}
		(map->cells + a + b*map->maxWidth)->type = 7;
		buildingList[6] -= 1;
		updateAround(map, a, b, building_value);
	}
	return Nodes;
}

void generateRdmRoads(struct map *map, int nb_sub, struct cell **Nodes)
{
	//Places the first roads in order to avoid deleting existing buildings
	for(int i = 0; i < nb_sub - 1; i++)
	{
		createWay(map, (*(Nodes +i) - map->cells) % map->maxHeight, (*(Nodes + i) - map->cells)/map->maxHeight, (*(Nodes + i + 1) - map->cells) % map->maxHeight, (*(Nodes +i + 1) - map->cells) / map->maxHeight);
		cleanWay(map);
		
	}
}
