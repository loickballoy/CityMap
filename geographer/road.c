#include "../assign/assign.h"
#include "err.h"
#include "road.h"
#include <stdio.h>

int updateConnected(struct map *map, int x, int y)
{
  struct cell* tempcell = map->cells + (x + y * map->maxWidth);
  if(x != 0)
    (tempcell-1)->isRoadConnected = 1;
  if(y != 0)
    (tempcell-map->maxWidth)->isRoadConnected = 1;
  if(x != map->maxWidth)
    (tempcell+1)->isRoadConnected = 1;
  if(y != map->maxHeight)
    (tempcell+map->maxWidth)->isRoadConnected = 1;
    return 1;
}

void square(struct map *map, int x, int y, int len, int *a, int *b)
{
  int startx = x < 0 ? 0 : x;
  int starty = y < 0 ? 0 : y;
  struct cell* tempcell = map->cells + (startx + starty * map->maxWidth);
  int endx = x + len > map->maxWidth ? map->maxWidth : x + len;
  int endy = (y + len) > map->maxHeight ? map->maxHeight : (y + len) ;

  for(int i = 0; i <= endx-startx; i++)
  {
    if((tempcell + i)->type == 6)
    {
      *a = i;
      *b = starty;
      tempcell->type = 12;
      return;
    }
    (tempcell + i)->type = 13;
  }
  for(int j = 0; j <= endy-starty; j++)
  {
    if((tempcell + j * map->maxWidth)->type == 6)
    {
      *a = startx;
      *b = j;
      tempcell->type = 12;
      return;
    }
    (tempcell + j * map->maxWidth)->type = 12;
  }


  tempcell = map->cells + (startx + (endy * map->maxWidth));
  for(int i = 0; i <= endx-startx; i++)
  {
    if((tempcell + i)->type == 6)
    {
      *a = i;
      *b = endy;
      tempcell->type = 12;
      return;
    }
    (tempcell+i)->type = 14;
  }

  tempcell = map->cells + (endx + (starty * map->maxWidth));
  for(int j = 0; j <= endy-starty; j++)
  {
    if((tempcell + j * map->maxWidth)->type == 6)
    {
      *a = endx;
      *b = j;
      tempcell->type = 12;
      return;
    }
    (tempcell + j * map->maxWidth)->type = 11;
  }
}

void roadToConnect(struct map *map, int x, int y)
{
  return;
}
