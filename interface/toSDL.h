#ifndef TOSDL_H_
#define TOSDL_H_

#include <stdlib.h>
#include <SDL.h>
#include "build_city.h"
#include "../metro/network.h"

void PrintMat(char **matrice, int DIM);

void PrintMetro(struct EDGE *edges, int DIM);

#endif
