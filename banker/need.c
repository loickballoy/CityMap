#include "need.h"
#include "building.h"
#include <err.h>
#include <stdlib.h>
#include <stdio.h>

int NO = 0;
int YES = 1;

unsigned char NUMBER_TYPE = 7;

int HALL[] = {0, 10, 50, 0, 0, 10, 30};
int PROPERTY[] = {0, 50, -50, 40, 40, -35, 15};
int OFFICE[] = {0, -50, 50, 0, 0, 0, 10};
int COMISSARY[] = {0, -20, 30, 0, 0, 50, 20};
int SHOP[] = {0, 0, 20, -50, 0, 20, 10};
int HOSPITAL[] = {0, 20, 30, 0, -50, 0, 20};


int *select(unsigned char type)
{
	if(type == 0)
		return HALL;
	if(type == 1)
		return PROPERTY;
	if(type == 2)
		return OFFICE;
	if(type == 3)
		return COMISSARY;
	if(type == 4)
		return SHOP;
	if(type == 5)
		return HOSPITAL;
	errx(1, "select(); Type undefined");
}

struct building *build(unsigned char type)
{
	int *typeArray = select(type);
	struct buildingType *newType = malloc(sizeof(struct buildingType));
	struct building *newBuild = malloc(sizeof(struct building));
	newBuild->values = newType;
	newBuild->placed = NO;
	newBuild->type = (int) type;

	newType->policy = *typeArray;
	newType->job = *(typeArray + 1);
	newType->habitation = *(typeArray + 2);
	newType->economy = *(typeArray + 3);
	newType->health = *(typeArray + 4);
	newType->security = *(typeArray + 5);
	newType->range = *(typeArray + 6);

	newType->location = NULL;

	return newBuild;
	
}

struct building **initTownList()
{
	struct building **buildingList = malloc(20*sizeof(struct building)); 
	*buildingList = build(0);
	*(buildingList + 1) = build(3);
	*(buildingList + 2) = build (5);
	int i = 3;
	for(; i < 13; i++)
	{
		*(buildingList+i) = build(1);
	}
	for(; i < 18; i++)
	{
		*(buildingList+i) = build(2);
	}
	for(; i < 21; i++)
	{
		*(buildingList+i)= build(4);
	}
	return buildingList;
}


