#ifndef CHARSEGMENTATION
#define CHARSEGMENTATION

unsigned int * resize(unsigned int * matrix, unsigned int width, unsigned int height, unsigned int newWidth, unsigned int newHeight); 
unsigned int * matrixToListChar(unsigned int matrix[], unsigned int height, unsigned int width);
unsigned int * matrixToListChar(unsigned int matrix[], unsigned int height, unsigned int width);

void cutChar(unsigned int pos1, unsigned int pos2, unsigned int matrix[], unsigned int width, unsigned int heigth, unsigned int numberOfLine, unsigned int numberOfWord, unsigned int numberOfChar, unsigned int newWidth, unsigned int newHeight);
 
unsigned int charSave(unsigned int list[], unsigned int matrix[], unsigned int width, unsigned int heigth, unsigned int numberOfLine, unsigned int numberOfWord, unsigned int newWidth, unsigned int Height);

unsigned int * trim(unsigned int * matrix, unsigned int width, unsigned int *height);
unsigned int * trimVertical(unsigned int * matrix, unsigned int *width, unsigned int height);

unsigned int * cutLineChar(unsigned int pos1, unsigned int pos2, unsigned int matrix[], unsigned int width, unsigned int height);
#endif
