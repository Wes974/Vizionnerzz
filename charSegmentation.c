#include "charSegmentation.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <math.h>

//Get the corresponding list according to the character currently analysed
unsigned int *matrixToListChar(unsigned int matrix[], unsigned int height, 
                                                            unsigned int width)
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

//Same than before but with the y axis
unsigned int *matrixToListCharTransposed(unsigned int matrix[], 
                                    unsigned int height, unsigned int width)
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

//Resize the given matrix to the corresponding lengths
unsigned int *resize(unsigned int *matrix, unsigned int width, 
            unsigned int height, unsigned int newWidth, unsigned int newHeight)
{
    unsigned int *newMatrix = calloc(newWidth * newHeight, 
                                                        sizeof(unsigned int));
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

//Save the char to the corresponding path with pos1 and pos2 being the begining and the end of the char
void cutChar(unsigned int pos1, unsigned int pos2, unsigned int matrix[], 
    unsigned int width, unsigned int height, unsigned int numberOfLine, 
        unsigned int numberOfWord, unsigned int numberOfChar, 
            unsigned int newWidth, unsigned int newHeight)
{
    unsigned int *newMatrix = calloc(width * height, sizeof(unsigned int));

    FILE *fp;
    char filename[28+10+1];
    sprintf(filename, "./data/line_%i/word_%i/char_%i.txt", numberOfLine, 
                                                    numberOfWord, numberOfChar);
    fp = fopen(filename, "w");
    char directoryName[19+6+1];
    sprintf(directoryName, "./data/line_%i/word_%i/", numberOfLine, 
                                                                numberOfWord);

    if (!mkdir(directoryName, S_IRUSR | S_IWUSR | S_IXUSR))
    {
        mkdir(directoryName, S_IRWXO);
        fp = fopen(filename, "w");
    }


    for (unsigned int i = 0; i < height; i++)
    {
        for (unsigned int j = pos1, jn = 0; j < pos2 && jn < pos2 - pos1; j++)
        {
            newMatrix[i * (pos2 - pos1) + jn] = matrix[i * width + j];
            jn++;
        }
    }

    unsigned int *pointerHeight = &height;
    unsigned int *realNewMatrix = trim(newMatrix, pos2 - pos1, pointerHeight);
    unsigned int *finalMatrix = resize(realNewMatrix, pos2 -pos1, height, 
                                                        newWidth, newHeight);

    for (unsigned int i = 0; i < newHeight; i++)
    {
        for (unsigned int j = 0; j < newWidth; j++)
        {
            fputc(finalMatrix[i * newWidth + j] + 48, fp);
        }
    }

    free(finalMatrix);


    //Add width in the file
    fprintf(fp, " ");
    width = newWidth;
    unsigned int nb = 0;

    while (width > 0)
    {
        width /= 10;
        nb++;
    }

    width = newWidth;

    while (nb > 1)
    {
        fputc(width / (unsigned int)powl(10, (nb - 1)) + 48, fp);
        width %= (unsigned int)powl(10, (nb - 1));
        nb--;
    }

    fputc(width % 10 + 48, fp);


    //Add height in the file
    fprintf(fp, " ");
    unsigned int newNewHeight = newHeight;
    nb = 0;

    while (newNewHeight > 0)
    {
        newNewHeight /= 10;
        nb++;
    }

    newNewHeight = newHeight;

    while (nb > 1)
    {
        fputc(newNewHeight / (unsigned int)powl(10, (nb - 1)) + 48, fp);
        newNewHeight %= (unsigned int)powl(10, (nb - 1));
        nb--;
    }

    fputc(newNewHeight % 10 + 48, fp);
    fclose(fp);
}

//Find the coordinates of the diiferents char in the word
unsigned int charSave(unsigned int list[], unsigned int matrix[], 
    unsigned int width, unsigned int height, unsigned int numberOfLine, 
    unsigned int numberOfWord, unsigned int newWidth, unsigned int newHeight)
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
            cutChar(pos1, pos2, matrix, width, height, numberOfLine, 
                            numberOfWord, numberOfChar, newWidth, newHeight);
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
        cutChar(pos1, width, matrix, width, height, numberOfLine, 
                            numberOfWord, numberOfChar, newWidth, newHeight);
        numberOfChar++;
    }

    return numberOfChar;
}

//Cut the blank top and the bottom of a matrix
unsigned int *trim(unsigned int *matrix, unsigned int width, 
                                                        unsigned int *height)
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

    free(yList);

    unsigned int *realNewMatrix = calloc(width * in, sizeof(unsigned int));

    for (unsigned i = 0; i < in; i++)
    {
        for (unsigned int j = 0; j < width; j++)
        {
            realNewMatrix[i * width + j] = newMatrix[i * width + j];
        }
    }

    free(newMatrix);
    *height = in;

    return realNewMatrix;
}

//Cut the blank left and right parts of a matrix
unsigned int *trimVertical(unsigned int *matrix, unsigned int *width, 
                                                            unsigned int height)
{
    unsigned int *xList = matrixToListChar(matrix, height, *width);
    unsigned int *newMatrix = calloc(height * (*width), sizeof(unsigned int));
    unsigned int jn = 0;

    for (unsigned int i = 0; i < height; i++)
    {
        jn = 0;
        for (unsigned int j = 0; j < *width; j++)
        {
            if (xList[j] == 1)
            {
                newMatrix[i * (*width) + jn] = matrix[i * (*width) + j];
                jn++;
            }
        }
    }

    free(xList);
    unsigned int *realNewMatrix = calloc(height * jn, sizeof(unsigned int));

    for (unsigned i = 0; i < height; i++)
    {
        for (unsigned int j = 0; j < jn; j++)
        {
            realNewMatrix[i * jn + j] = newMatrix[i * jn + j];
        }
    }

    free(newMatrix);
    *width = jn;

    return realNewMatrix;
}
