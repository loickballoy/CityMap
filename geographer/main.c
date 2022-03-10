#include "road.h"
#include "eval.h"
#include "update.h"
#include <stdlib.h>
#include <stdio.h>
#include "../banker/need.c"
#include "../assign/assign.c"
#include "../banker/building.h"
#include "../loader/read.c"

int main(void)
{
    int maxH = 60;
    int maxW = 60;
    struct map *newMap = malloc(sizeof(struct map));
    int **building_value = load_building_value();
	newMap->maxHeight = maxH;
	newMap->maxWidth = maxW;

	struct cell *cells = malloc(sizeof(struct cell) * maxW * maxH);
	newMap->cells = cells;
	for(int i = 0; i < (int) (maxH*maxW); i++)
	{
		for(int j = 0; j < NBSTATS; j++)
			(cells+i)->stats[j] = 0;

		(cells+i)->building = NULL;
	}

    (cells + 30 + 30 * newMap->maxWidth)->building = build(0);

    updateAround(newMap, 30, 30, building_value);

    printMatrixStat(newMap, 1);

    return 0;
}
