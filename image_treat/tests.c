#include "for_show.h"
#include "grayscale_otsu"

int main()
{
    SDL_Surface image = load_image("image.bmp");
    unsigned char array[image->h][image->w];

    grayscale(image, array);
    Make_A_File(Matrix_2_Surface(array), "grayscaled.bmp");
}
