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

    srand(time(NULL));
    
    Network net;

    net.computed = calloc(5, sizeof(double));
    printf("sizeof computed %lu\n", sizeof(net.computed));
    
    printf("%lu\n", sizeof(net));

    double weights[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    
    for (size_t i = 3; i < 8; i++) {
   
        double r = (double)rand() / (double)(RAND_MAX / 5); 
        printf("random[%lu] = %f\n", i, r);
        weights[i] = r;

    }

    net.weights = weights;

    double nr[] = {2, 2, 1};
    net.count_nr = nr;

    double weight[] = {1, 2, 2};
    net.count_weight = weight;

    double bias[5] = {0, 0, 0, 0, 0};
    net.bias = bias;

    printf("\n%f\n", net.bias[3]);

    printf("Parcours de computed\n");

    printf("sizeof weight    %lu\n", sizeof(net.weights));
    printf("sizeof weight[0] %lu\n", sizeof(net.weights[0]));

    for (size_t i = 0; i < 8; i++) {
    
        printf("weight[%lu] = %f\n", i, net.weights[i]);

    }

}


/*
Network createXOR() {

    Network net;

    net.computed = calloc(5, sizeof(double));
    printf("sizeof computed %lu\n", sizeof(net.computed));
    
    printf("%lu\n", sizeof(net));

    double w[8];

    fillArray(&w, 8, 2);
    net.weights = w;
    // net.biais = createArray(5, 0);
    
    double nr[] = {2, 2, 1};
    net.count_nr = nr;

    double weight[] = {1, 2, 2};
    net.count_weight = weight;

    return net;

}

void fillArray(double *arr[], size_t count, size_t inputSize) {
    
   printf("count = %lu\n", count);

   for (size_t i = 0; i < inputSize; i++) {
   
        *arr[i] = 0;

   }

   for (size_t i = inputSize; i < count; i++) {
   
       double r = (double)rand() / (double)(RAND_MAX / 5); 
       printf("random[%lu] = %f\n", i, r);
       *arr[i] = r;

   }

}
*/




/* ---------    UTILITIES   -------- */

double sigmoid(double z) {
    return 1.0 / (1.0 + exp(- z));
}


/*

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


Malo *fillNeurons(size_t count) {

    Malo *arr[count];
    
    for (size_t i = 0; i < count; i++) {
        
        Malo neur;
        neur.bias = (float)rand() / (float)(RAND_MAX / 5);
        neur.weight = (float)rand() / (float)(RAND_MAX / 5);
        
        arr[i] = &neur;
    }
    
    return *arr;
}

float *forwardPropagation(Network net) {

  for (size_t i = 0; i < net.NumHidden; i++) {
      

  }

}

*/
