#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "read.h"
#include "loadtools.h"

int **init_building_value()
{
    int **building_value = malloc(sizeof(int*) * BUILDING_NUMBER_TYPE);
    for (int i = 0; i < BUILDING_NUMBER_TYPE; ++i)
        *(building_value + i) = malloc(sizeof(int) * VALUE_NUMBER_TYPE);
    return building_value;
}

char **init_building_labels()
{
    char **building_labels = malloc(sizeof(char*) * BUILDING_NUMBER_TYPE);
    for (int i = 0; i < BUILDING_NUMBER_TYPE; ++i)
        *(building_labels + i) = malloc(sizeof(char) * (LABEL_SIZE + 1));
    return building_labels;
}

int *init_building_bias()
{
	int *building_bias = malloc(sizeof(int) * BIAS_NUMBER);
	return building_bias;
}

void fill_value(int *value, char *building_line)
{
    while (*building_line != '[')
        ++building_line;
    
    ++building_line;

    char buffer[BUFFER_SIZE];
    while (*building_line != ']')
    {
        char *buf = buffer;
        while (*building_line != ',' && *building_line != ']')
        {
            *buf = *building_line;
            ++buf;
            ++building_line;
        }

        *buf = 0;
    
        if (*building_line != ']')
            ++building_line;
 
        *value = (int) atol(buffer);
        ++value;
    }
}

void fill_label(char *label, char *building_line)
{
    for (int i = 0; i < LABEL_SIZE; ++i)
    {
        *label = *building_line;
        ++label;
        ++building_line;
    }
    *label = 0;
}

char **load_building_labels()                                          
{                                                                               
    FILE *file = settings_open();
    char **building_labels = init_building_labels();
    char buffer[LINE_BUFFER_SIZE];
    fgets(buffer, LINE_BUFFER_SIZE, file);
    for (int i = 0; i < BUILDING_NUMBER_TYPE; ++i)                              
    {                                                                           
        fgets(buffer, LINE_BUFFER_SIZE, file);                                        
        fill_label(*(building_labels + i), buffer);                                    
    }                                                                           
    fclose(file);
    return building_labels;                                                      
} 

int **load_building_value()
{   
    FILE *file = settings_open();
    char buffer[LINE_BUFFER_SIZE];
    fgets(buffer, LINE_BUFFER_SIZE, file);
    int **building_value = init_building_value();
    for (int i = 0; i < BUILDING_NUMBER_TYPE; ++i)
    {
        fgets(buffer, LINE_BUFFER_SIZE, file);
        fill_value(*(building_value + i), buffer);
    }
    fclose(file);
    return building_value;
}

int *load_building_bias()
{
	FILE *file = settings_open();
	char buffer[LINE_BUFFER_SIZE];
	fgets(buffer, LINE_BUFFER_SIZE, file);
	int *building_bias = init_building_bias();
	while(!isBias(buffer))
		fgets(buffer, LINE_BUFFER_SIZE, file);
	fill_value(building_bias, buffer);
	fclose(file);
	return building_bias;
}

int load_habitant_number()
{
	FILE *file = settings_open();
	char buffer[LINE_BUFFER_SIZE];
	fgets(buffer, LINE_BUFFER_SIZE, file);
	int habitant_number;
	while(!isHabitant(buffer))
		fgets(buffer, LINE_BUFFER_SIZE, file);
	fill_value(&habitant_number, buffer);
	fclose(file);
	return habitant_number;
}
