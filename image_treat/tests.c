#include <stdlib.h>
#include <err.h>
#include "Basics.h"
#include "for_show.h"
#include "greyscale_otsu.h"

#include "segmentation.h"

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
    int height = image->h;
    int width = image->w;
    Uint8 *gray = calloc(height * width, sizeof(Uint8));

    //Grayscale the image array and reconvert it into a surface
    grayscale(image, gray, height, width);
    SDL_Surface* b_image;
    b_image = Matrix_2_Surface(gray, height, width);
    
    //Convert the grayscaled surface into a .bmp file
    Make_A_File(b_image, "results/grayscaled.bmp");
    
    //Initialize the otsu array and binarize the image array
    unsigned int *otsu_array = calloc(height * width, sizeof(unsigned int));
    otsu(gray, otsu_array, height, width);


    //SEGMENTATION//
    segmentation(otsu_array, width, height);
    
    //NETWORK//

    /*
    //Create the file result.txt
    FILE *result;
    result = fopen("./data/result.txt", "w");
   
    unsigned int numberOfLine = (unsigned int)system("ls -l data/|wc -l") - 1; 
    for (unsigned int line = 0; line < numberOfLine; line++) {
        char wordFilename[255];
        sprintf(wordFilename, "ls -l data/line_%i|wc -l", line);
        unsigned int numberOfWord = (unsigned int)system(wordFilename) - 1;
        for (unsigned int word = 0; word < numberOfWord; word++) {
            char charFilename[255];
            sprintf(charFilename, "ls -l data/line_%i/word_%i|wc -l", line, word);
            unsigned int numberOfChar = (unsigned int)system(charFilename) - 1;
            for (unsigned int chara = 0; chara < numberOfChar; chara++) {
                //Get the char matrix width .txt
                FILE *charFile;
                char charFilename[255];
                sprintf(charFilename, "./data/line_%i/word_%i/char_%i.txt", line, word, chara);
                charFile = fopen(charFilename, "r");
                char charMatrixChar[255];
                fscanf(charFile, "%s", charMatrixChar);
                
                unsigned int *charMatrix = calloc(255, sizeof(unsigned int));
                unsigned int *p = charMatrix;
                for (unsigned int i = 0; i < 255; i++){
                    *p = charMatrix[i] - 48;
                    p++;
                }
                
                //Get the char width
                char charWidthChar[25];
                fscanf(charFile, "%s", charWidthChar);
                unsigned int charWidth;
                sscanf(charWidthChar, "%d", &charWidth);

                //Get the char height
                char charHeightChar[25];
                fscanf(charFile, "%s", charHeightChar);
                unsigned int charHeight;
                sscanf(charHeightChar, "%d", &charHeight);

                //NETWORK
                //char letter = network(...);
                //fputc(letter, result);

                
            }
            if (word != numberOfWord){
                fprintf(result, " ");
            }
        }
        if (line != numberOfLine){
            fprintf(result, "\n");
        }
    }
    */

    //Free the image array memory
    free(gray);
    
    //Convert the binarized array into a surface
    //SDL_Surface* f_image;
    //f_image = Matrix_2_Surface(otsu_array, height, width);

    //Print_Array(gray, height, width);

    //Free the binarized array memory
    free(otsu_array);

    //Convert the binarized surface into a .bmp file
    //Make_A_File(f_image, "results/binarized.bmp");
    
    return 0;
}
