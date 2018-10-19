#include "greyscale_otsu.h"

void grayscale(SDL_Surface *surf, unsigned char *array[], int rows, int col)
{
    for(size_t i = 0; i < col; i++)
    {
        for(size_t j = 0; j < rows; i++)
        {
            Uint32 pixel = get_pixel(image_surface, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            array[i + j] = 0.3 * r + 0.59 * g + 0.11 * b;
        }
    }
}

unsigned char otsu_treshold(unsigned char array[][], int rows, int col)
{
    int histo[256];
    array_init(histo);
    for(size_t i = 0; i < col; i++)
    {
        for(size_t j = 0; j < rows; i++)
        {
            size_t index = (size_t)array[i + j];
            histo[index]++;
        }
    }

    unsigned char medium = 0;
    for(size_t k = 0; k < sizeof(histo); k++)
    {
        medium += histo[k];
    }

    return medium / 256;

}

void otsu(unsigned char image[], unsigned char *b_image[], int rows, int col)
{
    unsigned char treshold = otsu_treshold(image);
    
    for(size_t i = 0; i < col; i++)
    {
        for(size_t j = 0; j < rows; i++)
        {
            if(image[i + j] >= treshold)
                b_image[i + j] = 255;
            else
                b_image[i + j] = 0;
        }
    }
}
