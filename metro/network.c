#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "graph.h"
#include "network.h"

struct Metro
{
  unsigned int label;
  unsigned int x;
  unsigned int y;
  
};



struct EDGE *buildAdjlists(struct Metro *STATIONS, unsigned int nb_stat,
			    double max, Graph g)
{
  unsigned int * rencontre = (unsigned int *) calloc( nb_stat, sizeof(unsigned int) );
  
  unsigned int proche;
  double min = DBL_MAX;

  struct EDGE *edges = calloc( nb_stat * nb_stat, sizeof(struct EDGE));
  unsigned int k = 0;

  int l = 1;

  for(unsigned int i = 0; i < nb_stat; i++)     //Appelle toute les stations
    {
      unsigned int x1 = STATIONS[i].x;
      unsigned int y1 = STATIONS[i].y;

      min = DBL_MAX;
      
      if(rencontre[i] == 0)                     // Si pas deja relié
	{
	  rencontre[i] = 1;
	      
	  for(unsigned int j = 0; j < nb_stat; j++)
	    {
	      if(i != j)
		{
		  unsigned int x2 = STATIONS[j].x;
		  unsigned int y2 = STATIONS[j].y;
                
		  double a = (double)((x1 - x2) * (x1 - x2));
		  double b = (double)((y1 - y2) * (y1 - y2));
		  double dist = sqrt(a + b);

		  if(dist < min && rencontre[j] == 0 && dist <= max){
		    min = dist;
		    proche = j;
		  }
                    
		}
	    }

	  if(min <= max){
	    
	    add_edge(g, i+1, proche+1);
	    edges[k].src = i;
	    edges[k].dst = proche;
	    
	    edges[k].src_x = STATIONS[i].x;
	    edges[k].src_y = STATIONS[i].y;
	    
	    edges[k].dst_x = STATIONS[proche].x;
	    edges[k].dst_y = STATIONS[proche].y;
	    
	    edges[k].ligne = l;
	    
	    k += 1;
	  }
	  else
	    l += 1;
	  
	}	
    }
  edges[0].nb_edge = k;
  printf("nb edge : %i", k);
  free(rencontre);
  return edges;
}



struct EDGE *buildAdjlists2(struct Metro *STATIONS, unsigned int nb_stat,
			    double max, Graph g)
{
  unsigned int * rencontre = (unsigned int *) calloc( nb_stat, sizeof(unsigned int) );
  
  unsigned int proche;
  double min = DBL_MAX;

  unsigned int nb_l = 2;

  if(nb_stat >= 15)
    nb_l = 3;
  if(nb_stat >= 20)
    nb_l = 4;
  if(nb_stat >= 25)
    nb_l = 5;

  unsigned int nb_st = nb_stat / nb_l;
  

  struct EDGE *edges = calloc( nb_stat, sizeof(struct EDGE));
  unsigned int k = 0;

  int l = 1;

  struct Metro *stat = &STATIONS[0];
  
  for(unsigned int i = 0; i < nb_stat; i++)     //Appelle toute les stations
    {
      
	unsigned int x1 = stat->x;
	unsigned int y1 = stat->y;

	min = DBL_MAX;
	
	if(rencontre[stat->label-1] == 0)                     // Si pas deja relié
	  {
	    rencontre[stat->label-1] = 1;
	    
	    for(unsigned int j = 0; j < nb_stat; j++)
	      {
		if(i != j)
		  {
		    unsigned int x2 = STATIONS[j].x;
		    unsigned int y2 = STATIONS[j].y;
		    
		    double a = (double)((x1 - x2) * (x1 - x2));
		    double b = (double)((y1 - y2) * (y1 - y2));
		    double dist = sqrt(a + b);
		    
		    if(dist < min && rencontre[j] == 0){
		      min = dist;
		      proche = j;
		    }
                    
		  }
	      }
	    if((i+1) % nb_st == 0 && l != (int)nb_l){
	     l += 1;
	    }
	    //else{
	      add_edge(g, stat->label, proche+1);
	      edges[k].src = stat->label-1;
	      edges[k].dst = proche;
	      
	      edges[k].src_x = stat->x;
	      edges[k].src_y = stat->y;
	      
	      edges[k].dst_x = STATIONS[proche].x;
	      edges[k].dst_y = STATIONS[proche].y;
	      
	      edges[k].ligne = l;
	      
	      k += 1;
	      //}
	    stat = &STATIONS[proche];
	      
	    
	  }
       
    }

  
  edges[0].nb_edge = k;

  free(rencontre);
  return edges;
}



int nb_stations(char **matrice, int DIM)
{
  int nb_stat = 0;
  
  for(int i = 0; i < DIM; i++)
    {
      for(int j =0; j < DIM; j++)
	{
            
	  if(matrice[i][j] == '7')
	    nb_stat += 1;
            
	}
    }
  return nb_stat;
}

struct Metro *BuildStations(char **matrice, int DIM, Graph g1)
{

  int nb_stat = nb_stations(matrice, DIM); 

  struct Metro *STATIONS = malloc(sizeof(struct Metro) * nb_stat);

  int k = 0;
  

  for(int i = 0; i < DIM; i++)
    {
      for(int j =0; j < DIM; j++)
	{
	  
	  if(matrice[i][j] == '7')
	    {
	      struct Metro st = {k+1, i, j};
	      add_label(g1, k+1, i, j);
	      STATIONS[k] = st;
	      k += 1;
	    }
	  
	}
    }
  
  return STATIONS;
  
}

struct EDGE *MakeMetro(char **matrice, int DIM)
{
  int NUMBER_STATIONS; 
  double MAX = 4.2;

  NUMBER_STATIONS = nb_stations(matrice, DIM);

  Graph g1 = new_graph(NUMBER_STATIONS, false);

  fprintf(g1->graph_file, "\tedge [color=black];\n");
  fprintf(g1->graph_file, "\tnode [color=turquoise, style=filled];\n");

  struct Metro *STATIONS = BuildStations(matrice, DIM, g1);
  
  struct EDGE *edges = buildAdjlists2(STATIONS, NUMBER_STATIONS, MAX, g1);

  print_graph(g1);
  display_graph(g1);
  erase_graph(g1);
  system("dot -Tpng graph.out -o graph.png");
  
  free(STATIONS);
  return edges;
}
