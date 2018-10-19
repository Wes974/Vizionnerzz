//
//  network.c
//  OCR Project
//

#include "network.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(){

    Network n;

    n.NumHidden = 0;



}


struct Network createXOR() {

    Network xor;
    xor.NumInput = 2;
    xor.NumHidden = 2;
    xor.NumOutput = 1;
    
    xor.input[xor.NumInput];
    xor.hidden[xor.NumHidden];
    xor.output[xor.NumOutput];

    fillNeurons(xor.input, xor.NumInput);
    fillNeurons(xor.hidden, xor.NumHidden);
    fillNeurons(xor.output, xor.NumOutput);
    
}

double sigmoid(double z) {
    return 1.0 / (1.0 + exp(- z));
}

void fillNeurons(Malo arr[], size_t count) {

    srand(time(NULL));
    for (size_t i = 0; i < count; i++) {
        Malo neur;
        neur.bias = (float)rand()/(float)(RAND_MAX/5);
        neur.weight = (float)rand()/(float)(RAND_MAX/5);
        arr[i] = neur;
    }

}
