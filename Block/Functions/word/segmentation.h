#ifndef SEGMENTATION
#define SEGMENTATION

unsigned int *  matrixToList(unsigned int matrix[], unsigned int height, unsigned int width);

unsigned int thresholdDefine(unsigned int list[], unsigned int width);

unsigned int * cutWord(unsigned int pos1, unsigned int pos2, unsigned int matrix[], unsigned int width, unsigned int heigth);

unsigned int * whatToSave(unsigned int threshold, unsigned int list[], unsigned int matrix[], unsigned int width, unsigned int heigth);



#endif
