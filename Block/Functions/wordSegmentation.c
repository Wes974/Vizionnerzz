#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "wordSegmentation.h"

unsigned int * matrixToListWord(unsigned int matrix[], unsigned int height, unsigned int width) {             //Convert a 2 dimensional matrix into a 1 dimensional List.
    unsigned int size = sizeof(unsigned int);
    unsigned int *list = calloc(width, size);
    for(unsigned int j = 0; j < width; j++){
        unsigned int value = 0;
        for (unsigned int i = 0; i < height; i++){
            if(matrix[i*width+j] == 1){   //If the column contain at least 1 black pixel, the corresponding position in the list is black.
            //if(matrix[0] == 1){
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
    char filename[49];
    sprintf(filename, "./data/line_%i/word_%i/word_%i.txt", lineNumber, numberOfWord, numberOfWord);
    fp = fopen(filename, "w");
    if(fp == NULL){
        char directoryName[49];
        sprintf(directoryName, "./data/line_%i/word_%i/", lineNumber, numberOfWord);
        mkdir(directoryName, 0700);
    }
    for(unsigned int i = pos1;i < pos2; i++){
        for(unsigned int j = 0; j < height; j++){
            fputc(matrix[i*height+j] + 48, fp);
        }
        //fprintf(fp, "\n");
    }
    fprintf(fp, " ");
    while (width > 0){
        fputc(width % 10 + 48, fp);
        width /= 10;
    } 
    fclose(fp);
}

unsigned int wordSave(unsigned int threshold, unsigned int list[], unsigned int matrix[], unsigned int width, unsigned int height, unsigned int lineNumber){    //find the positions between the begining and the end of a 
                                                                                                    //word and call the cut function to return the list containing
                                                                                                    //all the word.
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

