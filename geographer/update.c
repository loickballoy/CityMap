#include "../assign/assign.h"
#include "err.h"
#include "update.h"
#include <stdio.h>

int ponderation(int x, int y, int val)
{
    return 1;
}

void attribuate(int x, int y, struct cell *cell, int *value)
{
    int *stats = cell->stats;
    for (int i = 0; i < NBSTATS; i++)
        *(stats + i) += ponderation(x, y, *(value + i));
}

char equation(int x, int y, int a, int b, int range)
{
    printf("equation\n");
    return (x - a)*(x - a) + (y - b) * (y - b) < range * range;
}

void updateAround(struct map *map, int a, int b, int **building_value)
{
    struct cell *cell = (map->cells) + (a + b * map->maxWidth);

    if (!(cell->building))
        errx(1, "updateAround : Error the cell is not occupied by a building");

    int type = cell->building->type;
    int *value = *(building_value + type);
    int range = *(value + 6);
    int xsquare = a - range;
    int ysquare = b - range;
    int diam = range * 2;

    printf("xsquare = %i\n", xsquare);

    struct cell *cellatt;

    for (int x = xsquare; x < (xsquare + diam); ++x)
        if (x >= 0 && x < map->maxWidth)
            for (int y = ysquare; y < (ysquare + diam); ++y)
                if (y >= 0 && y < map->maxHeight)
                    if (equation(x, y, a, b, range))
                        {
                            cellatt = (map->cells) + (x + y * map->maxWidth);
                            attribuate(x, y, cellatt, value);
                            printf("heyheyuhzeuzheuizyheuzhezuhez\n");
                        }
}
