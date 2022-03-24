#ifndef TOOL_IMAGE_H
#define TOOL_IMAGE_H

#include <stdlib.h>
#include <SDL.h>
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "err.h"

void init_sdl();
SDL_Surface* load_image(char *path);
SDL_Surface* create_image(size_t h,size_t d);
SDL_Surface* display_image(SDL_Surface *img);
void wait_for_keypressed();

#endif
