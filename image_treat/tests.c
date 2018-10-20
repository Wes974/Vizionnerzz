#include <stdlib.h>
#include "Basics.h"
#include "for_show.h"
#include "greyscale_otsu.h"

int main()
{
    SDL_Surface* image;
    image = load_image("image2.bmp");
    
    int i = image->h;
    int j = image->w;
    Uint8 *gray = calloc(i * j, sizeof(Uint8));

    printf("Image Base:\n");

    /*for(int k = 0; k < i; k++)
    {
        for(int l = 0; l < j; l++)
        {
            Uint32 pixel = get_pixel(image, k, l);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            printf("%d ", r);
        }
        
        printf("\n");
    }
    printf("taille image: %d x %d\n", i, j);*/

    grayscale(image, gray, i, j);
    /*SDL_FreeSurface(image);
    
    printf("Tableau:\n");

    Print_Array(gray, j, i);*/
    /*for(int k = 0; k < i + j; k++)
        printf("rgb value: %d\n", array[k]);*/
    SDL_Surface* b_image;
    b_image = Matrix_2_Surface(gray, i, j);
    
    /*printf("Image Greyscaled:\n");

    for(int k = 0; k < i; k++)
    {
        for(int l = 0; l < j; l++)
        {
            Uint32 pixel = get_pixel(b_image, k, l);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, b_image->format, &r, &g, &b);
            printf("%d ", r);
        }
        
        printf("\n");
    }
    
    for(int m = 0; m < i; m++)
    {
        for(int n = 0; n < j; n++)
        {
            Uint32 newPixel = SDL_MapRGB(b_image->format, 0, 0, 0);
            put_pixel(b_image, m, n, newPixel);
        }
    }*/

    Make_A_File(b_image, "grayscaled.bmp");
    //SDL_FreeSurface(b_image);
    
    Uint8 *otsu_array = calloc(i * j, sizeof(Uint8));
    otsu(gray, otsu_array, i, j);
    //free(gray);
    /*printf("Tableau:\n");
    Print_Array(otsu_array, j, i);*/

    SDL_Surface* f_image;
    f_image = Matrix_2_Surface(otsu_array, i, j);
    //free(otsu_array);
    Make_A_File(f_image, "binarized.bmp");
    //SDL_FreeSurface(f_image);




    /*SDL_Surface* gray = NULL;
    gray = grayscale2(image);
    //SDL_FreeSurface(image);
    Make_A_File(gray, "grayscaled.bmp");
    //SDL_FreeSurface(gray);*/

}
