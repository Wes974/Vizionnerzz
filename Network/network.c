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

    srand(3);

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
    /******** INITALIZATION *********/
    /********************************/


    size_t testMaxCount = sizeof(expectedResults) / sizeof(expectedResults[0]);
    double newWeights[8];
    double newBias[5];
    for (size_t i = 0; i < 8; i++)
        newWeights[i] = 0;
    for (size_t i = 0; i < 5; i++)
        newBias[i] = 0;

    // Weights: [ in0.0,  in1.0, hid0.0, hid0.1, hid1.0, hid1.1, out0.0, out0.1]
    //          [ neur0,  neur1,  neur2,  neur2,  neur3,  neur3,  neur4,  neur4]
    //          [    w0,     w1,     w2,     w3,     w4,     w5,     w6,     w7]
    //          [i -> 0, i -> 1, 0 -> 2, 0 -> 3, 1 -> 2, 1 -> 3, 2 -> 4, 3 -> 4]


    size_t iter = 10000000;
    for (size_t i = 0; i < iter; i++) {
        for (size_t testIndex = 0; testIndex < testMaxCount; testIndex++) {
            net.computed[0] = trainingSet[2 * testIndex];
            net.computed[1] = trainingSet[2 * testIndex + 1];

    /********************************/
    /********* PROPAGATION **********/
    /********************************/

            forwardPropagation(net, propPrint);

    /********************************/
    /******* BACKPROPAGATION ********/
    /********************************/

            // 1 - Output error

            double outputError = expectedResults[testIndex] - net.computed[4];

            // 2 - Output weights
            double w3 = trainingStep * outputError * net.computed[3] * (1 - net.computed[4]) * net.computed[4];
            double w2 = trainingStep * outputError * net.computed[2] * (1 - net.computed[4]) * net.computed[4];

            newWeights[7] += w3;
            newWeights[6] += w2;
            newBias[4] += trainingStep * outputError * net.computed[4] * (1 - net.computed[4]);

            // 3 - Hidden layer errors
            double hidden3Error = outputError * net.weights[7];
            double hidden2Error = outputError * net.weights[6];

            // 4 - Hidden layer weight
            newWeights[5] += trainingStep * hidden3Error * net.computed[3] * (1 - net.computed[3]) * net.computed[1];
            newWeights[4] += trainingStep * hidden3Error * net.computed[3] * (1 - net.computed[3]) * net.computed[0];
            newBias[3] += trainingStep * hidden3Error * net.computed[3] * (1 - net.computed[3]);

            newWeights[3] += trainingStep * hidden2Error * net.computed[2] * (1 - net.computed[2]) * net.computed[1];
            newWeights[2] += trainingStep * hidden2Error * net.computed[2] * (1 - net.computed[2]) * net.computed[0];
            newBias[2] += trainingStep * hidden2Error * net.computed[2] * (1 - net.computed[2]);

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

    /********************************/
    /********* FINAL TESTS **********/
    /********************************/

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


    /********************************/
    /* Forward Propagation function */
    /********************************/

void forwardPropagation(Network net, unsigned int propPrint) {

    // Hidden Layer
    double netH1 = 0.0, netH2 = 0.0;

    // H1 Processing
    netH1 = net.weights[2] * net.computed[0] + net.weights[3] * net.computed[1] + net.bias[2] * 1;

    // H2 Processing
    netH2 = net.weights[4] * net.computed[0] + net.weights[5] * net.computed[1] + net.bias[3] * 1;

    // Sigmoid
    double activatedH1 = sigmoid(netH1), activatedH2 = sigmoid(netH2);

    net.computed[2] = activatedH1;
    net.computed[3] = activatedH2;

    // Output Layer
    double outH1 = 0.0;

    // Out Processing
    outH1 = net.weights[6] * activatedH1 + net.weights[7] * activatedH2 + net.bias[4] * 1;

    // Sigmoid
    double activatedOut = sigmoid(outH1);

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
