#include "read.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int **building_value = load_building_value();
    char **building_labels = load_building_labels();
	int *building_bias = load_building_bias();
	int habitant_number = load_habitant_number();

    print_value(building_value);
    print_labels(building_labels);
	print_bias(building_bias);
	printf("habitant_number = %i\n\n", habitant_number);
                       
    free_building_list((void*) building_value);
	free_building_list((void*) building_labels);
	free(building_bias);
    return 0;
}
