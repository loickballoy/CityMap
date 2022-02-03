#include "building.h"
#include <err.h>

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
