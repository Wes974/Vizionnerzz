#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "wordSegmentation.h"
#include "lineSegmentation.h"
#include "charSegmentation.h"
#include <sys/types.h>
#include <errno.h>

int main(){
    //EXAMPLE//
    unsigned int matrixPicture[3*5] = {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0}; 

    unsigned int width = 5;
    unsigned int height = 3;
    
    if(mkdir("./data",0700 && errno != EEXIST)){
        mkdir("./data/", 0700);
    }

    printf("Original Image :\n");
    for (unsigned int i = 0; i < height; i++){
        for (unsigned int j = 0; j < width; j++){
            printf("%u ", matrixPicture[i*width+j]);
        }
        printf("\n");
    }
    printf("\n");


    //LINE//
    
    unsigned int * listLines = matrixToListLine(matrixPicture, height, width);
    unsigned int numberOfLine = lineSave(listLines, matrixPicture, width, height);

    //WORD//

    for(unsigned int i = 0; i < numberOfLine; i++){
        //GET MATRIX LINE//
        FILE *lineFile;
        char lineFilename[255];
        sprintf(lineFilename, "./data/line_%i/line_%i.txt", i, i);
        lineFile = fopen(lineFilename, "r");
        char lineMatrixChar[255];
        fscanf(lineFile, "%s", lineMatrixChar);

        unsigned int *lineMatrix = calloc(255, sizeof(unsigned int));
        unsigned int *p = lineMatrix;
        for (unsigned int j = 0; j < 255; j++){
            *p = lineMatrixChar[j] - 48;
            p++;
        }
        char lineHeight[25];
        fscanf(lineFile, "%s", lineHeight);
        unsigned int lineHeightNumber;
        sscanf(lineHeight, "%d", &lineHeightNumber);

        printf("Line number %u :\n", i);
        for (unsigned int j = 0; j < lineHeightNumber; j++){
            for (unsigned int k = 0; k < width; k++){
                printf("%u ", lineMatrix[j*width+k]);
            }
            printf("\n");
        }
        //WORD SEGMENTATION
        unsigned int * listWords = matrixToListWord(lineMatrix, lineHeightNumber, width);

        printf("\n");
        for (unsigned int j = 0; j < width; j++){
            printf("%u ", listWords[j]);
        }
        printf("\n");
        unsigned int threshold = thresholdDefine(listWords, width);
        printf("Threshold = %u\n\n", threshold);
        unsigned int numberOfWord = wordSave(threshold, listWords, lineMatrix, width, lineHeightNumber, i);
        free(lineMatrix);
        
        for(unsigned int j = 0; j < numberOfWord; j++){
            //GET MATRIX WORD//
            FILE *wordFile;
            char wordFilename[255];
            sprintf(wordFilename, "./data/line_%i/word_%i/word_%i.txt", i, j, j);
            wordFile = fopen(wordFilename, "r");
            char wordMatrixChar[255];
            fscanf(wordFile, "%s", wordMatrixChar);
            
            unsigned int *wordMatrix = calloc(255, sizeof(unsigned int));
            unsigned int *q =wordMatrix;
            for (unsigned int k = 0; k < 255; k++){
                *q = wordMatrixChar[k] - 48;
                q++;
            }
            char wordWidth[25];
            fscanf(wordFile, "%s", wordWidth);
            unsigned int wordWidthNumber;
            sscanf(wordWidth, "%d", &wordWidthNumber);

            printf("Word number %u :\n", j);
            for (unsigned int k = 0; k < lineHeightNumber; k++){
                for (unsigned int l = 0; l < wordWidthNumber; l++){
                    printf("%u ", wordMatrix[k*width+l]);
                }
                printf("\n");
            }
            fclose(wordFile);
        }
        fclose(lineFile);
    }

    
    /*
    unsigned int * listWord = matrixToListLine(matrixPicture, height, width);
    unsigned int threshold = thresholdDefine(listWord, width);

    unsigned int numberOfWord = wordSave(threshold, listWord, matrixPicture, width, height, numberOfLine);
    
    //CHAR//
 
    unsigned int * charLines = matrixToListLine(matrixPicture, height, width); 
    unsigned int charNumber = charSave(charLines, matrixPicture, width, height, numberOfLine, numberOfWord);
    */
    return 0;
}
