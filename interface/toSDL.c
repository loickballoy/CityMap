#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "tool/tool_image.h"
#include "tool/pixel_operations.h"
#include "toSDL.h"


void PrintMat(char **matrice, int DIM)
{
  SDL_Surface* image_surface;
  SDL_Surface* Hall;
  SDL_Surface* Prop;
  SDL_Surface* Comi;
  SDL_Surface* Hosp;
  SDL_Surface* Offi;


  init_sdl();

  int dim_surface = DIM * 64;

  image_surface =  SDL_CreateRGBSurface(0, dim_surface, dim_surface, 32,0,0,0,0);
  Hall = load_image("images/hall.png");
  Prop = load_image("images/prop.png");
  Comi = load_image("images/comi.png");
  Hosp = load_image("images/hosp.png");
  Offi = load_image("images/offi.png");
  display_image(image_surface);

  wait_for_keypressed();


  void SetCase(int x, int y, char b, int dim)
  {
    SDL_Surface* bat;

    if(b == '0')
      bat = Hall;
    
    if(b == '1')
      bat = Prop;
    
    if(b == '2')
      bat = Comi;

    if(b == '3')
      bat = Hosp;

    if(b == '4')
      bat = Offi;

    int _x = x;
    int _y = y;

    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j < dim; j++)
	{
            //printf("x:%u y:%u \n", x,y);
            Uint32 pixel = get_pixel(bat, i, j);
            put_pixel(image_surface, _x, _y, pixel);
            _y += 1;
            if(_y == (y + dim))
	    {
                _y = y;
                _x += 1;
	    }
	}
    }
  }

  int x = 0;
  int y = 0;
  for(int i = 0; i < DIM; i++)
    {
        for(int j = 0; j < DIM; j++)
	{
            char b = matrice[i][j];
            printf("i:%u j:%u \n", i,j);
            //SetCase(y,x,b,64);
            SDL_Rect srcRect = {0,0,64,64};
            SDL_Rect dstRect = {y,x,64,64};

            SDL_Surface* bat;

            if(b == '0')
	      bat = Hall;
	    
	    if(b == '1')
	      bat = Prop;
	    
	    if(b == '2')
	      bat = Comi;
	    
	    if(b == '3')
	      bat = Hosp;
	    
	    if(b == '4')
	      bat = Offi;

            SDL_BlitSurface(bat, &srcRect, image_surface, &dstRect);
            display_image(image_surface);
            y += 64;
            if(y == dim_surface){
                y = 0;
            }
	}
        x += 64;
    }
  SDL_SaveBMP(image_surface, "CityMap.png");
  display_image(image_surface);

  wait_for_keypressed();
  SDL_FreeSurface(image_surface);
  SDL_FreeSurface(Hall);
  SDL_FreeSurface(Prop);
  SDL_FreeSurface(Comi);
  SDL_FreeSurface(Hosp);
  SDL_FreeSurface(Offi);
}
