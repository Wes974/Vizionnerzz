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

    //////////////////////////////////
    ///////// TRAINING DATA //////////
    //////////////////////////////////

    int trainingSet[] = {0, 0, 0, 1, 1, 0, 1, 1};
    double expectedResults[] = {0, 1, 1, 0};
    double trainingStep = 0.2;

    //////////////////////////////////
    ////////// NETWORK INIT //////////
    //////////////////////////////////

    srand(time(NULL));

    Network n;
    Network *net = &n;

    // computed[5] = {0, 0, 0, 0, 0};
    net->computed = calloc(5, sizeof(double));

    double weights[6] = {1, 1, 1, 1, 1, 1};

    for (size_t i = 0; i < 6; i++) {

        double r = (double)rand() / (double)(RAND_MAX / 5);
        weights[i] = r;

    }


    net->weights = weights;

    unsigned int count_nr[] = {2, 2, 1};
    net->count_nr = count_nr;

    unsigned int count_weight[] = {2, 2};
    net->count_weight = count_weight;

    double bias[3] = {0, 0, 0};
    for (size_t i = 0; i < 3; i++)
        bias[i] = (double)rand() / (double)(RAND_MAX / 5);
    net->bias = bias;

    printArr(weights, 6, "weights");
    printArr(bias, 3, "bias");

    //////////////////////////////////
    ///////// INITALIZATION //////////
    //////////////////////////////////


    size_t testMaxCount = sizeof(expectedResults) / sizeof(expectedResults[0]);

    // Weights: [ in0.0,  in1.0, hid0.0, hid0.1, hid1.0, hid1.1, out0.0, out0.1]
    //          [ neur0,  neur1,  neur2,  neur2,  neur3,  neur3,  neur4,  neur4]
    //          [    w0,     w1,     w2,     w3,     w4,     w5,     w6,     w7]
    //          [i -> 0, i -> 1, 0 -> 2, 0 -> 3, 1 -> 2, 1 -> 3, 2 -> 4, 3 -> 4]


    net->computed[0] = 1;
    net->computed[1] = 1;
    double w[6] = {1.0, -1.0, -1.0, 1.0, 1.0, 1.0};
    net->weights = w;

    forwardPropagation(net);
    printf("prop(1,1) = %f\n", net->computed[4]);
    net->computed[1] = 0;
    forwardPropagation(net);
    printf("prop(1,0) = %f\n", net->computed[4]);

    backPropagation(net, expectedResults, 1, .1);

    //return 0;
    
    size_t iter = 1000000;
    for (size_t i = 0; i < iter; i++) {
        //printf("Iter %lu: ", i);
        for (size_t testIndex = 0; testIndex < testMaxCount; testIndex++) {
            //printf("%lu ", testIndex + 1);
            net->computed[0] = trainingSet[2 * testIndex];
            net->computed[1] = trainingSet[2 * testIndex + 1];

            // for (size_t i = 0; i < 5; i++)
            //     printf("computed[%lu] = %f  ", i, net->computed[i]);

            // printf("\t i = %lu\n", i);

    //////////////////////////////////
    ////////// PROPAGATION ///////////
    //////////////////////////////////

            forwardPropagation(net);

    //////////////////////////////////
    //////// BACKPROPAGATION /////////
    //////////////////////////////////

            backPropagation(net, expectedResults, testIndex, trainingStep);

            /*// 1 - Output error

            double outputError = expectedResults[testIndex] - net->computed[4];

            // 2 - Output weights
            double w3 = trainingStep * outputError * net->computed[3] *
                (1 - net->computed[4]) * net->computed[4];
            double w2 = trainingStep * outputError * net->computed[2] *
                (1 - net->computed[4]) * net->computed[4];

            newWeights[7] += w3;
            newWeights[6] += w2;
            newBias[4] += trainingStep * outputError * net->computed[4] * 
                (1 - net->computed[4]);

            // 3 - Hidden layer errors
            double hidden3Error = outputError * net->weights[7];
            double hidden2Error = outputError * net->weights[6];

            // 4 - Hidden layer weight
            newWeights[5] += trainingStep * hidden3Error * net->computed[3] * 
                (1 - net->computed[3]) * net->computed[1];
            newWeights[4] += trainingStep * hidden3Error * net->computed[3] *
                (1 - net->computed[3]) * net->computed[0];
            newBias[3] += trainingStep * hidden3Error * net->computed[3] *
                (1 - net->computed[3]);

            newWeights[3] += trainingStep * hidden2Error * net->computed[2] *
                (1 - net->computed[2]) * net->computed[1];
            newWeights[2] += trainingStep * hidden2Error * net->computed[2] *
                (1 - net->computed[2]) * net->computed[0];
            newBias[2] += trainingStep * hidden2Error * net->computed[2] *
                (1 - net->computed[2]);

            for (size_t j = 2; j < 8; j++) {
                net->weights[j] += newWeights[j];
                newWeights[j] = 0;
            }
            for (size_t j = 2; j < 5; j++) {
                net->bias[j] += newBias[j];
                newBias[j] = 0;
            }*/
        }
        //printf("\n");

    }

    //////////////////////////////////
    ////////// FINAL TESTS ///////////
    //////////////////////////////////

    net->computed[0] = 0;
    net->computed[1] = 0;
    forwardPropagation(net);
    printf("(0, 0) = %f\n", net->computed[4]);

    net->computed[0] = 0;
    net->computed[1] = 1;
    forwardPropagation(net);
    printf("(0, 1) = %f\n", net->computed[4]);

    net->computed[0] = 1;
    net->computed[1] = 0;
    forwardPropagation(net);
    printf("(1, 0) = %f\n", net->computed[4]);

    net->computed[0] = 1;
    net->computed[1] = 1;
    forwardPropagation(net);
    printf("(1, 1) = %f\n", net->computed[4]);

    return 0;
}


    //////////////////////////////////
    // Forward Propagation function //
    //////////////////////////////////

