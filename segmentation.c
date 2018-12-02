#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "segmentation.h"
#include "wordSegmentation.h"
#include "lineSegmentation.h"
#include "charSegmentation.h"
#include <errno.h>
#include <math.h>

void putIntInAFile(FILE *file, unsigned int number){
    unsigned int temp = number;
    unsigned int nb = 0;
    while (temp > 0)
    {
        temp /= 10;
        nb++;
    }
    temp = number;
    while (nb > 1)
    {
        fputc(temp / (unsigned int)powl(10, (nb - 1)) + 48, file);
        temp %= (unsigned int)powl(10, (nb - 1));
        nb--;
    }
    fputc(temp % 10 + 48, file);
}

void segmentation(unsigned int *matrixPicture, unsigned int width, unsigned int height, unsigned int superUser)
{
    printf("su = %u", superUser);
    system("rm -rf data");
    if (!mkdir("./data", S_IRUSR | S_IWUSR | S_IXUSR))
    {
        mkdir("./data/", S_IRUSR | S_IWUSR | S_IXUSR);
    }

    /*
    printf("Original Image :\n");
    //unsigned int * height2 = &height;
    //unsigned int *matrixPictureNew = trim(matrixPicture, width, height2);
    for (unsigned int i = 0; i < height; i++)
    {
        for (unsigned int j = 0; j < width; j++)
        {
            printf("%u", matrixPicture[i * width + j]);
        }
        printf("\n");
    }
    printf("\n");
    */
    unsigned int totalChar = 0;

    //LINE//

    unsigned int *listLines = matrixToListLine(matrixPicture, height, width);
    unsigned int numberOfLine = lineSave(listLines, matrixPicture, width, height);
    free(listLines);

    //Put the number of line in line_intfo.txt
    FILE *line_info;
    line_info = fopen("./data/line_info.txt", "w");
    putIntInAFile(line_info, numberOfLine);
    fclose(line_info);

    //WORD//
    for (unsigned int i = 0; i < numberOfLine; i++)
    {

        //GET MATRIX LINE//
        FILE *lineFile;
        char lineFilename[22+5];
        sprintf(lineFilename, "./data/line_%i/line_%i.txt", i, i);
        lineFile = fopen(lineFilename, "r");

        char lineMatrixChar[500*500+1];
        fscanf(lineFile, "%s", lineMatrixChar);

        unsigned int *lineMatrix = calloc(500*500, sizeof(unsigned int));
        unsigned int *p = lineMatrix;
        for (unsigned int j = 0; j < 500*500; j++)
        {
            *p = lineMatrixChar[j] - 48;
            p++;
        }
        //free(p);

        char lineHeight[4];
        fscanf(lineFile, "%s", lineHeight);
        unsigned int lineHeightNumber;
        sscanf(lineHeight, "%d", &lineHeightNumber);

        fclose(lineFile);
        remove(lineFilename);

        //printf("lineHeight = %u\n", lineHeightNumber);

        //WORD SEGMENTATION

        //unsigned int *newWidth = &width;
        //unsigned int *lineMatrixTrimmed = trimVertical(lineMatrix, newWidth, height);
        //free(lineMatrix);

        /*
        printf("Line number %u :\n", i);
        for (unsigned int j = 0; j < lineHeightNumber; j++)
        {
            for (unsigned int k = 0; k < width; k++)
            {
                printf("%u", lineMatrix[j * width + k]);
            }
            printf("\n");
        }
        */
        unsigned int *listWordsV1 = matrixToListWord(lineMatrix, lineHeightNumber, width);
        unsigned int threshold = thresholdDefine(listWordsV1, width);
        unsigned int *listWords = matrixWordSpace(listWordsV1, threshold, width);

        
        //free(listWordsV1);
        //printf("\n");

        //printf("Threshold = %u\n\n", threshold);
        unsigned int numberOfWord = wordSave(listWords, lineMatrix, width, lineHeightNumber, i);
        
        FILE *word_info;
        char wordFilename[28+4+1];
        sprintf(wordFilename, "./data/line_%i/word_info.txt", i);
        word_info = fopen(wordFilename, "w");
        putIntInAFile(word_info, numberOfWord);
        fclose(word_info);

        /*
        for (unsigned int word = 0; word < width; word++)
            printf("%u", listWordsV1[word]);
        printf("\n");
        for (unsigned int word = 0; word < width; word++)
            printf("%u", listWords[word]);
        printf("\n");
        */
        free(lineMatrix);
        free(listWords);

        for (unsigned int j = 0; j < numberOfWord; j++)
        {

            //GET MATRIX WORD//
            FILE *wordFile;
            char wordFilename[28+10+1];
            sprintf(wordFilename, "./data/line_%i/word_%i/word_%i.txt", i, j, j);
            wordFile = fopen(wordFilename, "r");
            char wordMatrixChar[250*500+1];
            fscanf(wordFile, "%s", wordMatrixChar);

            unsigned int *wordMatrix = calloc(250*500, sizeof(unsigned int));
            unsigned int *q = wordMatrix;
            for (unsigned int k = 0; k < 250*500; k++)
            {
                *q = wordMatrixChar[k] - 48;
                q++;
            }
            //free(q);

            char wordWidth[3+1];
            fscanf(wordFile, "%s", wordWidth);
            fclose(wordFile);
            remove(wordFilename);
            unsigned int wordWidthNumber;
            sscanf(wordWidth, "%d", &wordWidthNumber);
            /*
            printf("Word number %u \n", j);
            for (unsigned int k = 0; k < lineHeightNumber; k++)
            {
                for (unsigned int l = 0; l < wordWidthNumber; l++)
                {
                    printf("%u", wordMatrix[k * wordWidthNumber + l]);
                }
                printf("\n");
            }
            */
            //CHAR SEGMENTATION
            
            unsigned int *listChar = matrixToListChar(wordMatrix, lineHeightNumber, wordWidthNumber);

            unsigned int numberOfChar = charSave(listChar, wordMatrix, wordWidthNumber, lineHeightNumber, i, j, 10, 10);

            FILE *char_info;
            char charFilename[32+10+1];
            sprintf(charFilename, "./data/line_%i/word_%i/char_info.txt", i, j);
            char_info = fopen(charFilename, "w");
            putIntInAFile(char_info, numberOfChar);
            fclose(char_info);
            free(wordMatrix);
            free(listChar);
            //printf("numberOfChar = %u\n", numberOfChar);
            
            //UNECESSARY
            for (unsigned int k = 0; k < numberOfChar; k++)
            {
                totalChar++;
                //GET CHAR
                FILE *charFile;
                char charFilename[28+10+1];
                sprintf(charFilename, "./data/line_%i/word_%i/char_%i.txt", i, j, k);
                charFile = fopen(charFilename, "r");

                char charMatrixChar[250*500+1];
                fscanf(charFile, "%s", charMatrixChar);

                unsigned int *charMatrix = calloc(250*500, sizeof(unsigned int));
                unsigned int *r = charMatrix;
                for (unsigned int k = 0; k < 250*500; k++)
                {
                    *r = charMatrixChar[k] - 48;
                    r++;
                }
                //free(r);

                char charWidth[3+1];
                fscanf(charFile, "%s", charWidth);
                unsigned int charWidthNumber;
                sscanf(charWidth, "%d", &charWidthNumber);


                char charHeight[3+1];
                fscanf(charFile, "%s", charHeight);
                fclose(charFile);
                unsigned int charHeightNumber;
                sscanf(charHeight, "%d", &charHeightNumber);

                //printf("height = %u, width = %u\n", charHeightNumber, charWidthNumber);

                if (1){
                    printf("\nLine number : %u\nWord number : %u\nChar number : %u\n", i, j, k);
                    for (unsigned int k = 0; k < charHeightNumber; k++)
                    {
                        for (unsigned int l = 0; l < charWidthNumber; l++)
                        {
                            printf("%u", charMatrix[k * charWidthNumber + l]);
                        }
                        printf("\n");
                    }
                }
                
                //unsigned int * charMatrixTrim = trim(charMatrix, charWidthNumber, &charHeightNumber);
                
                //unsigned int * newCharMatrix = resize(charMatrix, charWidthNumber, charHeightNumber, 10, 10);
                free(charMatrix);                
                /*
                printf("\nChar number %u (Resized)\n", k);
                for (unsigned int k = 0; k < 10; k++){
                    for (unsigned int l = 0; l < 10; l++){
                        printf("%u", newCharMatrix[k*10+l]);
                    }
                    printf("\n");
                }
                free(newCharMatrix);
                */
            }
            
        }
    }
    //printf("total = %u", totalChar);
}
