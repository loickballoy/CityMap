#ifndef NETWORK_H_
#define NETWORK_H_

#include <stdlib.h>

struct EDGE
{
  unsigned int src;
  unsigned int dst;

  unsigned int src_x;
  unsigned int src_y;

  unsigned int dst_x;
  unsigned int dst_y;

  int ligne;
  unsigned int nb_edge;
};

struct EDGE *MakeMetro(char **matrice, int DIM);

#endif
