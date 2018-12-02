#ifndef LINESEGMENTATION
#define LINESEGMENTATION

unsigned int * matrixToListLine(unsigned int matrix[], unsigned int height, unsigned int width);
 
void cutLine(unsigned int pos1, unsigned int pos2, unsigned int matrix[], unsigned int width, unsigned int heigth, unsigned int numberOfLine);
 
unsigned int lineSave(unsigned int list[], unsigned int matrix[], unsigned int width, unsigned int heigth);



#endif
