#include "loadtools.h"
#include <stdlib.h>
#include <stdio.h>

// HALL PROPERTY OFFICE COMISSARY SHOP HOSPITAL //
int BUILDING_NUMBER_TYPE = 6;

// POLICY JOB HABITATION ECONOMY HEALTH SECURITY RANGE HABITANT_FOR//
int VALUE_NUMBER_TYPE = 8;
// POLICY JOB HABITATION ECONOMY HEALTH SECURITY //
int BIAS_NUMBER = 6;

int BUFFER_SIZE = 32;
int LINE_BUFFER_SIZE = 256;
int LABEL_SIZE = 3;

char SETTINGS[] = "settings";

FILE *settings_open()
{
    FILE *file = fopen(SETTINGS, "r+");
    if (file == NULL)
    {   
        perror("Error in settings_open_write() in load");
        exit(1);
    }
    return file;
}

void print_value(int **building_value)
{
    for (int i = 0; i < BUILDING_NUMBER_TYPE; ++i)
    {
        printf("building %i = [", i);
        for (int j = 0; j < VALUE_NUMBER_TYPE; ++j)
        {
            if (j == VALUE_NUMBER_TYPE - 1)
                printf("%i", *(j + *(building_value + i)));
            else
                printf("%i, ", *(j + *(building_value + i)));
        }
        printf("]\n");
    }
    printf("\n");
}

void print_labels(char **building_labels)
{   
    printf("labels = [");
    for (int i = 0; i < BUILDING_NUMBER_TYPE; ++i)
    {
        if (i == BUILDING_NUMBER_TYPE - 1)
            printf("%s]\n", *(building_labels + i));
        else
            printf("%s, ", *(building_labels + i));
    }
    printf("\n");
}

void print_bias(int *building_bias, char jump)
{
	printf("bias = [");
    for (int i = 0; i < BIAS_NUMBER; ++i)
    {
        if (i == BIAS_NUMBER - 1)
            printf("%i]\n", *(building_bias + i));
        else
            printf("%i, ", *(building_bias + i));
    }
    if (jump)
        printf("\n");
}

char isBias(char *line)
{
	char is = 0;
	if (*line == 'B' && *(line + 1) == 'I' && *(line + 2) == 'A')
		is = 1;
	return is;
}

char isHabitant(char *line)
{
	char is = 0;
	if (*line == 'H' && *(line + 1) == 'A' && *(line + 2) == 'B')
		is = 1;
	return is;
}

void free_building_list(void **build_)
{
	for (int i = 0; i < BUILDING_NUMBER_TYPE; ++i)
		free(*(build_ + i));
	free(build_);
}
