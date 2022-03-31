#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"

struct metro
{
    unsigned int label;
    unsigned int x;
    unsigned int y;
    //unsigned int *adjlists;
};

unsigned int *buildAdjlists(struct metro *STATIONS, unsigned int nb_stat,
			    unsigned int max, Graph g)
{
    for(unsigned int i = 0; i < nb_stat; i++)
    {
        unsigned int x1 = STATIONS[i].x;
        unsigned int y1 = STATIONS[i].y;
        
        for(unsigned int j = 0; j < nb_stat; j++)
        {
            if(i != j)
            {
                unsigned int x2 = STATIONS[j].x;
                unsigned int y2 = STATIONS[j].y;
                
                double a = double((x1 - x2) * (x1 - x2));
                double b = double((y1 - y2) * (y1 - y2));
                double dist = sqrt(a + b);
                
                if(dist <= max)
                {
                    add_edge(g, i, j);
                    // verif connexe
                }
	    }
	}
    }
}

int main()
{
  unsigned int NUMBER_STATIONS;
  unsigned int MAX;

  struct metro *STATIONS = malloc(sizeof(struct metro) * NUMBER_STATIONS);

  //remplissage de STATIONS en récupérant les x et y dans la matrice

  // buildAdjlists

  

}

