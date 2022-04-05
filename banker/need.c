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

	for(int i = 0; i < NBSTATS; i++)
		newType->stats[i] = *(typeArray+i);

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

struct building *createList(int bat, unsigned int nbBat)
{
  struct building *batList = malloc(nbBat * sizeof(struct building));
  for(unsigned int i = 0;i < nbBat; i++)
    {
      *(batList + i) = *build(bat);
    }
  return batList;
}


struct buildList **initTownList2(unsigned int nb_hab, unsigned int sec)
{
  unsigned int comi_range = 60000;
  unsigned int hosp_range = 20000;
  unsigned int shop_range = 112;

  unsigned int nb_prop;

  nb_prop = nb_hab / PROPERTY[2];
  if(nb_hab % PROPERTY[2] != 0)
    nb_prop += 1;

  unsigned int nb_offi;

  nb_offi = nb_hab / OFFICE[1];
  if(nb_hab % OFFICE[1] != 0)
    nb_offi += 1;

  int nb_comi = nb_hab / (comi_range * sec);

  int nb_hosp = nb_hab / (hosp_range * sec);

  int nb_shop = nb_hab / shop_range;


  struct buildList ha_l;
  struct buildList *hall_list = &ha_l;
  hall_list->batDisp = 1;
  hall_list->batList = createList(0, 1);

  struct buildList pr_l;
  struct buildList *prop_list = &pr_l;
  prop_list->batDisp = nb_prop;
  prop_list->batList = createList(1, nb_prop);

  struct buildList of_l;
  struct buildList *offi_list = &of_l;
  offi_list->batDisp = nb_offi;
  offi_list->batList = createList(2, nb_offi);

  struct buildList co_l;
  struct buildList *comi_list = &co_l;
  comi_list->batDisp = nb_comi;
  comi_list->batList = createList(3, nb_comi);

  struct buildList sh_l;
  struct buildList *shop_list = &sh_l;
  shop_list->batDisp = nb_shop;
  shop_list->batList = createList(4, nb_shop);

  struct buildList ho_l;
  struct buildList *hosp_list = &ho_l;
  hosp_list->batDisp = nb_hosp;
  hosp_list->batList = createList(5, nb_hosp);

  struct buildList **buildingList = malloc(NUMBER_TYPE*sizeof(struct buildList));

  *buildingList = hall_list;
  *(buildingList + 1) = prop_list;
  *(buildingList + 2) = offi_list;
  *(buildingList + 3) = comi_list;
  *(buildingList + 4) = shop_list;
  *(buildingList + 5) = hosp_list;

  return buildingList;
}

/*
struct building **initTownList3(unsigned int nb_hab, unsigned int sec)
{
  unsigned int comi_range = 60000;
  unsigned int hosp_range = 20000;
  unsigned int shop_range = 112;

  unsigned int nb_prop;

  nb_prop = nb_hab / PROPERTY[2];
  if(nb_hab % PROPERTY[2] != 0)
    nb_prop += 1;

  unsigned int nb_offi;

  nb_offi = nb_hab / OFFICE[1];
  if(nb_hab % OFFICE[1] != 0)
    nb_offi += 1;

  unsigned int nb_comi = nb_hab / (comi_range * sec);

  unsigned int nb_shop = nb_hab / shop_range;

  unsigned int nb_hosp = nb_hab / (hosp_range * sec);

  unsigned int bat[NUMBER_TYPE];
  bat[0] = 1;
  bat[1] = nb_prop;
  bat[2] = nb_offi;
  bat[3] = nb_comi;
  bat[4] = nb_shop;
  bat[5] = nb_hosp;

  struct building **FinalList;

  FinalList = malloc(sizeof(struct building ) * NUMBER_TYPE);

  for(unsigned int k = 0; k < NUMBER_TYPE; k++)
    FinalList[k] = malloc(sizeof(struct building ) * bat[k]);

  for(unsigned int i = 0; i < NUMBER_TYPE; i++)
    {
      printf("Number build %u : %u\n",i, bat[i]);
      for(unsigned int j = 0; j < bat[i]; j++)
	{
	  if(j == bat[i]-1)
	    printf("Last build : %u\n\n", j);
	  FinalList[i][j] = *build(i);
	}
    }
  return FinalList;
}
*/

unsigned int *initTownList3(unsigned int nb_hab, double sec)
{
  unsigned int comi_range = 60000;
  unsigned int hosp_range = 20000;
  unsigned int shop_range = 112;

  unsigned int nb_prop;

  nb_prop = nb_hab / 50;
  if(nb_hab % PROPERTY[2] != 0)
    nb_prop += 1;

  unsigned int nb_offi;

  nb_offi = nb_hab / 50;
  if(nb_hab % OFFICE[1] != 0)
    nb_offi += 1;

  unsigned int nb_comi = nb_hab / 20;

  unsigned int nb_shop = nb_hab / shop_range;

  unsigned int nb_hosp = nb_hab / 50;

  unsigned int *bat = malloc(sizeof(unsigned int)* NUMBER_TYPE);
  bat[0] = 1;
  bat[1] = nb_prop;
  bat[2] = nb_offi;
  bat[3] = nb_comi;
  bat[4] = nb_shop;
  bat[5] = nb_hosp;

  return bat;
}
