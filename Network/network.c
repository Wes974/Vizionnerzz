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
    /******** TRAINING DATA *********/
    /********************************/
    
    int trainingSet[] = {0, 0, 0, 1, 1, 0, 1, 1};
    double expectedResults[] = {0, 1, 1, 0};
    double trainingStep = 0.2;

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


    unsigned int propPrint = 0;
    unsigned int backPrint = 0;
    unsigned int finalTests = 1;
    unsigned int finalPrints = 1;
    unsigned int packedMerge = 0;


    //size_t testIndex = 1;
    size_t testMaxCount = sizeof(expectedResults) / sizeof(expectedResults[0]);
    double newWeights[8];
    double newBias[5];
    for (size_t i = 0; i < 8; i++)
        newWeights[i] = 0;
    for (size_t i = 0; i < 5; i++)
        newBias[i] = 0;

    printf("sizeof bias    %lu\n", sizeof(net.bias));
    printf("sizeof bias[0] %lu\n", sizeof(net.bias[0]));

    for (size_t i = 0; i < 5; i++) {
    
        printf("bias[%lu] = %f\n", i, net.bias[i]);

    }

    // Weights: [ in0.0,  in1.0, hid0.0, hid0.1, hid1.0, hid1.1, out0.0, out0.1]
    //          [ neur0,  neur1,  neur2,  neur2,  neur3,  neur3,  neur4,  neur4]
    //          [    w0,     w1,     w2,     w3,     w4,     w5,     w6,     w7]
    //          [i -> 0, i -> 1, 0 -> 2, 0 -> 3, 1 -> 2, 1 -> 3, 2 -> 4, 3 -> 4]


    size_t iter = 100000000;
    for (size_t i = 0; i < iter; i++) {
        for (size_t testIndex = 0; testIndex < testMaxCount; testIndex++) {
            net.computed[0] = trainingSet[2 * testIndex];
            net.computed[1] = trainingSet[2 * testIndex + 1];

    /********************************/
    /********* PROPAGATION **********/
    /********************************/

            forwardPropagation(net, propPrint);

            if (propPrint)
                printf("\nafter, activatedOut = %f\n", net.computed[4]);

    /********************************/
    /******* BACKPROPAGATION ********/
    /********************************/

            // 1 - Calcul de l'erreur sortie

            double outputError = expectedResults[testIndex] - net.computed[4];
            if (backPrint)
                printf("output error = %f\n", outputError);

            // 2 - Poids sortie
            double w3 = trainingStep * outputError * net.computed[3] * (1 - net.computed[4]) * net.computed[4];
            double w2 = trainingStep * outputError * net.computed[2] * (1 - net.computed[4]) * net.computed[4];

            //double DW6 = trainingStep * outputError * (net.computed[4] - net.computed[4] * net.computed[4]) * net.computed[2];
            //double DW7 = trainingStep * outputError * (net.computed[4] - net.computed[4] * net.computed[4]) * net.computed[3];

            newWeights[7] += w3;
            newWeights[6] += w2;
            newBias[4] += trainingStep * outputError * net.computed[4] * (1 - net.computed[4]);

            // 3 - Calcul de l'erreur couche cachee

            double hidden3Error = outputError * net.weights[7];
            double hidden2Error = outputError * net.weights[6];
            
            if (backPrint)
                printf("hidden errors = %f, %f\n", hidden3Error, hidden2Error);

            // 4 - Poids caches

            newWeights[5] += trainingStep * hidden3Error * net.computed[3] * (1 - net.computed[3]) * net.computed[1];
            newWeights[4] += trainingStep * hidden3Error * net.computed[3] * (1 - net.computed[3]) * net.computed[0];
            newBias[3] += trainingStep * hidden3Error * net.computed[3] * (1 - net.computed[3]);

            if (backPrint)
                printf("h1: %f, %f\n", trainingStep * hidden3Error * net.computed[1], trainingStep * hidden3Error * net.computed[0]);

            newWeights[3] += trainingStep * hidden2Error * net.computed[2] * (1 - net.computed[2]) * net.computed[1];
            newWeights[2] += trainingStep * hidden2Error * net.computed[2] * (1 - net.computed[2]) * net.computed[0];
            newBias[2] += trainingStep * hidden2Error * net.computed[2] * (1 - net.computed[2]);

            if (backPrint)
                printArr(newWeights, 8, "newWeights");
            if (!packedMerge) {
                for (size_t j = 2; j < 8; j++) {
                    net.weights[j] += newWeights[j];
                    newWeights[j] = 0;
                }
                for (size_t j = 2; j < 5; j++) {
                    net.bias[j] += newBias[j];
                    newBias[j] = 0;
                }
            }
        }

        if (backPrint) {
            printf("%f\n", newWeights[3]);
            printArr(newWeights, 8, "newWeights");
        }
/*
        if (packedMerge) {
            for (size_t j = 2; j < 8; j++) {
                net.weights[j] -= newWeights[j];
                newWeights[j] = 0;
            }
            for (size_t j = 2; j < 5; j++) {
                net.bias[j] -= newBias[j];
                newBias[j] = 0;
            }
        }
*/
    }

    if (finalPrints) {
        printArr(net.weights, 8, "final weights");
        printArr(net.bias, 5, "final biases");
    }

    if (finalTests) {
        net.computed[0] = 0;
        net.computed[1] = 0;
        forwardPropagation(net, 0);
        printf("(0, 0) = %f\n", net.computed[4]);

        net.computed[0] = 0;
        net.computed[1] = 1;
        forwardPropagation(net, 0);
        printf("(0, 1) = %f\n", net.computed[4]);

        net.computed[0] = 1;
        net.computed[1] = 0;
        forwardPropagation(net, 0);
        printf("(1, 0) = %f\n", net.computed[4]);

        net.computed[0] = 1;
        net.computed[1] = 1;
        forwardPropagation(net, 0);
        printf("(1, 1) = %f\n", net.computed[4]);
    }
}


    /********************************/
    /* Forward Propagation function */
    /********************************/

