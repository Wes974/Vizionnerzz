#include "charSegmentation.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

unsigned int * matrixToListChar(unsigned int matrix[], unsigned int height, unsigned int width) {
    unsigned int *list = calloc(width, sizeof(unsigned int));
    for(unsigned int j = 0; j < width; j++){
        unsigned int value = 0;
        for (unsigned int i = 0; i < height; i++){
            if(matrix[i*width+j] == 1){
                value = 1;
            }
        }
        list[j] = value;
    }
    return list;
}

unsigned int * matrixToListCharTransposed(unsigned int matrix[], unsigned int height, unsigned int width) {
    unsigned int *list = calloc(height, sizeof(unsigned int));
    for(unsigned int i = 0; i < height; i++){
        unsigned int value = 0;
        for (unsigned int j = 0; j < width; j++){
            if(matrix[i*width+j] == 1){
                value = 1;
            }
        }
        list[i] = value;
    }
    return list;
}

unsigned int * resize(unsigned int * matrix, unsigned int width, unsigned int height, unsigned int newWidth, unsigned int newHeight){
    unsigned int * newMatrix = calloc(width * height, sizeof(unsigned int));
    float ratioX = (float) width / (float)newWidth;
    float ratioY = (float) height / (float)newHeight;
    unsigned int in = 0;
    unsigned int jn = 0;

    for (float i = 0; i < width && in < newWidth; i+=ratioX){
        jn = 0;
        for (float j = 0; j < height && jn < newHeight; j+=ratioY){
            newMatrix[in*newWidth+jn] = matrix[(int)i*width+(int)j];
            jn++;
        }
        in++;
    }
    return newMatrix;
}

void cutChar(unsigned int pos1, unsigned int pos2, unsigned int matrix[], unsigned int width, unsigned int height, unsigned int numberOfLine, unsigned int numberOfWord, unsigned int numberOfChar){

    FILE *fp;
    char filename[292];
    sprintf(filename, "./data/line_%i/word_%i/char_%i.txt", numberOfLine, numberOfWord, numberOfChar);
    fp = fopen(filename, "w");
    if(fp == NULL){
        char directoryName[292];
        sprintf(directoryName, "./data/line_%i/word_%i/", numberOfLine, numberOfWord);
        mkdir(directoryName, 0700);
        fp = fopen(filename, "w");
    }

    //unsigned int * matrixResized = resize(matrix, width, height, 24, 24);

    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = pos1; j < pos2; j++){
            fputc(matrix[i*width+j] + 48, fp);
        }
    }
    //Add width in the file
    fprintf(fp, " ");
    width = pos2 - pos1;
    while (width > 0){
        fputc(width % 10 + 48, fp);
        width /= 10;
    }
    /*
    //Add height in the file
    fprintf(fp, " ");
    while (height > 0){
        fputc(height % 10 + 48, fp);
        height /= 10;
    }
    */
    fclose(fp);
}


unsigned int charSave(unsigned int list[], unsigned int matrix[], unsigned int width, unsigned int height, unsigned int numberOfLine, unsigned int numberOfWord){
    unsigned int pos1 = 0;
    unsigned int pos2 = 1;
    unsigned int inAChar = 0;
    unsigned int numberOfChar = 0;

    for(unsigned int k = 0; k < width; k++){
        if(list[k] == 1 && !inAChar){
            inAChar = 1;
            pos1 = k;
        }
        else if(list[k] == 1){
            inAChar = 1;
            pos2 = k;
        }

        else if (list[k] == 0 && inAChar){
            pos2 = k;
            cutChar(pos1, pos2, matrix, width, height, numberOfLine, numberOfWord, numberOfChar);
            numberOfChar++;
            inAChar = 0;
        }
        else if(list[k] == 0){
            inAChar = 0;
        }
    }
    if(inAChar){
        cutChar(pos1, width, matrix, width, height, numberOfLine, numberOfWord, numberOfChar);
        numberOfChar++;
    }
    return numberOfChar;
}

unsigned int * trim(unsigned int *matrix, unsigned int width, unsigned int height){
    unsigned int * newMatrix = calloc(width * height, sizeof(unsigned int));
    unsigned int * xList = matrixToListChar(matrix, width, height);
    unsigned int * yList = matrixToListCharTransposed(matrix, width, height);
    unsigned int in = 0;
    unsigned int jn = 0;
    printf("list :\n");
    for (unsigned int i = 0; i < width; i++)
        printf("%u, ", yList[i]);
    printf("\n");
    for (unsigned int i = 0; i < height; i++){
        if(yList[i] == 1){
            for (unsigned int j = 0; j < width; j++){
                if(xList[j] == 1){
                    newMatrix[i*width+j] = matrix[i*width+j];
                    jn++;
                }
            }
            in++;
        }
    }
    return newMatrix;
}
