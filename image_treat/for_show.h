#ifndef FOR_SHOW_H_
#define FOR_SHOW_H_

#include "Basics.h"

SDL_Surface* Matrix_2_Surface(Uint8 array[], size_t rows, size_t col);
void Make_A_File(SDL_Surface* surf, const char* file);
void Print_Array(Uint8 array[], size_t rows, size_t col);

#endif
