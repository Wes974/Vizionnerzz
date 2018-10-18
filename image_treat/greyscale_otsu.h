#ifndef GREYSCALE_OTSU_H_
#define GREYSCALE_OTSU_H_

#include "Basics.h"

static inline
void array_init(int array[])
{
    for (size_t i = 0; i < 256; ++i)
        array[i] = 0;
}

void grayscale(SDL_Surface *surf, unsigned char *array[][]);
unsigned char otsu_treshold(unsigned char array[][]);
void otsu(unsigned char image[][], unsigned char *b_image[][]);

#endif
