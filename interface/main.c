#include <stdio.h>                                                              
#include <err.h>                                                                
#include <stdlib.h>                                                             
#include "toSDL.h"                                                              
#include "../metro/network.h"
#include "build_city.h"

/**
* @file main.c
* @details This file is the extenstion of the tests found <build_city.c> and executes the code found in said file.
* @author Remy Decourcelle <remy.decoutcelle@epita.fr>, Loïck Balloy <loick.balloy@epita.fr>, Axel Cochepin <axel.cochepin@epita.fr>, Guillaume Charvolin <guillaume.charvolin@epita.fr>
* @version 0.1
* @date 2022
*/



int main(void){

  int DIM = 15;

  char **matrice = genMat(DIM);

  build_city(matrice, DIM);
  
  return 0;
}
