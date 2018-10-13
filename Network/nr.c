//
//  nr.c
//  OCR Project
//


#include <math.h>
#include "nr.h"

// Sigmoid function
double sigmoid(double z) {
    return 1.0 / (1.0 + exp(- z));
}


