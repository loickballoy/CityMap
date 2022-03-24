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
  SDL_Surface* H;
  SDL_Surface* P;
  SDL_Surface* S;


  init_sdl();

  int dim_surface = DIM * 64;

  image_surface =  SDL_CreateRGBSurface(0, dim_surface, dim_surface, 32,0,0,0,0);
  H = load_image("images/H.png");
  P = load_image("images/P.png");
  S = load_image("images/S.png");
  display_image(image_surface);

  wait_for_keypressed();


  void SetCase(int x, int y, char b, int dim)
  {
    SDL_Surface* bat;

    if(b == 'H')
      bat = H;
    if(b == 'P')
      bat = P;
    if(b == 'S')
      bat = S;

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

            if(b == 'H')
                bat = H;
            if(b == 'P')
                bat = P;
            if(b == 'S')
                bat = S;

            SDL_BlitSurface(bat, &srcRect, image_surface, &dstRect);
            display_image(image_surface);
            y += 64;
            if(y == dim_surface){
                y = 0;
            }
	}
        x += 64;
    }
  SDL_SaveBMP(image_surface, "test");
  display_image(image_surface);

  wait_for_keypressed();
  SDL_FreeSurface(image_surface);
  SDL_FreeSurface(H);
  SDL_FreeSurface(P);
  SDL_FreeSurface(S);
}
