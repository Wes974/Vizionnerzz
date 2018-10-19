#include "for_show.h"

SDL_Surface* Matrix_2_Surface(int array[], int rows, int col)
{
    SDL_Surface* image_surface;

    image_surface = SDL_CreateRGBSurface(0, rows, col, 32, 0, 0, 0, 0);
    
    for(size_t i = 0; i < col; i++)
    {
        for(size_t j = 0; j < rows; i++)
        {       
            Uint32 newPixel = SDL_MapRGB(image_surface->format, array[i][j], array[i][j], array[i][j]);
            put_pixel(image_surface, j, i, newPixel);
        }
    }

    return image_surface;
}

void Make_A_File(SDL_Surface *surf, const char* file)
{
    if(SDL_SaveBMP(surf, file) < 0)
    {
        printf("Make_A_File failed: %s\n", SDL_GetError());
    }
}
