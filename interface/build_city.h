#ifndef BUILD_CITY_H_
#define BUILD_CITY_H_

#include <stdlib.h>
#include <SDL.h>

//!A tool to test build_city
char **genMat(int DIM);

//!Displays with SDL, the city as well as the subway lines and stations
void build_city(char **matrice, int DIM);

#endif
