#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "segmentation.h"
#include "wordSegmentation.h"
#include "lineSegmentation.h"
#include "charSegmentation.h"
#include <sys/types.h>
#include <errno.h>

void segmentation(unsigned int * matrixPicture, unsigned int width, unsigned int height){
    
    system("rm -rf data");
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
        char lineMatrixChar[1920*1080];
        fscanf(lineFile, "%s", lineMatrixChar);

        unsigned int *lineMatrix = calloc(1920*1080, sizeof(unsigned int));
        unsigned int *p = lineMatrix;
        for (unsigned int j = 0; j < 1920*1080; j++){
            *p = lineMatrixChar[j] - 48;
            p++;
        }
        char lineHeight[25];
        fscanf(lineFile, "%s", lineHeight);
        unsigned int lineHeightNumber;
        sscanf(lineHeight, "%d", &lineHeightNumber);
        
        //printf("lineHeight = %u\n", lineHeightNumber);

        printf("Line number %u :\n", i);
        for (unsigned int j = 0; j < lineHeightNumber; j++){
            for (unsigned int k = 0; k < width; k++){
                printf("%u ", lineMatrix[j*width+k]);
            }
            printf("\n");
        }
        //WORD SEGMENTATION
        
        unsigned int * listWordsV1 = matrixToListWord(lineMatrix, lineHeightNumber, width);
        unsigned int threshold = thresholdDefine(listWordsV1, width);
        unsigned int * listWords = matrixWordSpace(listWordsV1, threshold, width);


        printf("Threshold = %u\n\n", threshold);
        unsigned int numberOfWord = wordSave(listWordsV1, lineMatrix, width, lineHeightNumber, i);
        free(lineMatrix);
        
        for(unsigned int j = 0; j < numberOfWord; j++){
            
            //GET MATRIX WORD//
            FILE *wordFile;
            char wordFilename[255];
            sprintf(wordFilename, "./data/line_%i/word_%i/word_%i.txt", i, j, j);
            wordFile = fopen(wordFilename, "r");
            char wordMatrixChar[1920*1080];
            fscanf(wordFile, "%s", wordMatrixChar);
            
            unsigned int *wordMatrix = calloc(1920*1080, sizeof(unsigned int));
            unsigned int *q =wordMatrix;
            for (unsigned int k = 0; k < 1920*1080; k++){
                *q = wordMatrixChar[k] - 48;
                q++;
            }
            char wordWidth[25];
            fscanf(wordFile, "%s", wordWidth);
            unsigned int wordWidthNumber;
            sscanf(wordWidth, "%d", &wordWidthNumber);

            printf("Word number %u \n", j);
            for (unsigned int k = 0; k < lineHeightNumber; k++){
                for (unsigned int l = 0; l < wordWidthNumber; l++){
                    printf("%u ", wordMatrix[k*wordWidthNumber+l]);
                }
                printf("\n");
            }
            
            //CHAR SEGMENTATION
            unsigned int * listChar = matrixToListChar(wordMatrix, lineHeightNumber, wordWidthNumber);

            unsigned int numberOfChar = charSave(listChar, wordMatrix, wordWidthNumber, lineHeightNumber, i, j);
            printf("numberOfChar = %u\n", numberOfChar);
            for (unsigned int k = 0; k < numberOfChar; k++){
                //GET CHAR
                FILE *charFile;
                char charFilename[255];
                sprintf(charFilename, "./data/line_%i/word_%i/char_%i.txt", i, j, k);
                charFile = fopen(charFilename, "r");
                char charMatrixChar[1920*1080];
                fscanf(charFile, "%s", charMatrixChar);
                
                unsigned int *charMatrix = calloc(1920*1080, sizeof(unsigned int));
                unsigned int *q =charMatrix;
                for (unsigned int k = 0; k < 999; k++){
                    *q = charMatrixChar[k] - 48;
                    q++;
                }
                char charWidth[25];
                fscanf(charFile, "%s", charWidth);
                unsigned int charWidthNumber;
                sscanf(charWidth, "%d", &charWidthNumber);

                unsigned int * charMatrixTrim = trim(charMatrix, charWidthNumber, lineHeightNumber);

                printf("Char number %u \n", k);
                for (unsigned int k = 0; k < lineHeightNumber; k++){
                    for (unsigned int l = 0; l < charWidthNumber; l++){
                        printf("%u ", charMatrixTrim[k*charWidthNumber+l]);
                    }
                    printf("\n");
                }

                unsigned int * newCharMatrix = resize(charMatrixTrim, charWidthNumber, lineHeightNumber, 24, 24);
                
                printf("\nChar number %u (Resized)\n", k);
                for (unsigned int k = 0; k < 24; k++){
                    for (unsigned int l = 0; l < 24; l++){
                        printf("%u ", newCharMatrix[k*24+l]);
                    }
                    printf("\n");
                }

                free(charMatrix);
                fclose(charFile);
            }
            free(wordMatrix);
            fclose(wordFile);
            remove(wordFilename);
        }
        fclose(lineFile);
        remove(lineFilename);
        //free(lineMatrix);
        //free(listWords);
        //free(listWordsV1);
        
    }
    free(listLines);
}

