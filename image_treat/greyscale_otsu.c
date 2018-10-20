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

void create_Histo(Uint8 *image, size_t rows, size_t col, unsigned long *histo)
{
    array_init(histo);
    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < col; j++)
        {
            size_t index = image[i * col + j];
            histo[index] = histo[index] + 1;
        }
    }
}

//Find the treshold of otsu by constructing a histogram

unsigned char otsu_treshold(Uint8 array[], size_t rows, size_t col)
{
    unsigned long *histo =calloc(256, sizeof(unsigned long));
    create_Histo(array, rows, col, histo);
    Uint8 treshold = 0;
    float var_max = 0, prov_tresh = 0;
    unsigned long sum = 0, sumB = 0;
    unsigned long q1 = 0, q2 = 0, m1 = 0, m2 = 0;
    unsigned long N = rows * col;

    for(int i = 0; i < 256; i++)
        sum += i  * histo[i];

    for(int j = 0; j < 256; j++)
    {
        q1 += histo[j];
        if(q1 == 0)
            continue;
        q2 = N - q1;
        if(q2 == 0)
            break;

        sumB += j * histo[j];
        m1 = sumB / q1;
        m2 = (sum - sumB) / q2;

        prov_tresh = q1 * q2 * (m1 - m2) * (m1 - m2);

        if(prov_tresh > var_max)
        {
            treshold = j;
            var_max = prov_tresh;
        }
    }

    return treshold;
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


