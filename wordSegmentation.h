#ifndef WORDSEGMENTATION
#define WORDSEGMENTATION

unsigned int *  matrixToListWord(unsigned int matrix[], unsigned int height, 
                                                            unsigned int width);

unsigned int thresholdDefine(unsigned int list[], unsigned int width);

void cutWord(unsigned int pos1, unsigned int pos2, unsigned int matrix[], 
    unsigned int width, unsigned int heigth, unsigned int numberOfWord, 
        unsigned int lineNumber);

unsigned int wordSave(unsigned int list[], unsigned int matrix[], 
            unsigned int width, unsigned int heigth, unsigned int lineNumber);

unsigned int *matrixWordSpace(unsigned int list[], unsigned int threshold, 
                                                            unsigned int width);

#endif

