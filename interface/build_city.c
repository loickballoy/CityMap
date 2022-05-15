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

  printf("Bienvenue sur CityMap !\n");
  //printf("Rentrez les différents paramètres et nous vous générerons une ville\n");
  /*
  int nb_hab;
  int budget;
  int sec;
  int edu;
  int env;

  printf("\nNombre habitants : ");
  scanf("%d", &nb_hab);

  printf("\nBudget : ");
  scanf("%d", &budget);

  printf("\nSécurité : ");
  scanf("%d", &sec);

  printf("\nEducation : ");
  scanf("%d", &edu);

  printf("\nEnvironnement : ");
  scanf("%d", &env);
  printf("\n");

  */

  //list batiment

  //execute les programmes de génération de ville

  //affiche l'image de la ville



  printf("VILLE :\n");

  //char **matrice = genMat(DIM);     // A mettre en parametre de build_city quand on pourra récupérer la matrice de Remy

  PrintMat(matrice, DIM);           // Affiche en SDL la matrice

  struct EDGE *edges = MakeMetro(matrice, DIM);  // Fait le metro

  PrintMetro(edges, DIM);

  // Affiche le metro en SDL (graph.png)

  for(int i = 0; i < DIM; i++)
    {
      free(matrice[i]);
    }
  free(matrice);
  free(edges);

  printf("\n");

}
