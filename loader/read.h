#ifndef READ_H
#define READ_H

int **init_building_value();
char **init_building_labels();
void fill_value(int *value, char *building_line);
void fill_label(char *label, char *building_line);
char **load_building_labels();
int **load_building_value();
int *load_building_bias();
int load_habitant_number();

#endif

