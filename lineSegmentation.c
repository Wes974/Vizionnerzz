#include "lineSegmentation.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <math.h>

//Get the corresponding list according to the line currently analysed
unsigned int * matrixToListLine(unsigned int matrix[], unsigned int height, 
                                                        unsigned int width) {
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

//Save the line to the corresponding path with pos1 and pos2 being the begining and the end of the line
void cutLine(unsigned int pos1, unsigned int pos2, unsigned int matrix[], 
            unsigned int width, unsigned int height, unsigned int numberOfLine){

    FILE *fp;
    char filename[22 + 10];
    sprintf(filename, "./data/line_%i/line_%i.txt", numberOfLine, numberOfLine);

    fp = fopen(filename, "w");
    char directoryName[13+3];
    sprintf(directoryName, "./data/line_%i/", numberOfLine);

    if(!mkdir(directoryName, S_IRUSR | S_IWUSR | S_IXUSR)){
        mkdir(directoryName, S_IRWXO);
        fp = fopen(filename, "w");
    }

    //printf("pos 1 = %u\npos2 = %u", pos1, pos2);
    for(unsigned int i = pos1; i <= pos2; i++){
        for(unsigned int j = 0; j < width; j++){
            fputc(matrix[i*width+j] + 48, fp);
        }
    }
    fprintf(fp, " ");
    height = pos2 - pos1;
    //printf("height = %u\n", height);
    unsigned int nb = 0;
    while (height > 0){
        height /= 10;
        nb++;
    }
    height = pos2 - pos1;
    while (nb > 1){
        fputc(height / (unsigned int)powl(10, (nb - 1)) + 48, fp);
        height %= (unsigned int)powl(10, (nb - 1));
        nb--;
    }
    fputc(height % 10 + 48, fp);
    fclose(fp);
}

//Find the coordinates of the diiferents line in the image
unsigned int lineSave(unsigned int list[], unsigned int matrix[], 
                                    unsigned int width, unsigned int height){
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

