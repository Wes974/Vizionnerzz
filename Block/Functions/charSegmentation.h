#ifndef CHARSEGMENTATION
#define CHARSEGMENTATION

unsigned int * matrixToListChar(unsigned int matrix[], unsigned int height, unsigned int width);
 
void cutChar(unsigned int pos1, unsigned int pos2, unsigned int matrix[], unsigned int width, unsigned int heigth, unsigned int numberOfLine, unsigned int numberOfWord, unsigned int numberOfChar);
 
unsigned int charSave(unsigned int list[], unsigned int matrix[], unsigned int width, unsigned int heigth, unsigned int numberOfLine, unsigned int numberOfWord);



#endif
