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


struct Network createXOR() {

    /*Malo in[2];
    Malo hidden[2];
    Malo out[1];

    fillNeurons(in, 2);
    fillNeurons(hidden, 2);
    fillNeurons(out, 1);*/

    struct Network notAXor = {2, 2, 1,fillNeurons(2), fillNeurons(2), fillNeurons(1)};
    /*xor.NumInput = 2;
    xor.NumHidden = 2;
    xor.NumOutput = 1;
    
    xor.input[xor.NumInput];
    xor.hidden[xor.NumHidden];
    xor.output[xor.NumOutput];

    fillNeurons(xor.input, xor.NumInput);
    fillNeurons(xor.hidden, xor.NumHidden);
    fillNeurons(xor.output, xor.NumOutput);*/
    return notAXor;
}

double sigmoid(double z) {
    return 1.0 / (1.0 + exp(- z));
}

int * fillNeurons(size_t count) {

    srand(time(NULL));
    Malo *arr[count];
    printf("size: %lu (%lu items)\n", sizeof(arr), sizeof(arr)/sizeof(Malo));
    for (size_t i = 0; i < count; i++) {
        printf("%lu/%lu ", i, count);
        Malo neur;
        neur.bias = (float)rand()/(float)(RAND_MAX/5);
        neur.weight = (float)rand()/(float)(RAND_MAX/5);
        printf("bias: %f weight: %f size: %lu\n", neur.bias, neur.weight, sizeof(neur));
        *arr[i] = neur;
        printf("done, %f\n", arr[0]->bias);
    }
    return arr;
}
