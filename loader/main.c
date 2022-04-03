#include "read.h"
#include "write.h"
#include "loadtools.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // TEST OF LOADER
    printf("----LOADER TEST----\n");
    int **building_value = load_building_value();
    print_value(building_value);
    char **building_labels = load_building_labels();
    print_labels(building_labels);
	int *building_bias = load_building_bias();
    print_bias(building_bias, 1);
	int habitant_number = load_habitant_number();
    printf("habitant_number = %i\n\n", habitant_number);

    // TEST HABITANT WRITER
    printf("----HABITANT WRITER TEST----\n");
    habitant_number = 20000;
    printf("Writing %i on habitant number...\n", habitant_number);
    write_habitant_number(habitant_number);
    habitant_number = load_habitant_number();
	printf("habitant_number = %i\n\n", habitant_number);
    
    habitant_number = 50;
    printf("Writing %i on habitant number...\n", habitant_number);
    write_habitant_number(habitant_number);
    habitant_number = load_habitant_number();
    printf("habitant_number = %i\n\n", habitant_number);

    // TEST BIAS WRITER
    printf("----HABITANT BIAS TEST----\n");
    int building_biass[] = {8, 5, 10, 20, 30, 2};
    printf("Writing the followin bias : ");
    print_bias(building_biass, 0);
    write_bias(building_biass);
    building_bias = load_building_bias();
    print_bias(building_bias, 1);

    int building_biasss[] = {50, 50, 50, 50, 50, 50};
    printf("Writing the followin bias : ");
    print_bias(building_biasss, 0);
    write_bias(building_biasss);
    building_bias = load_building_bias();
    print_bias(building_bias, 250);
     
    // FREE
    printf("----FREE TEST----\n");
    free_building_list((void*) building_value);
	free_building_list((void*) building_labels);
	free(building_bias);
    return 0;
}