#ifndef ASSIGN_H
#define ASSIGN_H

#include "../banker/building.h"

struct cell{
	struct building *building;
	unsigned int security;
	unsigned int job;
	unsigned int habitation;
	unsigned int economy;
	unsigned int health;
	int isRoadConnected;	
};

struct map
{
	struct cell **cells;
	int maxHeight;
	int maxWidth;
};

#endif
