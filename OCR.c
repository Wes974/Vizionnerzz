#include <stdlib.h>
#include <err.h>
#include "Basics.h"
#include "for_show.h"
#include "greyscale_otsu.h"

#include "segmentation.h"

void OCR(char *path, unsigned int superUser)
{
    //Create and load the image file
    SDL_Surface* image;
    image = load_image(path);
    
    //Error if the file wasn't found
    if(image == NULL)
        printf("Load failed: %s\n", SDL_GetError());
    
    //Get image size and initialize the image array
    int height = image->h;
    int width = image->w;
    //printf("h = %u, w = %u", height ,width);
    Uint8 *gray = calloc(height * width, sizeof(Uint8));

    //Grayscale the image array and reconvert it into a surface
    grayscale(image, gray, height, width);
    //Print_Array(gray, width, height);
    SDL_Surface* b_image;
    b_image = Matrix_2_Surface(gray, height, width);
    
    //Convert the grayscaled surface into a .bmp file
    Make_A_File(b_image, "results/grayscaled.bmp");
    
    //Initialize the otsu array and binarize the image array
    unsigned int *otsu_array = calloc(height * width, sizeof(unsigned int));
    otsu(gray, otsu_array, height, width);
    blackOrWhite(otsu_array, height, width);


    //SEGMENTATION//
    segmentation(otsu_array, width, height, superUser);
    
    //NETWORK//
   
    //Create the file result.txt
    FILE *result;
    result = fopen("./data/result.txt", "w");
   
    //Get the number of line
    FILE *line_info;
    line_info = fopen("./data/line_info.txt", "r");
    unsigned int lol = 0;
    unsigned int *numberOfLine = &lol;
    fscanf(line_info, "%u", numberOfLine);
    fclose(line_info);
    remove("./data/line_info.txt");
    //printf("line = %u\n", *numberOfLine);

    for (unsigned int line = 0; line < *numberOfLine; line++) {
        
        FILE *word_info;
        char wordFilename[26 + 3];
        sprintf(wordFilename, "./data/line_%u/word_info.txt", line);
        word_info = fopen(wordFilename, "r");
        unsigned int lolword = 0;
        unsigned int *numberOfWord = &lolword;
        fscanf(word_info, "%u", numberOfWord);
        fclose(word_info);
        remove(wordFilename);
        //printf("word = %u\n", *numberOfWord);

        for (unsigned int word = 0; word < *numberOfWord; word++) {

            FILE *char_info;
            char charFilename[32 + 5];
            sprintf(charFilename, "./data/line_%u/word_%u/char_info.txt", 
                                                                    line, word);
            char_info = fopen(charFilename, "r");
            unsigned int lolchar = 0;
            unsigned int *numberOfChar = &lolchar;
            fscanf(char_info, "%u", numberOfChar);
            fclose(char_info);
            remove(charFilename);
            //printf("char = %u\n", *numberOfChar);
   

            for (unsigned int chara = 0; chara < *numberOfChar; chara++) {
                //Get the char matrix width .txt
                
                FILE *charFile;
                char charFilename[255];
                sprintf(charFilename, "./data/line_%i/word_%i/char_%i.txt", 
                                                            line, word, chara);
                charFile = fopen(charFilename, "r");
                char charMatrixChar[255];
                fscanf(charFile, "%s", charMatrixChar);
                fclose(char_info);
                
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
                fputc(97, result);

                
            }
            if (word != *numberOfWord){
                fprintf(result, " ");
            }
        }
        if (line != *numberOfLine){
            fprintf(result, "\n");
        }
        
    }
    fclose(result);
    
    //Free the image array memory
    free(gray);

    //Free the binarized array memory
    free(otsu_array);
}
