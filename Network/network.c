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
    double trainingStep = 1;

    /********************************/
    /********* NETWORK INIT *********/
    /********************************/

    srand(time(NULL));
    
    Network net;

    net.computed = calloc(5, sizeof(double));
    
    double weights[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    
    for (size_t i = 2; i < 8; i++) {
   
        double r = (double)rand() / (double)(RAND_MAX / 5); 
        printf("random[%lu] = %f\n", i, r);
        weights[i] = r;

    }

    net.weights = weights;

    double count_nr[] = {2, 2, 1};
    net.count_nr = count_nr;

    double count_weight[] = {1, 2, 2};
    net.count_weight = count_weight;

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

    size_t testIndex = 1;
    size_t testMaxCount = sizeof(expectedResults) / sizeof(expectedResults[0]);
    double newWeights[8];
    for (size_t i = 0; i < 8; i++)
        newWeights[i] = 0;
    // Weights: [ in0.0,  in1.0, hid0.0, hid0.1, hid1.0, hid1.1, out0.0, out0.1]
    //          [ neur0,  neur1,  neur2,  neur2,  neur3,  neur3,  neur4,  neur4]
    //          [    w0,     w1,     w2,     w3,     w4,     w5,     w6,     w7]
    //          [i -> 0, i -> 1, 0 -> 2, 0 -> 3, 1 -> 2, 1 -> 3, 2 -> 4, 3 -> 4]


    /********************************/
    /********* PROPAGATION **********/
    /********************************/


    /********************************/
    /******* BACKPROPAGATION ********/
    /********************************/
    
    // 1 - Calcul de l'erreur sortie
    
    double outputError = (expectedResults[testIndex] - net.computed[4]) * net.computed[4] * (1 - net.computed[4]);
    printf("output error = %f\n", outputError);

    // 2 - Poids sortie
    double w3 = trainingStep * outputError * net.computed[3];
    double w2 = trainingStep * outputError * net.computed[2];
    newWeights[7] += w3;
    newWeights[6] += w2;

    // 3 - Calcul de l'erreur couche cachee
    
    double hidden3Error = (net.computed[3] * (1 - net.computed[3])) * (outputError * w3);
    double hidden2Error = (net.computed[2] * (1 - net.computed[2])) * (outputError * w2);

    printf("hidden errors = %f, %f\n", hidden3Error, hidden2Error);

    // 4 - Poids caches
    
    newWeights[5] += trainingStep * hidden3Error * net.computed[1];
    newWeights[3] += trainingStep * hidden3Error * net.computed[0];

    printf("h1: %f, %f\n", trainingStep * hidden3Error * net.computed[1], trainingStep * hidden3Error * net.computed[0]);
    
    newWeights[4] += trainingStep * hidden2Error * net.computed[1];
    newWeights[2] += trainingStep * hidden2Error * net.computed[0];

    printf("%f\n", newWeights[3]);
    printArr(newWeights, 8);
}


    /********************************/
    /********** UTILITIES ***********/
    /********************************/

double sigmoid(double z) {
    return 1.0 / (1.0 + exp(- z));
}

void printArr(double arr[], size_t count) {
    printf("arr: [%f", arr[0]);
    for (size_t i = 1; i < count; i++)
        printf(", %f", arr[i]);
    printf("]\n");
}
