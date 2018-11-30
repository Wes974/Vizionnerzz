#include "charSegmentation.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

unsigned int *matrixToListChar(unsigned int matrix[], unsigned int height, unsigned int width)
{
    unsigned int *list = calloc(width, sizeof(unsigned int));
    for (unsigned int j = 0; j < width; j++)
    {
        unsigned int value = 0;
        for (unsigned int i = 0; i < height; i++)
        {
            if (matrix[i * width + j] == 1)
            {
                value = 1;
            }
        }
        list[j] = value;
    }
    return list;
}

unsigned int *matrixToListCharTransposed(unsigned int matrix[], unsigned int height, unsigned int width)
{
    unsigned int *list = calloc(height, sizeof(unsigned int));
    for (unsigned int i = 0; i < height; i++)
    {
        unsigned int value = 0;
        for (unsigned int j = 0; j < width; j++)
        {
            if (matrix[i * width + j] == 1)
            {
                value = 1;
            }
        }
        list[i] = value;
    }
    return list;
}

unsigned int *resize(unsigned int *matrix, unsigned int width, unsigned int height, unsigned int newWidth, unsigned int newHeight)
{
    unsigned int *newMatrix = calloc(width * height, sizeof(unsigned int));
    float ratioX = (float)width / (float)newWidth;
    float ratioY = (float)height / (float)newHeight;
    unsigned int in = 0;
    unsigned int jn = 0;

    for (float i = 0; i < width && in < newWidth; i += ratioX)
    {
        jn = 0;
        for (float j = 0; j < height && jn < newHeight; j += ratioY)
        {
            newMatrix[jn * newWidth + in] = matrix[(int)j * width + (int)i];
            jn++;
        }
        in++;
    }
    return newMatrix;
}

void cutChar(unsigned int pos1, unsigned int pos2, unsigned int matrix[], unsigned int width, unsigned int height, unsigned int numberOfLine, unsigned int numberOfWord, unsigned int numberOfChar)
{
    unsigned int *newMatrix = calloc(width * height, sizeof(unsigned int));
    FILE *fp;
    char filename[292];
    sprintf(filename, "./data/line_%i/word_%i/char_%i.txt", numberOfLine, numberOfWord, numberOfChar);
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        char directoryName[292];
        sprintf(directoryName, "./data/line_%i/word_%i/", numberOfLine, numberOfWord);
        mkdir(directoryName, 0700);
        fp = fopen(filename, "w");
    }

    //printf("width = %u\n", pos2 - pos1);
    for (unsigned int i = 0; i < height; i++)
    {
        for (unsigned int j = pos1, jn = 0; j < pos2 && jn < pos2 - pos1; j++)
        {
            newMatrix[i * width + jn] = matrix[i * width + j];
            jn++;
        }
    }
    printf("width = %u, height = %u\n", pos2-pos1, height);
    unsigned int *newHeight = &height;
    unsigned int *realNewMatrix = trim(newMatrix, width, newHeight);
    for (unsigned int i = 0; i < *newHeight; i++)
    {
        for (unsigned int j = 0; j < pos2 - pos1; j++)
        {
            fputc(realNewMatrix[i * width + j] + 48, fp);
        }
    }
    printf("Char number %u \n", 0);
    for (unsigned int k = 0; k < *newHeight; k++)
    {
        for (unsigned int l = 0; l < pos2 - pos1; l++)
        {
            printf("%u ", realNewMatrix[k * width + l]);
        }
        printf("\n");
    }

    //Add width in the file
    fprintf(fp, " ");
    width = pos2 - pos1;
    unsigned int nb = 0;
    while (width > 0)
    {
        width /= 10;
        nb++;
    }
    width = pos2 - pos1;
    while (nb > 1)
    {
        fputc(width / ((nb - 1) * 10) + 48, fp);
        width %= 10;
        nb--;
    }
    fputc(width % 10 + 48, fp);

    //Add height in the file
    fprintf(fp, " ");
    unsigned int newNewHeight = *newHeight;
    nb = 0;
    while (newNewHeight > 0)
    {
        newNewHeight /= 10;
        nb++;
    }
    newNewHeight = *newHeight;
    while (nb > 1)
    {
        fputc(newNewHeight / ((nb - 1) * 10) + 48, fp);
        newNewHeight %= 10;
        nb--;
    }
    fputc(width % 10 + 48, fp);

    fclose(fp);
}

unsigned int charSave(unsigned int list[], unsigned int matrix[], unsigned int width, unsigned int height, unsigned int numberOfLine, unsigned int numberOfWord)
{
    unsigned int pos1 = 0;
    unsigned int pos2 = 1;
    unsigned int inAChar = 0;
    unsigned int numberOfChar = 0;

    for (unsigned int k = 0; k < width; k++)
    {
        if (list[k] == 1 && !inAChar)
        {
            inAChar = 1;
            pos1 = k;
        }
        else if (list[k] == 1)
        {
            inAChar = 1;
            pos2 = k;
        }

        else if (list[k] == 0 && inAChar)
        {
            pos2 = k;
            cutChar(pos1, pos2, matrix, width, height, numberOfLine, numberOfWord, numberOfChar);
            numberOfChar++;
            inAChar = 0;
        }
        else if (list[k] == 0)
        {
            inAChar = 0;
        }
    }
    if (inAChar)
    {
        cutChar(pos1, width, matrix, width, height, numberOfLine, numberOfWord, numberOfChar);
        numberOfChar++;
    }
    return numberOfChar;
}

unsigned int *trim(unsigned int *matrix, unsigned int width, unsigned int *height)
{
    unsigned int *yList = matrixToListCharTransposed(matrix, *height, width);
    unsigned int *newMatrix = calloc(width * (*height), sizeof(unsigned int));
    unsigned int in = 0;
    for (unsigned int i = 0; i < *height; i++)
    {
        if (yList[i] == 1)
        {
            for (unsigned int j = 0; j < width; j++)
            {
                newMatrix[in * width + j] = matrix[i * width + j];
            }
            in++;
        }
    }
    //printf("in = %u\n", in);
    unsigned int *realNewMatrix = calloc(width * in, sizeof(unsigned int));
    for (unsigned i = 0; i < in; i++)
    {
        for (unsigned int j = 0; j < width; j++)
        {
            realNewMatrix[i * width + j] = newMatrix[i * width + j];
        }
    }
    *height = in;
    return realNewMatrix;
}
