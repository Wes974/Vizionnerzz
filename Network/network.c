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

    Network n = createXOR();

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
    
    for (size_t i = 0; i < count; i++) {
        
        Malo neur;
        neur.bias = (float)rand() / (float)(RAND_MAX / 5);
        neur.weight = (float)rand() / (float)(RAND_MAX / 5);
        
        arr[i] = &neur;
    }
    
    return *arr;
}
