//
//  network.c
//  OCR Project
//

#include "network.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

 //   printf("hiddenMalo[0].bias = %f\n", ((Malo)createXOR().hidden[0]).bias);
    createXOR();
}


Network createXOR() {

    Network notAXor;
    
    notAXor.NumInput    = 2;
    notAXor.NumHidden   = 2;
    notAXor.NumOutput   = 1;

    notAXor.input   = fillNeurons(2);
    notAXor.hidden  = fillNeurons(2);
    notAXor.output  = fillNeurons(1);

    return notAXor;
}


double sigmoid(double z) {
    return 1.0 / (1.0 + exp(- z));
}

Malo * fillNeurons(size_t count) {

    srand(time(NULL));
    Malo *arr[count];
    
    printf("size: %lu\n", sizeof(arr) / sizeof(Malo));
    
    for (size_t i = 0; i < count; i++) {
        
        printf("%lu/%lu ", i, count);
        
        Malo neur;
        neur.bias = (float)rand() / (float)(RAND_MAX / 5);
        neur.weight = (float)rand() / (float)(RAND_MAX / 5);
        
        printf("bias: %f weight: %f\n", neur.bias, neur.weight);
        
        arr[i] = &neur;
    }
    
    return *arr;
}