void forwardPropagation(Network *net) {

    // Hidden Layer
    
    for (size_t i = 0; i < net->count_nr[1]; i++) {
        double sum = 0.0;
        for (size_t j = 0; j < net->count_weight[0]; j++) {
            sum += net->computed[j] * net->weights[i * net->count_weight[0] + j];
        }
        net->computed[net->count_nr[0] + i] = sigmoid(sum + net->bias[i]);
    }

    // Output Layer
    
    for (size_t i = 0; i < net->count_nr[2]; i++) {
        double sum = 0.0;
        for (size_t j = 0; j < net->count_weight[1]; j++) {
            sum += net->computed[net->count_nr[0] + j] * net->weights[net->count_weight[0] * net->count_nr[1] + i * net->count_weight[1] + j];
        }
        net->computed[net->count_nr[0] + net->count_nr[1] + i] = sigmoid(sum + net->bias[2]);
    }
}

    //////////////////////////////////
    //////// BACKPROPAGATION /////////
    //////////////////////////////////

void backPropagation(Network *net, double expectedResults[], size_t resStart, double trainingStep) {
    double newWeights[net->count_weight[0] * net->count_nr[1] + net->count_weight[1] * net->count_nr[2]];
    double newBias[net->count_nr[1] + net->count_nr[2]];
    double outputErrors[net->count_nr[2]];
    double hiddenErrors[net->count_nr[1]];
    
    // 1 - Output error
    size_t outputPos = net->count_nr[0] + net->count_nr[1];
    size_t outputWeightPos = net->count_nr[1] * net->count_weight[0];

    for (size_t i = 0; i < net->count_nr[2]; i++) {
        outputErrors[i] = (expectedResults[resStart + i] - net->computed[outputPos + i]);
        /*newBias[net->count_nr[1] + i] = outputErrors[i] * trainingStep * transferDeriv(net->computed[outputPos + i]);
        for (size_t j = 0; j < net->count_weight[1]; j++) {
            newWeights[outputWeightPos + i * net->count_weight[1] + j] = trainingStep * outputErrors[i] * net->computed[net->count_nr[0] + j] * transferDeriv(net->computed[outputPos + i]);
        }*/
    }

    // 2 - Hidden layer errors

    for (size_t i = 0; i < net->count_nr[1]; i++) {
        double e = 0.0;
        for (size_t j = 0; j < net->count_nr[2]; j++) {
            e += net->weights[outputWeightPos + i + j * net->count_weight[1]] * outputErrors[j];
            /*for (size_t k = 0; k < net->count_nr[2]; k++) {
            }*/
        }
        /*newWeights[i * net->count_weight[0] + j] = trainingStep * e * net->computed[j] * transferDeriv(net->computed[net->count_nr[0] + i]);
        newBias[i] = e * trainingStep * transferDeriv(net->computed[net->count_nr[0] + i]);*/
        hiddenErrors[i] = e;
    }

    // 3 - Output new weights
    
    for (size_t i = 0; i < net->count_nr[2]; i++) {
        double w = trainingStep * outputErrors[i] * transferDeriv(net->computed[outputPos + i]);
        for (size_t j = 0; j < net->count_weight[1]; j++)
            newWeights[outputWeightPos + i * net->count_weight[1] + j] = w * net->computed[outputPos + i];
        newBias[net->count_nr[1] + i] = w;
    }

    // 4 - Hidden new weights

    for (size_t i = 0; i < net->count_nr[1]; i++) {
        double w = trainingStep * hiddenErrors[i] * transferDeriv(net->computed[net->count_nr[0] + i]);
        for (size_t j = 0; j < net->count_weight[0]; j++)
            newWeights[i * net->count_weight[0] + j] = w * net->computed[net->count_nr[0] + i];
        newBias[i] = w;
    }

    //printArr(newWeights, sizeof(newWeights) / sizeof(double), "newWeights");
    //printArr(newBias, sizeof(newBias) / sizeof(double), "newBias");

    for (size_t i = 0; i < sizeof(newWeights) / sizeof(double); i++) {
        net->weights[i] += newWeights[i];
    }
    for (size_t i = 0; i < sizeof(newBias) / sizeof(double); i++) {
        net->bias[i] += newBias[i];
    }
}

    //////////////////////////////////
    /////////// UTILITIES ////////////
    //////////////////////////////////

double sigmoid(double z) {
    return 1.0 / (1.0 + exp(- z));
}

double transferDeriv(double x) {
    return x * (1.0 - x);
}

void printArr(double arr[], size_t count, char name[]) {
    printf("%s: [%f",name, arr[0]);
    for (size_t i = 1; i < count; i++)
        printf(", %f", arr[i]);
    printf("]\n");
}
