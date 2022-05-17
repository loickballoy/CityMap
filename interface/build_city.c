#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include "toSDL.h"
#include "../metro/network.h"


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
