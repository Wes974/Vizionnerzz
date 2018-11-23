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
        for (unsigned int i = 0; i < lineHeightNumber; i++){
            for (unsigned int j = 0; j < width; j++){
                printf("%u ", lineMatrix[i*width+j]);
            }
            printf("\n");
        }

        unsigned int * listWords = matrixToListWord(lineMatrix, lineHeightNumber, width);

        printf("\n");
        for (unsigned int j = 0; j < width; j++){
            printf("%u ", listWords[j]);
        }
        printf("\n");
        unsigned int threshold = thresholdDefine(listWords, width);
        printf("Threshold = %u\n", threshold);
        wordSave(threshold, listWords, lineMatrix, width, lineHeightNumber, i);
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
