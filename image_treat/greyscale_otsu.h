#ifndef GREYSCALE_OTSU_H_
#define GREYSCALE_OTSU_H_

#include "Basics.h"

static inline
void array_init(unsigned long *array)
{
    for (size_t i = 0; i < 256; i++)
        array[i] = 0;
}

void grayscale(SDL_Surface *surf, Uint8 array[] , size_t rows, size_t col);
void create_Histo(Uint8 *image, size_t rows, size_t col, unsigned long *histo);
unsigned char otsu_treshold(Uint8 array[], size_t rows, size_t col);
void otsu(Uint8 image[], unsigned int b_image[], size_t rows, size_t col);
SDL_Surface* grayscale2(SDL_Surface *surf);

#endif
