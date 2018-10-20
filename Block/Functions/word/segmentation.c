#include <stdlib.h>
#include <stdio.h>
//#include "segmentation.h"

unsigned int * matrixToList(unsigned int matrix[], unsigned int height, unsigned int width) {             //Convert a 2 dimensional matrix into a 1 dimensional List.

    unsigned int *list = calloc(width, sizeof(unsigned int));
    for(unsigned int j = 0; j < width; j++){
        unsigned int value = 0;
        for (unsigned int i = 0; i < height; i++){
            if(matrix[i*width+j] == 1){                                  //If the column contain at least 1 black pixel, the corresponding position in the list is black.
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
    printf("numerateur : %i\n", num);
    return num/denum;                                               //return the average between the number of white pixels and the number of spaces to find the 
                                                                    //average space size.
}

unsigned int * cutWord(unsigned int pos1, unsigned int pos2, unsigned int matrix[], unsigned int width, unsigned int height){             //use the position of the begining and the ned of a word and
                                                                                                    //return the word (a matrix)
    unsigned int *word = calloc(height * (pos2-pos1), sizeof(unsigned int));
    for(unsigned int j = 0;j < width;j++){
        for(unsigned int i = 0; i < pos2; i++){
            word[i*width+j] = (unsigned int)(matrix[i*width+j+pos1]);
        }
    }
    return word;
}


unsigned int * whatToSave(unsigned int threshold, unsigned int list[], unsigned int matrix[], unsigned int width, unsigned int height){    //find the positions between the begining and the end of a 
                                                                                                    //word and call the cut function to return the list containing
                                                                                                    //all the word.
    unsigned int pos1 = 0;
    unsigned int pos2 = 0;
    unsigned int inAWord = 1;
    unsigned int *words = calloc(width, sizeof(unsigned int *));
    unsigned int numberOfWords = 0;
    for(unsigned int i = 0; i < width; i++){
        //unsigned int *toCopy = calloc(pos2*height, sizeof(unsigned int*));
        if(list[i] == 1){
            inAWord = 1;
            pos2 = i;
        }
        if(list[i] == 0 && inAWord){
            if(pos2 - pos1 > threshold){
                for(unsigned int j = 0; j < width; j++){
                    for(unsigned int i = 0; i < height; i++){
                        words[i*width*height+j*height+numberOfWords] = cutWord(pos1, pos2, matrix, width, height)[i*width+j];
                    }
                }
                numberOfWords++;
                
            }
        }
        if(list[i] == 0){
            pos1 = i;
            inAWord = 0;
        }
    }
    //desalloc
    return words;
}


