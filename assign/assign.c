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

	/*printf("moy = %i\n", moy);
	printf("_moy = %i\n", _moy);*/

	return (moy < _moy)?testMap:newMap;

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

int fillTown(struct map *map, int *buildingList, int roof, int **building_value)
{

	//fill the map with a building at a free place (the most interresting one)

	int *a = malloc(sizeof(int));
	int *b = malloc(sizeof(int));
	*a = 0;
	*b = 12;
	int maxStats = 0;
	struct cell *cell = searchGlobalNeed(map, buildingList, &maxStats,roof, a);
	//printf("a = %i", *a);
	if(*a == 0 && buildingList[1] > 0 && buildingList[2] > 0 && buildingList[4] > 0)//if(there is no vital need) then generate random
	{
		printf("hey random\n ");
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
	//printf("maxstat = %i || maxstat = %i \n", maxStats, cell->stats[maxStats]);
	int t;
	int r = buildingList[getValue(maxStats)];
	if(maxStats == 1 && r > 0)
	{
		//cell->building = *(buildingList+14);
		cell->type = 2;//OFFICE
		cell->stats[1] = 0;
		buildingList[getValue(maxStats)] -= 1;
		//printf("rest of offices = %i\n", buildingList[gateValue(maxStats)]);
		t = 2;	
	}
	else if(maxStats == 2 && r > 0)
	{
		//cell->building  = *(buildingList+4);
		cell->type = 1;//PROPERTY
		cell->stats[2] = 0;
		buildingList[getValue(maxStats)] -= 1;
		//printf("rest of property = %i\n", buildingList[gateValue(maxStats)]);
		t = 1;	
	}

	else if(maxStats == 3 && r > 0)
	{
		//cell->building  = *(buildingList+18);
		cell->type = 4;//SHOP
		cell->stats[3] = 0;
		buildingList[getValue(maxStats)] -= 1;
		//printf("rest of shop = %i\n", buildingList[gateValue(maxStats)]);
		t = 4;
	
	}

	else if(maxStats == 4 && r > 0)
	{
		//cell->building  = *(buildingList+2);
		cell->type = 5;//HOSPITAL
		cell->stats[4]= 0;
		buildingList[getValue(maxStats)] -= 1;
		//printf("rest of hospi = %i\n", buildingList[gateValue(maxStats)]);
		t = 5;
	
	}
	else if (maxStats == 0 && r > 0)
	{
		//cell->building  = *(buildingList+2);
		cell->type = 3;//COMMISSARY
		cell->stats[5]= 0;
		buildingList[getValue(maxStats)] -= 1;
		//printf("rest of bavures = %i\n", buildingList[gateValue(maxStats)]);
		t = 3;	
	}
	else
	{
		printf("%i\n sah chelou\n", maxStats);
		//errx(1,"Undefined  | assign.c: FillTown()\n");
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

	//free
	free(a);
	free(b);

	return t;
}

void replaceTown(struct map *map, int *buildingList, int roof, int **building_value, int *nbreplacement)
{

	//Replace some building by others to make the town better

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
	*a = temp % map->maxWidth;//set de a
	*b = temp / map->maxWidth;//set de b
	//printf("replacement colonne : %i || ligne : %i || type : %i || maxstat : %i \n", *a, *b, cell->type,maxStats);
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
		//printf("hey hey nouc comico\n");
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
	//result = result + map->maxWidth/2 + map->maxWidth*(map->maxHeight/2);
	for(int j = 0; j < map->maxWidth * map->maxHeight; j++)
	{
		struct cell *upTest = map->cells + j;
		if(upTest->type > 0 && upTest->type < 6)
		{
			for(int i = 0; i < NBSTATS; i++)
			{
				//printf("%i\n", NBSTATS);
				if(upTest->stats[i] > maxneed && buildingList[getValue(i)] != 0)
				{
					if(getType(upTest->type) != i)//is that really changing ?
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
	//result = map->cells + map->maxWidth/2 + map->maxWidth*(map->maxHeight/2);
	for(int j = 0; j < map->maxWidth * map->maxHeight; j++)
	{
		struct cell *upTest = map->cells + j;
		if(upTest->type == -1)
		{
			for(int i = 0; i < NBSTATS; i++)
			{
				//printf("buildingList[%i] = %u \n" ,i, buildingList[i]);
				if(upTest->stats[i] > maxneed && buildingList[getValue(i)] > 0)//implement un and buildinglist stat == 0
				{
					//printf("buildingList[%i] = %u \n" ,i, buildingList[i]);
					//printf("search : stats[%i] = %i || maxneed = %i  || a = %i\n", i ,upTest->stats[i],maxneed, j);

					//printf("le reste donnée dans searchGlobal = %i, et la stat = %i\n",buildingList[gateValue(i)], i);
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
	//printf(" search a = %i\n\n", *a);
	return result;
}

struct cell *generateRandomBuilding(struct map *map, int *buildingList, int *maxstat, int *a, int nbcompt)
{

	//Generate a building at a free place between the center and RDMRANGE

	int range = RDMRANGE;
	//printf("%i lqlq\n",*maxstat);
	*maxstat = rand()%3 +1;
	//printf("%i lqlq\n",*maxstat);
	int compt = 0;
	while (buildingList[getValue(*maxstat)] > 0 && compt < 1000)
	{
		//printf("list stat : %u \n", buildingList[*maxstat]);
		*maxstat = rand()%3 +1;
		int rndm = rand();
		srand(rndm + nbcompt+time(0));
		compt += 1;
	}
	//printf("dans gen rfm maxStats = %i, alors qu'il reste: %i\n", *maxstat, buildingList[gateValue(*maxstat)]);
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
  *a = 0;
  *b = 0;
  int x = map->maxWidth / 2;
  int y = map->maxHeight / 2; 
  //printf("init : x = %i || y = %i || len = %i \n", x, y, len);
  int startx = x-len/2 < 0 ? 0 : x-len/2;
  int starty = y-len/2 < 0 ? 0 : y-len/2;
  struct cell* tempcell = map->cells + (startx + starty * map->maxWidth);
  int endx = (x + len/2) >= map->maxWidth ? map->maxWidth-1 : x + len/2;
  int endy = (y + len/2) >= map->maxHeight ? map->maxHeight-1 : (y + len/2);


  for(int i = 0; i <= endx-startx; i++)
  {
    //printf("startx = %i  || starty = %i || endx = %i || endy = %i || i = %i\n",startx,starty,endx,endy, i);
    if((tempcell + i)->stats[1] == 0)
    {
      *a = startx+i;
      *b = starty;
      //printf(" hey hey trouver 1\n");
      return;
    }
  }
  for(int j = 0; j <= endy-starty; j++)
  {
    if((tempcell + j * map->maxWidth)->stats[1] == 0)
    {
      *a = startx;
      *b = starty+j;
      //printf(" hey hey trouver 2\n");
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
      //printf(" hey hey trouver 3\n");
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
      //printf(" hey hey trouver 4\n");
      return;
    }
  }
  return;
}

struct cell **generateRandomSubway(struct map *map, int *buildingList, int **building_value)
{
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
		//printf("a subway as been placed");
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
	printf("subway end\n");
	return Nodes;
}

void generateRdmRoads(struct map *map, int nb_sub, struct cell **Nodes)
{
	for(int i = 0; i < nb_sub - 1; i++)
	{
		createWay(map, (*(Nodes +i) - map->cells) % map->maxHeight, (*(Nodes + i) - map->cells)/map->maxHeight, (*(Nodes + i + 1) - map->cells) % map->maxHeight, (*(Nodes +i + 1) - map->cells) / map->maxHeight);
		cleanWay(map);
		printf("GRR\n");
	}
	printf("GRR2\n");
	/*for (int i = 1; i < nb_sub; i++)
	{
		roadToConnect(map, *(Nodes), *(Nodes + i));
		cleanWay(map);
	}*/	
}
