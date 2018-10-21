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
    double trainingStep = 0.1;

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

    double bias[2] = {0, 0};
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

    printf("sizeof bias    %lu\n", sizeof(net.bias));
    printf("sizeof bias[0] %lu\n", sizeof(net.bias[0]));

    for (size_t i = 0; i < 5; i++) {
    
        printf("bias[%lu] = %f\n", i, net.bias[i]);

    }

    size_t testIndex = 0;
    size_t testMaxCount = sizeof(expectedResults) / sizeof(expectedResults[0]);
    double newWeights[8];
    // Weights: [ in0.0,  in1.0, hid0.0, hid0.1, hid1.0, hid1.1, out0.0, out0.1]
    //          [ neur0,  neur1,  neur2,  neur2,  neur3,  neur3,  neur4,  neur4]
    //          [    w0,     w1,     w2,     w3,     w4,     w5,     w6,     w7]
    //          [i -> 0, i -> 1, 0 -> 2, 0 -> 3, 1 -> 2, 1 -> 3, 2 -> 4, 3 -> 4]


    /********************************/
    /********* PROPAGATION **********/
    /********************************/

    forwardPropagation(net);

    printf("\nafter, activatedOut = %f", net.computed[4]);

    /********************************/
    /******* BACKPROPAGATION ********/
    /********************************/
    
    // 1 - Calcul de l'erreur sortie
    
//    double outputError = (expectedResults[testIndex] - net.computed[4]) * net.computed[4] * (1 - net.computed[4]);
//    printf("output error = %f\n", outputError);

    // 2 - Poids sortie
    
//    newWeights[7]

    // 3 - Calcul de l'erreur couche cachee
    
    // 4 - Poids caches
    
}


    /********************************/
    /* Forward Propagation function */
    /********************************/

void forwardPropagation(Network net) {

    printf("\nBegin forward propagation\n");

    // Hidden Layer
    double netH1 = 0.0, netH2 = 0.0;
    
    // H1 Processing
    netH1 = net.weights[0] * net.computed[0] + net.weights[2] * net.computed[1] + net.bias[0] * 1;
    printf("netH1 = %f\n", netH1);
    // H2 Processing
    netH2 = net.weights[1] * net.computed[0] + net.weights[3] * net.computed[1] + net.bias[0] * 1;
    printf("netH2 = %f\n", netH2);

    // Sigmoid
    double activatedH1 = sigmoid(netH1), activatedH2 = sigmoid(netH2);

    net.computed[2] = activatedH1;
    net.computed[3] = activatedH2;

    printf("activatedH1 = %f\n", activatedH1);
    printf("activatedH2 = %f\n", activatedH2);

    // Output Layer
    double outH1 = 0.0;

    // Out Processing
    outH1 = net.weights[4] * activatedH1 + net.weights[5] * activatedH2 + net.bias[1] * 1;
    printf("outH1 = %f\n", outH1);

    // Sigmoid
    double activatedOut = sigmoid(outH1);
    
    printf("activatedOut = %f\n", activatedOut);

    net.computed[4] = activatedOut;

}

    /********************************/
    /********** UTILITIES ***********/
    /********************************/

double sigmoid(double z) {
    return 1.0 / (1.0 + exp(- z));
}
