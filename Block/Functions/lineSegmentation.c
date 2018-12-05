#include "lineSegmentation.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

unsigned int * matrixToListLine(unsigned int matrix[], unsigned int height, unsigned int width) {
    unsigned int *list = calloc(width, sizeof(unsigned int));

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

void cutLine(unsigned int pos1, unsigned int pos2, unsigned int matrix[], unsigned int width, unsigned int height, unsigned int numberOfLine){

    FILE *fp;
    char filename[292];
    sprintf(filename, "./data/line_%i/line_%i.txt", numberOfLine, numberOfLine);

    fp = fopen(filename, "w");

    if(fp == NULL){
        char directoryname[292];
        sprintf(directoryname, "./data/line_%i/", numberOfLine);
        mkdir(directoryname, 0700);
        fp = fopen(filename, "w");
    }

    for(unsigned int i = pos1; i < pos2; i++){
        for(unsigned int j = 0; j < width; j++){
            fputc(matrix[i*width+j] + 48, fp);
        }
    }
    fprintf(fp, " ");
    height = pos2 - pos1;
    while (height > 0){
        fputc(height % 10 + 48, fp);
        height /= 10;
    }
    fclose(fp);
}


unsigned int lineSave(unsigned int list[], unsigned int matrix[], unsigned int width, unsigned int height){
    unsigned int pos1 = 0;
    unsigned int pos2 = 1;
    unsigned int inALine = 0;
    unsigned int numberOfLine = 0;
    
    for(unsigned int k = 0; k < height; k++){
        if(list[k] == 1 && !inALine){
            inALine = 1;
            pos1 = k;
        }
        else if(list[k] == 1){
            inALine = 1;
            pos2 = k;
        }
        
        else if(list[k] == 0 && inALine){
            pos2 = k;
            //printf("cultine : %u, %u\n", pos1, pos2);
            cutLine(pos1, pos2, matrix, width, height, numberOfLine);
            numberOfLine++;
            inALine = 0;
        }
        else if(list[k] == 0){
            inALine = 0;
        }
    }
    if(inALine){
        //printf("cultine : %u, %u\n", pos1, pos2);
        cutLine(pos1, height, matrix, width, height, numberOfLine);
        numberOfLine++;
    }
    return numberOfLine;
}

