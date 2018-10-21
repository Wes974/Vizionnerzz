#include <stdlib.h>
#include <err.h>
#include "Basics.h"
#include "for_show.h"
#include "greyscale_otsu.h"

int main(int argc, char** argv)
{
    char* param = argv[1];

    if(argc != 2)
        errx(1, "Too many arguments");

    SDL_Surface* image;
    image = load_image(param);

    if(image == NULL)
        printf("Load failed: %s\n", SDL_GetError());
    
    int i = image->h;
    int j = image->w;
    Uint8 *gray = calloc(i * j, sizeof(Uint8));

    grayscale(image, gray, i, j);
    SDL_Surface* b_image;
    b_image = Matrix_2_Surface(gray, i, j);
    
    Make_A_File(b_image, "results/grayscaled.bmp");
    
    Uint8 *otsu_array = calloc(i * j, sizeof(Uint8));
    otsu(gray, otsu_array, i, j);
    free(gray);

    SDL_Surface* f_image;
    f_image = Matrix_2_Surface(otsu_array, i, j);
    free(otsu_array);
    Make_A_File(f_image, "results/binarized.bmp");

    return 0;
}
