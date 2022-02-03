#ifndef BUILDING_H
#define BUILDING_H

struct citizen
{
	unsigned char age;
};

unsigned char NUMBER_TYPE = 7;

unsigned int HALL[] = {500, 30, 0, 0, 0, 0, 20};
unsigned int PROPERTY[] = {0, 0, 30, 0, 0, 0, 0};
unsigned int OFFICE[] = {0, 50, 0, 0, 0, 0, 5};
unsigned int COMISSARY[] = {0, 20, 0, 0, 0, 500, 15};
unsigned int SHOP[] = {0, 10, 0, 200, 0, 0, 10};
unsigned int HOSPITAL[] = {0, 20, 0, 0, 300, 0, 20};

struct buildingType
{
	unsigned int policy;
	unsigned int job;
	unsigned int habitation;
	unsigned int economy;
	unsigned int health;
	unsigned int security;
	unsigned char range;
	unsigned int *location;
};

struct building
{
	struct buildingType *type;
	unsigned int x;
	unsigned int y;
};


#endif
