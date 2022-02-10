#include "need.h"
#include "building.h"
#include <err.h>
#include <stdlib.h>
#include <stdio.h>

unsigned char NUMBER_TYPE = 7;

unsigned int HALL[] = {500, 30, 0, 0, 0, 10, 20};
unsigned int PROPERTY[] = {0, 0, 30, 0, 0, 0, 0};
unsigned int OFFICE[] = {0, 50, 0, 0, 0, 0, 5};
unsigned int COMISSARY[] = {0, 20, 0, 0, 0, 500, 15};
unsigned int SHOP[] = {0, 10, 0, 200, 0, 0, 10};
unsigned int HOSPITAL[] = {0, 20, 0, 0, 300, 0, 20};


unsigned int *select(unsigned char type)
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
	unsigned int *typeArray = select(type);
	struct buildingType *newType = malloc(sizeof(struct buildingType));
	struct building *newBuild = malloc(sizeof(struct building));
	newBuild->type = newType;

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


