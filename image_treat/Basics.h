#ifndef BASICS_H_
#define BASICS_H_

#include <stdlib.h>
#include <SDL2.h>
#include "SDL2/SDL2.h"
#include "SDL2/SDL2_image.h"

SDL_Surface* load_image(char *path);
Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

#endif
