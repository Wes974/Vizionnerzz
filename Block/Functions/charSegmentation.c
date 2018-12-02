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

    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = pos1; j < pos2; j++){
            fputc(matrix[i*width+j] + 48, fp);
        }
    }
    fprintf(fp, " ");
    width = pos2 - pos1;
    while (width > 0){
        fputc(width % 10 + 48, fp);
        width /= 10;
    }
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

