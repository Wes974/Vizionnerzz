#include <stdio.h>
#include "segmentation.h"

int main(){
    //WORD//
    unsigned int matrix[3*5] = {0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0};
    /*
    for(unsigned int i = 0;i < 3*5; i++){
        printf("%i\n", matrix[i]);
    }
    */
    unsigned int width = 5;
    unsigned int height = 3;
    unsigned int * list = matrixToList(matrix, height, width);
    unsigned int * wordList =  whatToSave(thresholdDefine(list, width), list, matrix, 3, 3);
    //unsigned int * cutted = cutWord(1, 4, matrix, 5, 3);
    for(unsigned int k = 0;k < width; k++){
        for(unsigned int i = 0; i < height; i++){
            for(unsigned int j = 0; j < width; j++){
                printf("%i, ", wordList[i*width*height+j*height+k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    //printf("\n");
    //for(unsigned int i = 0;i < width;i++){
    //    printf("%i, ", wordList[i]); 
    //}
    
 
    return 0;
}
