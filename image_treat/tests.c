#include <stdlib.h>
#include <err.h>
#include "Basics.h"
#include "for_show.h"
#include "greyscale_otsu.h"

int main(int argc, char** argv)
{
    //Get the path of the image file
    char* param = argv[1];

    //Error if there is more than 2 arguments
    if(argc != 2)
        errx(1, "Too many arguments");

    //Create and load the image file
    SDL_Surface* image;
    image = load_image(param);
    
    //Error if the file wasn't found
    if(image == NULL)
        printf("Load failed: %s\n", SDL_GetError());
    
    //Get image size and initialize the image array
    int i = image->h;
    int j = image->w;
    Uint8 *gray = calloc(i * j, sizeof(Uint8));

    //Grayscale the image array and reconvert it into a surface
    grayscale(image, gray, i, j);
    SDL_Surface* b_image;
    b_image = Matrix_2_Surface(gray, i, j);
    
    //Convert the grayscaled surface into a .bmp file
    Make_A_File(b_image, "results/grayscaled.bmp");
    
    //Initialize the otsu array and binarize the image array
    Uint8 *otsu_array = calloc(i * j, sizeof(Uint8));
    otsu(gray, otsu_array, i, j);

    //Free the image array memory
    free(gray);
    
    //Convert the binarized array into a surface
    SDL_Surface* f_image;
    f_image = Matrix_2_Surface(otsu_array, i, j);

    //Free the binarized array memory
    free(otsu_array);

    //Convert the binarized surface into a .bmp file
    Make_A_File(f_image, "results/binarized.bmp");

    return 0;
}
