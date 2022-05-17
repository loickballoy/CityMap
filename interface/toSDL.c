#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "tool/tool_image.h"
#include "tool/pixel_operations.h"
#include "toSDL.h"
#include "../metro/network.h"

/**
* @file toSDL.c
* @details This file converts the matrix given after the placement of our buildings to an SDL image.
* @author Remy Decourcelle <remy.decoutcelle@epita.fr>, Loïck Balloy <loick.balloy@epita.fr>, Axel Cochepin <axel.cochepin@epita.fr>, Guillaume Charvolin <guillaume.charvolin@epita.fr>
* @version 0.1
* @date 2022
*/



void PrintMat(char **matrice, int DIM)
{
  SDL_Surface* image_surface;
  SDL_Surface* Hall;
  SDL_Surface* Prop;
  SDL_Surface* Comi;
  SDL_Surface* Hosp;
  SDL_Surface* Offi;
  SDL_Surface* Road;
  SDL_Surface* Shop;
  SDL_Surface* Noir;
  SDL_Surface* Metro;


  init_sdl();

  int dim_surface = DIM * 64;

  image_surface =  SDL_CreateRGBSurface(0, dim_surface, dim_surface, 32,0,0,0,0);
  Hall = load_image("images/hall.png");
  Prop = load_image("images/prop.png");
  Comi = load_image("images/comi.png");
  Hosp = load_image("images/hosp.png");
  Offi = load_image("images/offi.png");
  Shop = load_image("images/shop.png");
  Road = load_image("images/road.png");
  Noir = load_image("images/noir.png");
  Metro = load_image("images/metro.png");

  int x = 0;
  int y = 0;
  for(int i = 0; i < DIM; i++)
    {
      for(int j = 0; j < DIM; j++)
	{
	  char b = matrice[i][j];
          
	  SDL_Rect srcRect = {0,0,64,64};
	  SDL_Rect dstRect = {y,x,64,64};
	  
	  SDL_Surface* bat;
	  bat = Noir;
	  
	  if(b == '0')
	    bat = Hall;
	  
	  if(b == '1')
	    bat = Prop;
	  
	  if(b == '2')
	    bat = Offi;
	  
	  if(b == '3')
	    bat = Comi;

	  if(b == '4')
	    bat = Shop;
	  
	  if(b == '5')
	    bat = Hosp;
	  
	  if(b == '6')
	    bat = Road;

	  if(b == '7')
	    bat = Metro;

	  
	  SDL_BlitSurface(bat, &srcRect, image_surface, &dstRect);
          
	  y += 64;
	  if(y == dim_surface){
	    y = 0;
	  }
	}
      x += 64;
    }
  
  SDL_SaveBMP(image_surface, "CityMap.png");
  //display_image(image_surface);
  
  //wait_for_keypressed();
  
  SDL_FreeSurface(image_surface);
  SDL_FreeSurface(Hall);
  SDL_FreeSurface(Prop);
  SDL_FreeSurface(Comi);
  SDL_FreeSurface(Hosp);
  SDL_FreeSurface(Offi);
  SDL_FreeSurface(Shop);
  SDL_FreeSurface(Road);
  SDL_FreeSurface(Noir);
  SDL_FreeSurface(Metro);

  SDL_Quit();
  //exit(EXIT_SUCCESS);

}

void PrintMetro(struct EDGE *edges, int DIM)
{
  SDL_Surface* image_surface;
  SDL_Surface* Metro;
  SDL_Surface* Ligne;
  
  SDL_Surface* Noir;
  SDL_Surface* Rouge;
  SDL_Surface* Bleue;
  SDL_Surface* Orange;
  SDL_Surface* Vert;
  SDL_Surface* Violet;


  init_sdl();

  int dim_surface = DIM * 64;

  image_surface =  SDL_CreateRGBSurface(0, dim_surface, dim_surface, 32,0,0,0,0);

  //init images
  Noir = load_image("images/noir.png");
  Metro = load_image("images/metro.png");
  Ligne = load_image("images/ligne.png");

  Rouge = load_image("images/rouge.png");
  Vert = load_image("images/vert.png");
  Bleue = load_image("images/bleue.png");
  Orange = load_image("images/orange.png");
  Violet = load_image("images/violet.png");

  SDL_Rect srcRect = {0,0,64,64};

  unsigned int nb_edge = edges[0].nb_edge; 

  
  //parcours edges
  for(int k = 0; k < (int)nb_edge; k++)
    {
      
      struct EDGE ed = edges[k];

      int i = (int) ed.src_x;
      int j = (int) ed.src_y;

      int a = (int) ed.dst_x;
      int b = (int) ed.dst_y;

      if(ed.ligne == 1)
	Ligne = Vert;
      if(ed.ligne == 2)
	Ligne = Rouge;
      if(ed.ligne == 3)
	Ligne = Bleue;
      if(ed.ligne == 4)
	Ligne = Orange;
      if(ed.ligne == 5)
	Ligne = Violet;

      
      int n_i = 1;
      int n_j = 1;
      
      if(i > a)
	n_i = -1;
      if(j > b)
	n_j = -1;

      while(j != b){

	j += n_j; 
	
	SDL_Rect dstRect = {j*64,i*64,64,64};

	SDL_BlitSurface(Ligne, &srcRect, image_surface, &dstRect);
	
      }
      while(i != a){

	i += n_i;
	
	SDL_Rect dstRect = {j*64,i*64,64,64};

	SDL_BlitSurface(Ligne, &srcRect, image_surface, &dstRect);
	
      }
 
    }

  for(int k = 0; k < (int)nb_edge; k++) //Rajoute les stations
    {
      
      struct EDGE ed = edges[k];

      SDL_Rect dstRect1 = {((int)ed.src_y*64),((int)ed.src_x*64),64,64};

      SDL_BlitSurface(Metro, &srcRect, image_surface, &dstRect1);

      SDL_Rect dstRect2 = {((int)ed.dst_y*64),((int)ed.dst_x*64),64,64};

      SDL_BlitSurface(Metro, &srcRect, image_surface, &dstRect2);
    }

      

  SDL_SaveBMP(image_surface, "Metro.png");
  //display_image(image_surface);

  //wait_for_keypressed();

  SDL_FreeSurface(image_surface);
  SDL_FreeSurface(Metro);
  //SDL_FreeSurface(Ligne);
  SDL_FreeSurface(Noir);

  
  SDL_FreeSurface(Rouge);
    
  SDL_FreeSurface(Vert);
  
  SDL_FreeSurface(Bleue);
  
  SDL_FreeSurface(Orange);
  
  SDL_FreeSurface(Violet);
  
  SDL_Quit();
}
