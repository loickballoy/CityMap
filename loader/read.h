#ifndef READ_H
#define READ_H
#include <stdio.h>

int **init_building_value();
char **init_building_labels();
void fill_value(int *value, char *building_line);
void fill_label(char *label, char *building_line);
char **load_building_labels();
int **load_building_value();
int *load_building_bias();
FILE *settings_open(char *path);
void print_value(int **building_value);
void print_labels(char **building_labels);
void print_bias(int *building_bias);
void free_building_list(void **build_);
char isHabitant(char *line);
int load_habitant_number();

#endif

