#include <stdio.h>                                                              
#include <err.h>                                                                
#include <stdlib.h>                                                             
#include "toSDL.h"                                                              
#include "../metro/network.h"
#include "build_city.h"

int main(void){

  int DIM = 15;

  char **matrice = genMat(DIM);

  build_city(matrice, DIM);
  
  return 0;
}
