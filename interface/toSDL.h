#ifndef TOSDL_H_
#define TOSDL_H_

#include <stdlib.h>
#include <SDL.h>
#include "build_city.h"
#include "../metro/network.h"

//!Displays from a given matrice a city
void PrintMat(char **matrice, int DIM);

//!Displays from a given graph the subway stations and lines
void PrintMetro(struct EDGE *edges, int DIM);

#endif
