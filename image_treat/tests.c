#include "Basics.h"
#include "for_show.h"
#include "greyscale_otsu.h"

int main()
{
    SDL_Surface* image = load_image("image.bmp");
    
    int i = image->h;
    int j = image->w;
    unsigned char array[i + j];

    grayscale(image, *array, i, j);
    Make_A_File(Matrix_2_Surface(array, i, j), "grayscaled.bmp");
}
