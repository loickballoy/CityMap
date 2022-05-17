#include "../assign/assign_tools.h"
#include "err.h"
#include "road.h"
#include <stdio.h>

int updateConnected(struct map *map, int x, int y)
{
  struct cell* tempcell = map->cells + (x + y * map->maxWidth);
  if(x != 0)
    (tempcell-1)->isRoadConnected += 1;
  if(y != 0)
    (tempcell-map->maxWidth)->isRoadConnected += 1;
  if(x != map->maxWidth)
    (tempcell+1)->isRoadConnected += 1;
  if(y != map->maxHeight)
    (tempcell+map->maxWidth)->isRoadConnected += 1;
  return 1;
}

void square(struct map *map, int x, int y, int len, int *a, int *b)
{
  *a = 0;
  *b = 0;
  
  int startx = x-len/2 < 0 ? 0 : x-len/2;
  int starty = y-len/2 < 0 ? 0 : y-len/2;
  struct cell* tempcell = map->cells + (startx + starty * map->maxWidth);
  int endx = (x + len/2) >= map->maxWidth ? map->maxWidth-1 : x + len/2;
  int endy = (y + len/2) >= map->maxHeight ? map->maxHeight-1 : (y + len/2);


  for(int i = 0; i <= endx-startx; i++)
  {
    
    if((tempcell + i)->type == 6)
    {
      *a = startx+i;
      *b = starty;
      
      return;
    }
  }
  for(int j = 0; j <= endy-starty; j++)
  {
    if((tempcell + j * map->maxWidth)->type == 6)
    {
      *a = startx;
      *b = starty+j;
      
      return;
    }
  }


  tempcell = map->cells + (startx + (endy * map->maxWidth));
  for(int i = 0; i <= endx-startx; i++)
  {
    if((tempcell + i)->type == 6)
    {
      *a = startx+i;
      *b = endy;
      
      return;
    }
  }

  tempcell = map->cells + (endx + (starty * map->maxWidth));
  for(int j = 0; j <= endy-starty; j++)
  {
    if((tempcell + j * map->maxWidth)->type == 6)
    {
      *a = endx;
      *b = starty+j;
      
      return;
    }
  }
  return;
}

void createWay(struct map* map, int x, int y, int a, int b)//x,y = cell from || a,b = cell to
{
  int **building_value = load_building_value();
  struct cell* tempcell = map->cells;
  if(y < b)
  {
    for(int i = b; i != y; i--)
    {
      tempcell = map->cells + a + i*map->maxWidth;
      if (tempcell->type == 7)
	      continue;

      else if(tempcell->type != -1 && tempcell->type != 6 )
      {
        reverseUpdateAround(map, a, i, building_value);
        tempcell->type = 6;
      }
      else
        tempcell->type = 6;
    }
  }
  else
  {
    for(int i = b; y != i; i++)
    {
      tempcell = map->cells + a + i*map->maxWidth;
      if (tempcell->type == 7)
	      continue;

      else if(tempcell->type != -1 && tempcell->type != 6)
      {
        reverseUpdateAround(map, a, i, building_value);
        tempcell->type = 6;
      }
      else
        tempcell->type = 6;
    }
  }
  if(x < a)
  {
    for(int j = a; x != j; j--)
    {
      tempcell = map->cells + j + y*map->maxWidth;
      if (tempcell->type == 7)
	      continue;
     
      else if(tempcell->type != -1 && tempcell->type != 6)
      {
        reverseUpdateAround(map, j, y, building_value);
        tempcell->type = 6;
      }
      else
        tempcell->type = 6;
    }
  }
  else
  {
    for(int j = a; x != j; j++)
    {
      tempcell = map->cells + j + y*map->maxWidth;
      if (tempcell->type == 7)
	      continue;
     
      else if(tempcell->type != -1 && tempcell->type != 6)
      {
        reverseUpdateAround(map, j, y, building_value);
        tempcell->type = 6;
      }
      else
        tempcell->type = 6;
    }
  }
  free_building_list((void **)building_value);
  return;
}

void roadToConnect(struct map *map, int x, int y)
{
  int a = 0;
  int b = 0;
  int far = 0;
  while(a == 0)//find the nearest road to connect
  {
    square(map, x, y, 3+far*2, &a, &b);
    far++;
  }
  createWay(map, x, y, a, b);//place roads need to add the replacement on buildinglist
  return;
}

void cleanWay(struct map *map)
{
  for(int j = 0; j < map->maxWidth * map->maxHeight; j++)
	{
		struct cell *upTest = map->cells + j;
		if(upTest->type == 6)
		{
      if(isGoodWay(map,j % map->maxWidth, j / map->maxWidth) == 0)
      {
        upTest->type = -1;
      }
    }
  }
}


int isGoodWay(struct map *map, int x, int y)
{
  int len = 3;
  int blanc = 0;
  int startx = x-len/2 < 0 ? 0 : x-len/2;
  int starty = y-len/2 < 0 ? 0 : y-len/2;
  struct cell* tempcell = map->cells + (startx + starty * map->maxWidth);
  int endx = (x + len/2) >= map->maxWidth ? map->maxWidth-1 : x + len/2;
  int endy = (y + len/2) >= map->maxHeight ? map->maxHeight-1 : (y + len/2) ;

  for(int i = 0; i <= endx-startx; i++)
  {
    if((tempcell + i)->type == -1)
      blanc += 1;
    if(((tempcell + i)->type != 6 && (tempcell + i)->type != -1 && blanc) || blanc > 1)
    {
      return 1;
    }
  }
  for(int j = 0; j <= endy-starty; j++)
  {
    if((tempcell + j)->type == -1)
      blanc += 1;
    if(((tempcell + j * map->maxWidth)->type != 6 && (tempcell + j * map->maxWidth)->type != -1) || blanc > 1)
    {
      return 1;
    }
  }


  tempcell = map->cells + (startx + (endy * map->maxWidth));
  for(int i = 0; i <= endx-startx; i++)
  {
    if((tempcell + i)->type == -1)
      blanc += 1;
    if(((tempcell + i)->type != 6 && (tempcell + i)->type != -1) || blanc > 1)
    {
      return 1;
    }
  }

  tempcell = map->cells + (endx + (starty * map->maxWidth));
  for(int j = 0; j <= endy-starty; j++)
  {
    if((tempcell + j)->type == -1)
      blanc += 1;
    if(((tempcell + j * map->maxWidth)->type != 6 && (tempcell + j * map->maxWidth)->type != -1) || blanc > 1)
    {
      return 1;
    }
  }
  return 0;
}
