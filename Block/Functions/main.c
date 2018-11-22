#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "wordSegmentation.h"
#include "lineSegmentation.h"
#include "charSegmentation.h"
#include <sys/types.h>
#include <errno.h>

int main(){
    //EXAMPLE//
    unsigned int matrixPicture[3*5] = {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0}; 

    unsigned int width = 5;
    unsigned int height = 3;
    
    if(mkdir("./data",0700 && errno != EEXIST)){
        mkdir("./data/", 0700);
    }

    //LINE//
    
    unsigned int * listLines = matrixToListLine(matrixPicture, height, width);
    unsigned int numberOfLine = lineSave(listLines, matrixPicture, width, height);
    //WORD//
    
    for(unsigned int i = 0; i < numberOfLine; i++){
        FILE *lineFile;
        char lineFilename[33];
        sprintf(lineFilename, "./data/line_%i/line_%i.txt", i, i);
        printf("%s\n", lineFilename);
        lineFile = fopen(lineFilename, "r");
        char lineMatrixChar[255];
        fscanf(lineFile, "%s", lineMatrixChar);
        //unsigned int *lineMatrix

        char lineHeight[25];
        fscanf(lineFile, "%s", lineHeight);
        unsigned int lineHeightNumber;
        sscanf(lineHeight, "%d", &lineHeightNumber);

        unsigned int * listWords = matrixToListWord(lineMatrix, lineHeightNumber, width);
        //unsigned int threshold = thresholdDefine(listWords, width);
        //wordSave(threshold, listWords, matrixLine, width, lineHeight, i);
        fclose(lineFile);  
    }

    
    /*
    unsigned int * listWord = matrixToListLine(matrixPicture, height, width);
    unsigned int threshold = thresholdDefine(listWord, width);

    unsigned int numberOfWord = wordSave(threshold, listWord, matrixPicture, width, height, numberOfLine);
    
    //CHAR//
 
    unsigned int * charLines = matrixToListLine(matrixPicture, height, width); 
    unsigned int charNumber = charSave(charLines, matrixPicture, width, height, numberOfLine, numberOfWord);
    */
    return 0;
}
