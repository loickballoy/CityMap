#ifndef READ_H
#define READ_H
#include <stdio.h>

int **init_building_value();
char **init_building_labels();
void fill_value(int *value, char *building_line);
void fill_label(char *label, char *building_line);
char **load_building_labels();
int **load_building_value();
FILE *settings_open(char *path);
void print_value(int **building_value);
void print_labels(char **building_labels);
void free_building_value_and_labels(int **build_value, char **build_labels);

#endif

