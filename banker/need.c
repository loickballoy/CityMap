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
  int shop_range = 112;
  sec += 0;
  int nb_prop;

  nb_prop = nb_hab / 50;
  if(nb_hab % PROPERTY[2] != 0)
    nb_prop += 1;

  int nb_offi;

  nb_offi = nb_hab / 50;
  if(nb_hab % OFFICE[1] != 0)
    nb_offi += 1;

  int nb_comi = nb_hab / 20;

  int nb_shop = nb_hab / shop_range;

  int nb_hosp = nb_hab / 50;

  int nb_sub = nb_hab / 500;

  int *bat = malloc(sizeof(int)* NUMBER_TYPE);
  bat[0] = 1;
  bat[1] = nb_prop;
  bat[2] = nb_offi;
  bat[3] = nb_comi;
  bat[4] = nb_shop;
  bat[5] = nb_hosp;
  bat[6] = nb_sub;

  return bat;
}
