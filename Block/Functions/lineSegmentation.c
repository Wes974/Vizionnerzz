#include "lineSegmentation.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

unsigned int * matrixToListLine(unsigned int matrix[], unsigned int height, unsigned int width) {             //Convert a 2 dimensional matrix into a 1 dimensional List.

    unsigned int *list = calloc(width, sizeof(unsigned int));
    for(unsigned int j = 0; j < height; j++){
        unsigned int value = 0;
        for (unsigned int i = 0; i < width; i++){
            if(matrix[j*height+i] == 1){                                  //If the line contain at least 1 black pixel, the corresponding position in the list is black.
                value = 1;
            }
        }
        list[j] = value;
    }
    
    return list;
}

void cutLine(unsigned int pos1, unsigned int pos2, unsigned int matrix[], unsigned int width, unsigned int height, unsigned int numberOfLine){             //use the position of the begining and the ned of a line and
                                                                                                    //return the line (a matrix)
    FILE *fp;                           //Find the line matrix in data/line_number/line_number.txt
    char filename[49];
    sprintf(filename, "./data/line_%i/line_%i.txt", numberOfLine, numberOfLine);
    fp = fopen(filename, "w");
    if(fp == NULL){
        char directoryName[33];
        sprintf(directoryName, "./data/line_%i/", numberOfLine);
        mkdir(directoryName, 0700);
    }
    for(unsigned int i = pos1;i < pos2; i++){
        for(unsigned int j = 0; j < width; j++){
            fputc(matrix[i*width+j] + 48, fp);
        }
    }
    fprintf(fp, " ");
    while (height > 0){
        fputc(height % 10 + 48, fp);
        height /= 10;
    }
    fclose(fp);
}


unsigned int lineSave(unsigned int list[], unsigned int matrix[], unsigned int width, unsigned int height){    //find the positions between the begining and the end of a 
                                                                                                    //line and call the cut function to return every line in corresponding directories.
    unsigned int pos1 = -1;
    unsigned int pos2 = 0;
    unsigned int inALine = 0;
    unsigned int numberOfLine = 0;
    for(unsigned int k = 0; k < height; k++){
        
        if(list[k] == 1){
            inALine = 1;
            pos2 = k;
        }
        
        if(list[k] == 0 && inALine){
            cutLine(pos1 + 1, pos2 + 1, matrix, width, height, numberOfLine);
            numberOfLine++;
            pos1 = k;
        }
        else if(list[k] == 0){
            pos1 = k;
            inALine = 0;
        }
    }
    if(inALine){
        cutLine(pos1 + 1, pos2 + 1, matrix, width, height, numberOfLine);
        numberOfLine++;
    }
    return numberOfLine;
}

