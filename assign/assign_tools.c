#include <stdio.h>
#include <stdlib.h>
#include <time.h> //use time()
#include <unistd.h> //use sleep()
#include <err.h> //use errx()
#include "assign_tools.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_BLEU "\x1b[34m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_PURPLE "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_ROAD "\x1b[30m"
#define COLOR_RESET "\x1b[0m"

void analyseMatrix(struct map *newmap)
{

	//make an average of all the needs

	int nbbat = 0;

	int stat[NBSTATS] = {0};

	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		for(int i = 0; i < NBSTATS; i++)
			stat[i] += upTest->stats[i];
		nbbat++;
	}
	printf("\n");
	printf(COLOR_BLEU "MOY SECU = %i\n" COLOR_RESET, stat[0]/nbbat);
	printf(COLOR_GREEN "MOY JOB = %i\n" COLOR_RESET, stat[1]/nbbat);
	printf(COLOR_YELLOW "MOY HAB = %i\n" COLOR_RESET, stat[2]/nbbat);
	printf(COLOR_PURPLE "MOY ECO = %i\n" COLOR_RESET, stat[3]/nbbat);
	printf(COLOR_CYAN "MOY HEAL = %i\n" COLOR_RESET, stat[4]/nbbat);
}

void analyseMatrix_print(struct map *newmap)
{

	//print the strongest need of each cells of the matrix

	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		int max = upTest->stats[0];
		int type = 0;
		for(int i = 1; i < NBSTATS; i++)
		{
			if(upTest->stats[i] > max)
			{
				max = upTest->stats[i];
				type = i;
			}
		}
		if(max == 0)
			printf("   ;");
		if(max != 0)
		{
			//printf("");
			if(max / 10 < 10)
			{
				if(type == 0)
					printf(COLOR_BLEU "%i ;" COLOR_RESET, upTest->stats[type]);
				else if(type == 1)
					printf(COLOR_GREEN "%i ;" COLOR_RESET, upTest->stats[type]);
				else if(type == 2)
					printf(COLOR_YELLOW "%i ;" COLOR_RESET, upTest->stats[type]);
				else if(type == 3)
					printf(COLOR_PURPLE "%i ;" COLOR_RESET, upTest->stats[type]);
				else if(type == 4)
					printf(COLOR_CYAN "%i ;" COLOR_RESET, upTest->stats[type]);
				else if(type == 5)
					printf(COLOR_RED "%i ;" COLOR_RESET,upTest->stats[type]);
			}
			if(max / 10 >= 10)
			{
				if(type == 0)
					printf(COLOR_BLEU "%i;" COLOR_RESET, upTest->stats[type]);
				else if(type == 1)
					printf(COLOR_GREEN "%i;" COLOR_RESET, upTest->stats[type]);
				else if(type == 2)
					printf(COLOR_YELLOW "%i;" COLOR_RESET, upTest->stats[type]);
				else if(type == 3)
					printf(COLOR_PURPLE "%i;" COLOR_RESET, upTest->stats[type]);
				else if(type == 4)
					printf(COLOR_CYAN "%i;" COLOR_RESET, upTest->stats[type]);
				else if(type == 5)
					printf(COLOR_RED "%i;" COLOR_RESET,upTest->stats[type]);
			}

		}
		if(j%(newmap->maxWidth) == 0)
			printf("\n");
	}

	printf("\n");
	printf(COLOR_BLEU "MOY SECU = %i\n" COLOR_RESET, 0 );
	printf(COLOR_GREEN "MOY JOB = %i\n" COLOR_RESET, 0);
	printf(COLOR_YELLOW "MOY HAB = %i\n" COLOR_RESET, 0);
	printf(COLOR_PURPLE "MOY ECO = %i\n" COLOR_RESET, 0);
	printf(COLOR_CYAN "MOY HEAL = %i\n" COLOR_RESET, 0);
}


void printMatrixTime(struct map *newmap)//print la matricd en couleur avec une pose de 1sec a la fin
{

	//print the colored building matrix with a second of stop

	int nbbat = 0;
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		if(upTest->type == -1)
			printf("  ;");
		if(upTest != NULL)
		{
			nbbat++;
			//printf("");
			if(upTest->type == 0)
				printf(COLOR_BLEU "%c ;" COLOR_RESET, charType(upTest->type));
			else if(upTest->type == 1)
				printf(COLOR_GREEN "%c ;" COLOR_RESET, charType(upTest->type));
			else if(upTest->type == 2)
				printf(COLOR_YELLOW "%c ;" COLOR_RESET, charType(upTest->type));
			else if(upTest->type == 3)
				printf(COLOR_PURPLE "%c ;" COLOR_RESET, charType(upTest->type));
			else if(upTest->type == 4)
				printf(COLOR_CYAN "%c ;" COLOR_RESET, charType(upTest->type));
			else
				printf(COLOR_RED "%c ;" COLOR_RESET,charType(upTest->type));
		}
		if(j%(newmap->maxWidth) == 0)
		{
			printf("\n");
		}
	}
	printf("NBBAT = %i\n", nbbat);
	printf("\n");
	sleep(1);

}

