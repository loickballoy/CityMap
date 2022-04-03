#ifndef LOADTOOLS_H
#define LOADTOOLS_H
#include <stdio.h>

FILE *settings_open();
void print_value(int **building_value);
void print_labels(char **building_labels);
void print_bias(int *building_bias, char jump);
char isHabitant(char *line);
char isBias(char *line);
void free_building_list(void **build_);
void free_building_bias();

// HALL PROPERTY OFFICE COMISSARY SHOP HOSPITAL //
extern int BUILDING_NUMBER_TYPE;

// POLICY JOB HABITATION ECONOMY HEALTH SECURITY RANGE HABITANT_FOR//
extern int VALUE_NUMBER_TYPE;
// POLICY JOB HABITATION ECONOMY HEALTH SECURITY //
extern int BIAS_NUMBER;

extern int BUFFER_SIZE;
extern int LINE_BUFFER_SIZE;
extern int LABEL_SIZE;

#endif
