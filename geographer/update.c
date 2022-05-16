#include "../assign/assign_tools.h"
#include "err.h"
#include "update.h"
#include <stdio.h>

extern struct map;

int ponderation(int x, int y, int val, int a, int b)
{
    int xtemp =  x - a;
    int ytemp = y - b;
    xtemp = xtemp < 0?(-1)*xtemp:xtemp;
    ytemp = ytemp < 0?(-1)*ytemp:ytemp;
    if(xtemp+ytemp == 0)
      return 0;

    float pond = ((float)1/((float)(0.85+(float)xtemp/4+(float)ytemp/4)));//modulable par changement du 0.85 et des /4

    int ponderation = (int)(pond*(float)val);

    /*if(val < 0)//test if habitation
      printf("x : %i  , y : %i  , xtemp : %i  , ytemp : %i  , return : %i \n",x,y,xtemp,ytemp,ponderation);*/
    return ponderation;
}

void attribuate(int x, int y, struct cell *cell, int *value, int a, int b)
{
    int *stats = cell->stats;
    for (int i = 0; i < NBSTATS; i++)
        *(stats + i) += ponderation(x, y, *(value + i), a, b);
}

void reverseAttribuate(int x, int y, struct cell *cell, int *value, int a, int b)
{
    int *stats = cell->stats;
    for (int i = 0; i < NBSTATS; i++)
        *(stats + i) -= ponderation(x, y, *(value + i), a, b);
}

char equation(int x, int y, int a, int b, int range)
{
    return (x - a)*(x - a) + (y - b) * (y - b) < range * range;
}

void updateAround(struct map *map, int a, int b, int **building_value)
{
    struct cell *cell = (map->cells) + (a + b * map->maxWidth);

    if (cell->type == -1)
        errx(1, "updateAround : Error the cell is not occupied by a building at %i, %i \n ",a,b);

    int type = cell->type;
    int *value = *(building_value + type);
    int range = *(value + 6);
    int xsquare = a - range;
    int ysquare = b - range;
    int diam = range * 2;

    struct cell *cellatt;

    for (int x = xsquare; x < (xsquare + diam); ++x)
        if (x >= 0 && x < map->maxWidth)
            for (int y = ysquare; y < (ysquare + diam); ++y)
                if (y >= 0 && y < map->maxHeight)
                    if (equation(x, y, a, b, range))
                        {
                            cellatt = (map->cells) + (x + y * map->maxWidth);
                            attribuate(x, y, cellatt, value, a, b);
                        }
}

void reverseUpdateAround(struct map *map, int a, int b, int **building_value)
{
    struct cell *cell = (map->cells) + (a + b * map->maxWidth);

    if (cell->type == -1)
        errx(1, "reverseUpdateAround : Error the cell is not occupied by a building");
    if (cell->type == 7)
	    return;

    int type = cell->type;
    int *value = *(building_value + type);
    int range = *(value + 6);
    int xsquare = a - range;
    int ysquare = b - range;
    int diam = range * 2;

    struct cell *cellatt;

    for (int x = xsquare; x < (xsquare + diam); ++x)
        if (x >= 0 && x < map->maxWidth)
            for (int y = ysquare; y < (ysquare + diam); ++y)
                if (y >= 0 && y < map->maxHeight)
                    if (equation(x, y, a, b, range))
                        {
                            cellatt = (map->cells) + (x + y * map->maxWidth);
                            reverseAttribuate(x, y, cellatt, value, a, b);
                        }
}
