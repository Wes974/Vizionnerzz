#include <stdio.h>
#include <stdlib.h>
#include "wordSegmentation.h"
#include "lineSegmentation.h"
#include "charSegmentation.h"
#include <sys/types.h>


int main(){
    unsigned int matrixPicture[3*5] = {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0}; 

    unsigned int width = 5;
    unsigned int height = 3;

    //LINE//
    
    //int result = mkdir("./ocr", 0777);
    //printf("%i", result);
    unsigned int * listLines = matrixToListLine(matrixPicture, height, width);
    unsigned int numberOfLine = lineSave(listLines, matrixPicture, width, height);
    //WORD//

    /*
    for(unsigned int i = 0; i < lineNumber; i++){
        FILE *lineFile;
        char lineFilename[33];
        sprintf(lineFilename, "./data/line_%i/line_%i.txt", i, i);
        lineFile = fopen(lineFilename, "r");
        char matrixLineChar[width * height];
        printf("marche?\n");
        fscanf(lineFile, "%s", matrixLineChar);
        printf("%s\n", matrixLineChar);
        char lineHeightChar [23];
        fscanf(lineFile, "%s", lineHeightChar);

        //unsigned int* matrixLine = (unsigned int *)matrixLineChar;
        //unsigned long size = sizeof(unsigned int);
        //unsigned int matrixLine[width*height];
        //for(unsigned int i = 0; i < width * height; i++){
            //matrixLine[i] = matrixLineChar[i] - 48;
            //matrixLine[i] = atoi(matrixLineChar);
        //}
        unsigned int lineHeight = 0;
        for(unsigned int i = 23; i > 0; i--){
            lineHeight = lineHeight * 10 +lineHeightChar[i];
        }
        //printf("%i\n", matrixLine[0]);
        unsigned int * listWords = matrixToListWord(matrixLineChar, lineHeight, width);
        //unsigned int threshold = thresholdDefine(listWords, width);
        //wordSave(threshold, listWords, matrixLine, width, lineHeight, i);
        fclose(lineFile);  
    }

    */

    //WORD//

    unsigned int * listWord = matrixToListLine(matrixPicture, height, width);
    unsigned int threshold = thresholdDefine(listWord, width);

    unsigned int numberOfWord = wordSave(threshold, listWord, matrixPicture, width, height, numberOfLine);

    //CHAR//
 
    unsigned int * charLines = matrixToListLine(matrixPicture, height, width); 
    unsigned int charNumber = charSave(charLines, matrixPicture, width, height, numberOfLine, numberOfWord);

    printf("%i", charNumber);

    return 0;
}
