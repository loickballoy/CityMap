#include <stdio.h>
#include <string.h>
#include "read.h"
#include "loadtools.h"

/**
* @file write.c
* @details This file modifies the setting files to allow the modification of biases and rules in general.
* @author Remy Decourcelle <remy.decoutcelle@epita.fr>, Loïck Balloy <loick.balloy@epita.fr>, Axel Cochepin <axel.cochepin@epita.fr>, Guillaume Charvolin <guillaume.charvolin@epita.fr>
* @version 0.1
* @date 2022
*/



void write_habitant_number(int habitant_number)
{
	FILE *file = settings_open();
	char buffer[LINE_BUFFER_SIZE];
	fgets(buffer, LINE_BUFFER_SIZE, file);

	long int ft = 0;
	long int lineS = 0;
	long int temp = 0;
	while(!isHabitant(buffer))
	{
		fgets(buffer, LINE_BUFFER_SIZE, file);
		temp = ftell(file);
		lineS = ft - temp;
		ft = temp;
	}
	fseek(file, lineS, SEEK_CUR);
	char toPrint[LINE_BUFFER_SIZE];
	sprintf(toPrint, "HABITANT_NUMBER = [%i]                   ", habitant_number);
	fprintf(file, "%s", toPrint);
	fclose(file);
}

void write_bias(int *building_bias)
{
	FILE *file = settings_open();
	char buffer[LINE_BUFFER_SIZE];
	fgets(buffer, LINE_BUFFER_SIZE, file);

	long int ft = 0;
	long int lineS = 0;
	long int temp = 0;
	while(!isBias(buffer))
	{
		fgets(buffer, LINE_BUFFER_SIZE, file);
		temp = ftell(file);
		lineS = ft - temp;
		ft = temp;
	}
	fseek(file, lineS, SEEK_CUR);
	char dst[LINE_BUFFER_SIZE];
	char src[LINE_BUFFER_SIZE];
	strcpy(dst, "BIAS = [");
	for (int i = 0; i < BIAS_NUMBER; ++i)
	{
		if (i == BIAS_NUMBER - 1)
			sprintf(src, "%i]                    ", *(building_bias + i));
		else
			sprintf(src, "%i, ", *(building_bias + i));
		strcat(dst, src);
	}
	fprintf(file, "%s", dst);
	fclose(file);
}
