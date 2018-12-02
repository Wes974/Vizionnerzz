#include "for_show.h"

//Take a 2 dimensional matrix and transform it into a SDL_Surface

SDL_Surface* Matrix_2_Surface(Uint8 array[], size_t rows, size_t col)
{
    SDL_Surface* image_surface;

    image_surface = SDL_CreateRGBSurface(0, col, rows, 32, 0, 0, 0, 0);
    
    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < col; j++)
        {       
            Uint8 color = array[i * col + j];
            Uint32 newPixel = SDL_MapRGB(image_surface->format, color, color, color);
            put_pixel(image_surface, j, i, newPixel);
        }
    }

    return image_surface;
}

//Take a surface and save it at emplacement file in bmp format

void Make_A_File(SDL_Surface* surf, const char* file)
{
    if(SDL_SaveBMP(surf, file) < 0)
    {
        printf("Make_A_File failed: %s\n", SDL_GetError());
    }

    SDL_FreeSurface(surf);
}

void Print_Array(Uint8 array[], size_t rows, size_t col)
{
    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < col; j++)
        {       
            printf("%d ", array[i * rows + j]);
        }
        
        printf("\n");
    }

}
