#include "charSegmentation.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

unsigned int * matrixToListChar(unsigned int matrix[], unsigned int height, unsigned int width) {             //Convert a 2 dimensional matrix into a 1 dimensional List.

    unsigned int *list = calloc(width, sizeof(unsigned int));
    for(unsigned int j = 0; j < height; j++){
        unsigned int value = 0;
        for (unsigned int i = 0; i < width; i++){
            if(matrix[j*height+i] == 1){                                  //If the column contain at least 1 black pixel, the corresponding position in the list is black.
                value = 1;
            }
        }
        list[j] = value;
    }
    
    return list;
}

void cutChar(unsigned int pos1, unsigned int pos2, unsigned int matrix[], unsigned int width, unsigned int height, unsigned int numberOfLine, unsigned int numberOfWord, unsigned int numberOfChar){             //use the position of the begining and the ned of a word and
                                                                                                    //return the word (a matrix)
    FILE *fp;
    char filename[49];
    sprintf(filename, "./data/line_%i/word_%i/char_%i.txt", numberOfLine, numberOfWord, numberOfChar);
    fp = fopen(filename, "w");
    if(fp == NULL){
        printf("nottt");
        char directoryName[33];
        sprintf(directoryName, "./data/line_%i/word_%i/", numberOfLine, numberOfWord);
        mkdir(directoryName, 0700);
    }
    for(unsigned int i = 0;i < height; i++){
        for(unsigned int j = pos1; j < pos2; j++){
            fputc(matrix[i*width+j] + 48, fp);
        }
        //fprintf(fp, "\n");
    }
    fprintf(fp, " ");
    while (height > 0){
        fputc(height % 10 + 48, fp);
        height /= 10;
    }
    fclose(fp);
}


unsigned int charSave(unsigned int list[], unsigned int matrix[], unsigned int width, unsigned int height, unsigned int numberOfLine, unsigned int numberOfWord){    //find the positions between the begining and the end of a 
                                                                                                    //word and call the cut function to return the list containing
                                                                                                    //all the word.
    unsigned int pos1 = -1;
    unsigned int pos2 = 0;
    unsigned int inAChar = 0;
    unsigned int numberOfChar = 0;
    for(unsigned int k = 0; k < width; k++){
        
        if(list[k] == 1){
            inAChar = 1;
            pos2 = k;
        }
        
        if(list[k] == 0 && inAChar){
            cutChar(pos1 + 1, pos2 + 1, matrix, width, height, numberOfLine, numberOfWord, numberOfChar);
            numberOfChar++;
            pos1 = k;
        }
        else if(list[k] == 0){
            pos1 = k;
            inAChar = 0;
        }
    }
    if(inAChar){
        cutChar(pos1 + 1, pos2 + 1, matrix, width, height, numberOfLine, numberOfWord, numberOfChar);
        numberOfChar++;
    }
    return numberOfChar;
}

