#ifndef BUILDING_H
#define BUILDING_H


struct citizen
{
	unsigned char age;
};
/*
unsigned char NUMBER_TYPE = 7;

unsigned int HALL[NUMBER_TYPE];
unsigned int PROPERTY[NUMBER_TYPE];
unsigned int OFFICE[NUMBER_TYPE];
unsigned int COMISSARY[NUMBER_TYPE];
unsigned int SHOP[NUMBER_TYPE];
unsigned int HOSPITAL[NUMBER_TYPE];
*/
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
