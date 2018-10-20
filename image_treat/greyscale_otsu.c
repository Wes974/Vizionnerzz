#include "greyscale_otsu.h"
#include "for_show.h"

//Take a surface and convert it into a grayscaled version into a Matrix

void grayscale(SDL_Surface *surf, Uint8 array[], size_t rows, size_t col)
{
    //SDL_Surface* image = SDL_CreateRGBSurface(

    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < col; j++)
        {
            Uint32 pixel = get_pixel(surf, j, i);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, surf->format, &r, &g, &b);
            //printf("r: %d g: %d b: %d\n", r, g, b);
            array[i * col + j] = 0.3 * r + 0.59 * g + 0.11 * b;
        }
    }
}

//Create the otsu Histogram

Uint8 * create_Histo(Uint8 image, size_t rows, size_t col)
{
    Uint8 histo[256];
    array_init(histo);
    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < col; j++)
        {
            size_t index = array[i * col + j];
            histo[index] = histo[index] + 1;
        }
    }
    
    return histo;
}

//Find the treshold of otsu by constructing a histogram

unsigned char otsu_treshold(Uint8 array[], size_t rows, size_t col)
{
    Uint8 *histo;
    histo = create_Histo(array, rows, col);

}

//Return a binarized matrix from a greyscaled matrix

void otsu(Uint8 image[], Uint8 b_image[], size_t rows, size_t col)
{
    Uint8 treshold = otsu_treshold(image, rows, col);
    printf("Treshold: %d\n", treshold);
    
    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < col; j++)
        {
            if(image[i * col + j] >= treshold)
                b_image[i * col + j] = 255;
            else
                b_image[i * col + j] = 0;
        }
    }
}

/*SDL_Surface* grayscale2(SDL_Surface *surf)
{
    SDL_Surface* gray;
    gray = SDL_CreateRGBSurface(0, surf->w, surf->h, 32, 0, 0, 0, 0);

    for(int i = 0; i < surf->h; i++)
    {
        for(int j = 0; j < surf->w; j++)
        {
            Uint32 pixel = get_pixel(surf, j, i);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, surf->format, &r, &g, &b);
            //printf("r: %d g: %d b: %d\n", r, g, b);
            Uint8 color = 0.3 * r + 0.59 * g + 0.11 * b;
            Uint32 newPixel = SDL_MapRGB(surf->format, color, color, color);
            put_pixel(gray, j, i, newPixel);
        }
    }

    return gray;
}*/


