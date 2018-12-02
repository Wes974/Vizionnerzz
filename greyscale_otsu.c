#include "greyscale_otsu.h"
#include "for_show.h"

//Take a surface and convert it into a grayscaled version into a Matrix

void grayscale(SDL_Surface *surf, Uint8 array[], size_t rows, size_t col)
{
    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < col; j++)
        {
            Uint32 pixel = get_pixel(surf, j, i);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, surf->format, &r, &g, &b);
            array[i * col + j] = 0.3 * r + 0.59 * g + 0.11 * b;
        }
    }
}

//Create the otsu Histogram

void create_Histo(Uint8 *image, size_t rows, size_t col, unsigned long *histo)
{
    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < col; j++)
        {
            size_t index = image[i * col + j];
            histo[index] = histo[index] + 1;
        }
    }
}

void create_Histo2(unsigned int *image, size_t rows, size_t col, 
                                                        unsigned long *histo)
{
    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < col; j++)
        {
            size_t index = image[i * col + j];
            histo[index] = histo[index] + 1;
        }
    }
}

//Find the threshold of otsu by constructing a histogram

unsigned char otsu_threshold(Uint8 array[], size_t rows, size_t col)
{
    //Initialisation and creation of the grayscale histogram
    unsigned long *histo = calloc(256, sizeof(unsigned long));
    create_Histo(array, rows, col, histo);

    //Variable Initialisation
    Uint8 threshold = 0;
    float var_max = 0, prov_tresh = 0;
    unsigned long sum = 0, sumB = 0;
    unsigned long q1 = 0, q2 = 0, m1 = 0, m2 = 0;
    unsigned long N = rows * col;

    for(int i = 0; i < 256; i++)
        sum += i  * histo[i];

    for(int j = 0; j < 256; j++)
    {
        //Weight Background
        q1 += histo[j];
        if(q1 == 0)
            continue;
        
        //Weight Foreground
        q2 = N - q1;
        if(q2 == 0)
            break;

        sumB += j * histo[j];
        
        m1 = sumB / q1;             //Mean Background
        m2 = (sum - sumB) / q2;     //Mean Foreground

        //Calculate the Between Class Variance
        prov_tresh = q1 * q2 * (m1 - m2) * (m1 - m2);

        //Check if the new Between Class Variance is the max Variance
        if(prov_tresh > var_max)
        {
            threshold = j;
            var_max = prov_tresh;
        }
    }
    free(histo);

    return threshold;
}

//Return a binarized matrix from a greyscaled matrix

void otsu(Uint8 image[], unsigned int b_image[], size_t rows, size_t col)
{
    Uint8 threshold = otsu_threshold(image, rows, col);
    
    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < col; j++)
        {
            if(image[i * col + j] > threshold)
                b_image[i * col + j] = 0;
            else
                b_image[i * col + j] = 1;
        }
    }
}

void blackOrWhite(unsigned int image[], size_t rows, size_t col)
{
    unsigned long *histo = calloc(2, sizeof(unsigned long));
    create_Histo2(image, rows, col, histo);

    if(histo[0] < histo[1])
    {
        for(size_t i = 0; i < rows; i++)
        {
            for(size_t j = 0; j < col; j++)
            {
                image[i * col + j] = !image[i * col + j];
            }

        }

    }

    free(histo);
}
