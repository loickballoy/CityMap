#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "read.h"

// HALL PROPERTY OFFICE COMISSARY SHOP HOSPITAL //
int BUILDING_NUMBER_TYPE = 6;
// POLICY JOB HABITATION ECONOMY HEALTH SECURITY RANGE HABITANT_FOR//
int VALUE_NUMBER_TYPE = 8;
// POLICY JOB HABITATION ECONOMY HEALTH SECURITY //
int BIAS_NUMBER = 6;

int BUFFER_SIZE = 32;
int LINE_BUFFER_SIZE = 128;
int LABEL_SIZE = 3;
char SETTINGS_PATH[] = "settings";

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

void print_value(int **building_value)
{
    for (int i = 0; i < BUILDING_NUMBER_TYPE; ++i)
    {
        printf("value %i = [", i);
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
    for (int i = 0; i < BUILDING_NUMBER_TYPE; ++i)
       printf("label %i = %s\n", i, *(building_labels + i));
    printf("\n");
}

FILE *settings_open(char *path)
{
    FILE *file = fopen(path, "r");
    if (file == NULL)
        errx(1, "The file does not exist");
    return file;
}

char **load_building_labels()                                          
{                                                                               
    FILE *file = settings_open(SETTINGS_PATH);
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
    FILE *file = settings_open(SETTINGS_PATH);
    char buffer[LINE_BUFFER_SIZE];
    fgets(buffer, LINE_BUFFER_SIZE, file);
    int **building_value = init_building_value();
    int **building_value_copy = building_value;
    for (int i = 0; i < BUILDING_NUMBER_TYPE; ++i)
    {
        fgets(buffer, LINE_BUFFER_SIZE, file);
        fill_value(*(building_value_copy + i), buffer);
    }
    fclose(file);
    return building_value;
}

void free_building_value_and_labels(int **build_value, char **build_labels)
{
    for (int i = 0; i < BUILDING_NUMBER_TYPE; ++i)
    {
        free(*(build_value + i));
        free(*(build_labels + i));
    }
    free(build_value);
    free(build_labels);
}