char charType(int type)//renvoie le symbole associé au type
{
	if(type == 0)
		return 'M';
	if(type == 1)
		return 'P';
	if(type == 2)
		return 'O';
	if(type == 3)
		return 'C';
	if(type == 4)
		return 'S';
	if(type == 5)
		return 'H';
	if(type == 6)
		return 'R';
	errx(EXIT_FAILURE, "charType(): Type undifined");
}


void printMatrix(struct map *newmap)
{

	//print colored building matrix

	int nbbat = 0;
	int nbroad = 0;
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
			if(j%(newmap->maxWidth) == 0)
				printf("\n %i ", j/newmap->maxWidth);
			if(j < 10)
			{
				printf("%i ;",j);
				continue;
			}
			if(j < newmap->maxWidth)
			{
				printf("%i;",j);
				continue;
			}
			struct cell *upTest = newmap->cells + j;
			if(upTest->type == -1)
				printf("  ;");
			else
			{
				if(upTest->type != 6)
					nbbat++;
				if(upTest->type == 6)
					nbroad++;
				if(upTest->type == 0)
					printf(COLOR_BLEU "%c ;" COLOR_RESET, charType(upTest->type));
				else if(upTest->type == 1)
					printf(COLOR_GREEN "%c ;" COLOR_RESET, charType(upTest->type));
				else if(upTest->type == 2)
					printf(COLOR_YELLOW "%c ;" COLOR_RESET, charType(upTest->type));
				else if(upTest->type == 3)
					printf(COLOR_PURPLE "%c ;" COLOR_RESET, charType(upTest->type));
				else if(upTest->type == 4)
					printf(COLOR_CYAN "%c ;" COLOR_RESET, charType(upTest->type));
				else if(upTest->type == 5)
					printf(COLOR_RED "%c ;" COLOR_RESET,charType(upTest->type));
				else
					printf(COLOR_ROAD "%c ;" COLOR_RESET,charType(upTest->type));
			}
	}
	printf("\nNBBAT = %i\n", nbbat);
	printf("NBROAD = %i\n", nbroad);
	printf("\n");
}


void printMatrixStat(struct map *newmap, int stat)
{

	//print the stat's natrix

	stringType(stat);
	for(int j = 0; j < newmap->maxWidth * newmap->maxHeight; j++)
	{
		struct cell *upTest = newmap->cells + j;
		if(upTest->stats[stat] == 0)
			printf("%i ;", (upTest->stats[stat]));
		if(upTest->stats[stat] != 0)
		{
			if(upTest->stats[stat] < 0)
				printf(COLOR_RED "%i;" COLOR_RESET,(upTest->stats[stat]));
			else if(upTest->stats[stat] < 10)
				printf(COLOR_RED "%i ;" COLOR_RESET,(upTest->stats[stat]));
			else if(upTest->stats[stat] < 100)
				printf(COLOR_RED "%i;" COLOR_RESET,(upTest->stats[stat]));
			else
				printf(COLOR_RED "%i;" COLOR_RESET,(upTest->stats[stat]));
		}
		if(j%(newmap->maxWidth) == 0)
			printf("\n");
	}
	printf("\n");
}

void stringType(int stat)
{

	//Return the type's string

	if(stat == 0)
	{
		printf("POLITIC :");
		return;
	}
	if(stat == 1)
	{
		printf("JOB :");
		return;
	}
	if(stat == 2)
	{
		printf("HABITATION :");
		return;
	}
	if(stat == 3)
	{
		printf("ECONOMY :");
		return;
	}
	if(stat == 4)
	{
		printf("HEALTH :");
		return;
	}
	if(stat == 5)
	{
		printf("SECURITY :");
		return;
	}
	errx(EXIT_FAILURE,"stringType(): not a type");
}

int getType(int type)
{
	if (type == 1)
		return 2;
	else if (type == 2)
		return 1;
	else if (type == 3)
		return 5;
	else if (type == 4)
		return 3;
	else
		return 4;
}

int getValue(int i)
{
	if(i == 0)
		return 3;
	else if (i == 1)
		return 2;
	else if (i == 2)
		return 1;
	else if (i == 3)
		return 4;
	else
		return 5;
}