void forwardPropagation(Network net, unsigned int propPrint) {

    if (propPrint)
        printf("\nBegin forward propagation\n");

    // Hidden Layer
    double netH1 = 0.0, netH2 = 0.0;
    
    // H1 Processing
    netH1 = net.weights[2] * net.computed[0] + net.weights[3] * net.computed[1] + net.bias[2] * 1;
    if (propPrint)
        printf("netH1 = %f\n", netH1);
    // H2 Processing
    netH2 = net.weights[4] * net.computed[0] + net.weights[5] * net.computed[1] + net.bias[3] * 1;
    if (propPrint)
        printf("netH2 = %f\n", netH2);

    // Sigmoid
    double activatedH1 = sigmoid(netH1), activatedH2 = sigmoid(netH2);

    net.computed[2] = activatedH1;
    net.computed[3] = activatedH2;

    if (propPrint) {
        printf("activatedH1 = %f\n", activatedH1);
        printf("activatedH2 = %f\n", activatedH2);
    }

    // Output Layer
    double outH1 = 0.0;

    // Out Processing
    outH1 = net.weights[6] * activatedH1 + net.weights[7] * activatedH2 + net.bias[4] * 1;
    if (propPrint)
        printf("outH1 = %f\n", outH1);

    // Sigmoid
    double activatedOut = sigmoid(outH1);
    
    if (propPrint)
        printf("activatedOut = %f\n", activatedOut);

    net.computed[4] = activatedOut;

}

    /********************************/
    /********** UTILITIES ***********/
    /********************************/

double sigmoid(double z) {
    return 1.0 / (1.0 + exp(- z));
}

void printArr(double arr[], size_t count, char name[]) {
    printf("%s: [%f",name, arr[0]);
    for (size_t i = 1; i < count; i++)
        printf(", %f", arr[i]);
    printf("]\n");
}
