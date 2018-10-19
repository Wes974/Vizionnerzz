#ifndef GREYSCALE_OTSU_H_
#define GREYSCALE_OTSU_H_

#include "Basics.h"

static inline
void array_init(int array[])
{
    for (size_t i = 0; i < 256; ++i)
        array[i] = 0;
}

void grayscale(SDL_Surface *surf, unsigned char *array[], , int rows, int col);
unsigned char otsu_treshold(unsigned char array[], int rows, int col);
void otsu(unsigned char image[], unsigned char *b_image[], int rows, int col);

#endif
