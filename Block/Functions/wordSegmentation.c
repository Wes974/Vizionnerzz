#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "wordSegmentation.h"

unsigned int * matrixToListWord(unsigned int matrix[], unsigned int height, unsigned int width) {             //Convert a 2 dimensional matrix into a 1 dimensional List.
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

unsigned int thresholdDefine(unsigned int list[], unsigned int width){                  //Find the threshold between the space between characters and the space between words.
    unsigned int num = 0;
    unsigned int denum = 0;
    unsigned int prevBlack = 0;
    for(unsigned int i = 1; i < width; i++){
        if(list[i] == 0){
            num++;
            if(prevBlack){
                denum++;
            }
            prevBlack = 0;
        }
        else{
            prevBlack = 1;
        
        }
    }
    return num/denum;                                               //return the average between the number of white pixels and the number of spaces to find the 
                                                                    //average space size.
}

void cutWord(unsigned int pos1, unsigned int pos2, unsigned int matrix[], unsigned int width, unsigned int height, unsigned int numberOfWord, unsigned int lineNumber){             //use the position of the begining and the ned of a word and
                                                                                                    //return the word (a matrix)
    
    FILE *fp;
    char filename[292];
    sprintf(filename, "./data/line_%i/word_%i/word_%i.txt", lineNumber, numberOfWord, numberOfWord);
    fp = fopen(filename, "w");

    if(fp == NULL){
        char directoryName[292];
        sprintf(directoryName, "./data/line_%i/word_%i/", lineNumber, numberOfWord);
        mkdir(directoryName, 0700);
        fp = fopen(filename, "w");
    }

    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = pos1; j < pos2; j++){
            fputc(matrix[i*width+j] + 48, fp);
        }
    }
    fprintf(fp, " ");
    while (width > 0){
        fputc(width % 10 + 48, fp);
        width /= 10;
    } 
    fclose(fp);
    
}

unsigned int wordSave(unsigned int threshold, unsigned int list[], unsigned int matrix[], unsigned int width, unsigned int height, unsigned int lineNumber){
    unsigned int pos1 = -1;
    unsigned int pos2 = 0;
    unsigned int inAWord = 0;
    unsigned int numberOfWords = 0;
    for(unsigned int k = 0; k < width; k++){
        
        if(list[k] == 1){
            inAWord = 1;
            pos2 = k;
        }
        
        if(list[k] == 0 && inAWord && pos2 - pos1 >= threshold){
            cutWord(pos1 + 1, pos2 + 1, matrix, width, height, numberOfWords, lineNumber);
            numberOfWords++;
            pos1 = k;
        }
        else if(list[k] == 0){
            pos1 = k;
            inAWord = 0;
        }
    }
    return numberOfWords;
}

