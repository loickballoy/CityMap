#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include "toSDL.h"
#include "../metro/network.h"

/**
* @file build_city.c
* @details This file was mainly used for tests and built a random city in order to test the display with our GTK and SDL Graphical User Interface
* @author Remy Decourcelle <remy.decoutcelle@epita.fr>, Loïck Balloy <loick.balloy@epita.fr>, Axel Cochepin <axel.cochepin@epita.fr>, Guillaume Charvolin <guillaume.charvolin@epita.fr>
* @version 0.1
* @date 2022
*/



char **genMat(int DIM)
{
  char **matrice;

  matrice = malloc(sizeof(char *)* DIM);

  for(int k = 0; k < DIM; k++)
    {
      matrice[k] = malloc(sizeof(char *) * DIM);
    }

  for(int i = 0; i < DIM; i++)
    {
      for(int j =0; j < DIM; j++)
	{
            int number = rand();

            if(number%2 == 0)
	      matrice[i][j] = '1';
	    if(number%2 != 0)
	      matrice[i][j] = '4';
            if(number%3 == 0)
	      matrice[i][j] = '2';
            if(number%5 == 0)
	      matrice[i][j] = '3';
	    if(number%7 == 0)
	      matrice[i][j] = '4';
	    if(number%11 == 0)
	      matrice[i][j] = '0';


	}
    }
  return matrice;
}


void build_city(char **matrice, int DIM)
{
  PrintMat(matrice, DIM); // Uses SDL to display a given matrix

  struct EDGE *edges = MakeMetro(matrice, DIM); // Executes the subway algorithm

  PrintMetro(edges, DIM); // Uses SDL to display a graph of the subway lines and stations

  for(int i = 0; i < DIM; i++)
    {
      free(matrice[i]);
    }
  free(matrice);
  free(edges);
}
