#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "wordSegmentation.h"

unsigned int *matrixToListWord(unsigned int matrix[], unsigned int height, unsigned int width)
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

unsigned int thresholdDefine(unsigned int list[], unsigned int width)
{
    unsigned int num = 0;
    unsigned int denum = 0;
    unsigned int prevBlack = 0;
    for (unsigned int i = 1; i < width; i++)
    {
        if (list[i] == 0)
        {
            num++;
            if (prevBlack)
            {
                denum++;
            }
            prevBlack = 0;
        }
        else
        {
            prevBlack = 1;
        }
    }
    //printf("%u, %u", num, denum);
    if (denum == 0)
    {
        return 0;
    }
    return num / denum;
}

void cutWord(unsigned int pos1, unsigned int pos2, unsigned int matrix[], unsigned int width, unsigned int height, unsigned int numberOfWord, unsigned int lineNumber)
{

    FILE *fp;
    char filename[292];
    sprintf(filename, "./data/line_%i/word_%i/word_%i.txt", lineNumber, numberOfWord, numberOfWord);
    fp = fopen(filename, "w");

    if (fp == NULL)
    {
        char directoryName[292];
        sprintf(directoryName, "./data/line_%i/word_%i/", lineNumber, numberOfWord);
        mkdir(directoryName, 0700);
        fp = fopen(filename, "w");
    }

    for (unsigned int i = 0; i < height; i++)
    {
        for (unsigned int j = pos1; j < pos2; j++)
        {
            fputc(matrix[i * width + j] + 48, fp);
        }
    }
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
    fclose(fp);
}

unsigned int wordSave(unsigned int list[], unsigned int matrix[], unsigned int width, unsigned int height, unsigned int lineNumber)
{
    unsigned int pos1 = 0;
    unsigned int pos2 = 1;
    unsigned int inAWord = 0;
    unsigned int numberOfWords = 0;

    for (unsigned int k = 0; k < width; k++)
    {
        if (list[k] == 1 && !inAWord)
        {
            inAWord = 1;
            pos1 = k;
        }
        else if (list[k] == 1)
        {
            inAWord = 1;
            pos2 = k;
        }

        else if (list[k] == 0 && inAWord)
        {
            pos2 = k;
            cutWord(pos1, pos2, matrix, width, height, numberOfWords, lineNumber);
            numberOfWords++;
            inAWord = 0;
        }
        else if (list[k] == 0)
        {
            inAWord = 0;
        }
    }
    if (inAWord)
    {
        cutWord(pos1, width, matrix, width, height, numberOfWords, lineNumber);
        numberOfWords++;
    }
    return numberOfWords;
}

unsigned int *matrixWordSpace(unsigned int list[], unsigned int threshold, unsigned int width)
{

    unsigned int lastWord = 0;
    unsigned int firstLetter = 0;
    unsigned int inAWord = 0;
    for (unsigned int i = 0; i < width; i++)
    {
        if (list[i] == 1)
        {
            if (!inAWord)
            {
                firstLetter = i;
                if (firstLetter - lastWord < threshold)
                {
                    for (unsigned int j = lastWord; j < firstLetter; j++)
                    {
                        list[j] = 1;
                    }
                }
            }
            inAWord = 1;
        }
        else
        {
            if (inAWord)
            {
                lastWord = i;
            }
            inAWord = 0;
        }
    }
    return list;
}
