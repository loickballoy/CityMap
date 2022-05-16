#include "../loader/read.h"
#include "../loader/write.h"
#include "need.h"
#include "building.h"
#include <err.h>
#include <stdlib.h>
#include <stdio.h>

int NO = 0;
int YES = 1;

unsigned char NUMBER_TYPE = 7;

int HALL[] = {0/*policy*/, 10/*job*/, 50/*property*/, 0/*shop*/, 0/*Hosto*/, 10/*security*/, 30/*range*/};
int PROPERTY[] = {0, 40, -60, 35, 20, 10, 15};
int OFFICE[] = {0, -60, 50, 10, 0, 0, 10};
int COMISSARY[] = {0, -20, 20, 0, 0, -70, 20};
int SHOP[] = {0, -10, 20, -60, 0, 10, 10};
int HOSPITAL[] = {0, -20, 30, 0, -70, 0, 20};
int SUBWAY[] = {0, 10, 10, 10, 10, 10, 20};


int *initTownList3(unsigned int nb_hab, double sec)
{
  //int comi_range = 60000;
  //int hosp_range = 20000;
  sec +=0;
  int *bat = malloc(sizeof(int)* NUMBER_TYPE);
  int **building_value = load_building_value();
  int *bias = load_building_bias();
  for (int x = 0; x < 7; x++)
  {
	  *(bat + x) = nb_hab / *((*(building_value + x)) + 7);
	  if (x == 6 && *(bat + x) == 1)
		  *(bat + x) = 0;
	  else if (*(bat + x) == 0)
		  *(bat + x) = 1;
  }
  *(bat + 1) += *(bat + 1) * (*(bias + 2)) / 100;
  *(bat + 2) += *(bat + 2) * (*(bias + 1)) / 100;
  *(bat + 3) += *(bat + 3) * (*(bias + 5)) / 100;
  *(bat + 4) += *(bat + 4) * (*(bias + 3)) / 100;
  *(bat + 5) += *(bat + 5) * (*(bias + 4)) / 100;

  return bat;
}
