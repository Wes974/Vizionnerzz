#include <stdio.h>
#include "word/segmentation.h"

int main(){
    //WORD//
    unsigned int matrix[3*3] = {0, 1, 0, 0, 1, 0, 0, 1, 0};
    unsigned int * list = matrixToList(matrix, 3, 3);
    for(int i = 0;i < 3;i++){
        printf("%i, ", list[i]);
    }
    //unsigned int wordList[][] =  whatToSave(thresholdDefine(list), list, matrix);
     
    return 0;
}
