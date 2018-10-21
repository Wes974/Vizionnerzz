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

    /********************************/    
    /********* TRAINIG DATA *********/
    /********************************/
    
    int trainingSet[] = {0, 0, 0, 1, 1, 0, 1, 1};
    double expectedResults[] = {0, 1, 1, 0};

    /********************************/
    /********* NETWORK INIT *********/
    /********************************/

    srand(time(NULL));
    
    Network net;

    net.computed = calloc(5, sizeof(double));
    
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


    /********************************/
    /******** VERIFICATIONS *********/
    /********************************/

    printf("sizeof computed %lu\n", sizeof(net.computed));
    
    printf("%lu\n", sizeof(net));

    printf("\n%f\n", net.bias[3]);

    printf("Parcours de computed\n");

    printf("sizeof weight    %lu\n", sizeof(net.weights));
    printf("sizeof weight[0] %lu\n", sizeof(net.weights[0]));

    for (size_t i = 0; i < 8; i++) {
    
        printf("weight[%lu] = %f\n", i, net.weights[i]);

    }

    /********************************/
    /********* PROPAGATION **********/
    /********************************/


     /********************************/
     /******* BACKPROPAGATION ********/
     /********************************/
 
}


    /********************************/
    /********** UTILITIES ***********/
    /********************************/

double sigmoid(double z) {
    return 1.0 / (1.0 + exp(- z));
}
