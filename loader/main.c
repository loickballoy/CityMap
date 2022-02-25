#include "read.h"
#include <stdio.h>

int main(void)
{
    int **building_value = load_building_value();
    char **building_labels = load_building_labels(); 

    print_value(building_value);
    print_labels(building_labels);
                       
    //float *bias = load_bias(file);
    free_building_value_and_labels(building_value, building_labels);
    return 0;
}
