//
//  network.c
//  OCR Project
//

#define _GNU_SOURCE
#include "network.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){

    //////////////////////////////////
    ///////// TRAINING DATA //////////
    //////////////////////////////////

    /*int trainingSet[] = {0, 0, 0, 1, 1, 0, 1, 1};
    double expectedResults[] = {0, 1, 1, 0, 1, 0, 0, 1};*/
    double trainingStep = 1;

    FILE *f;
    f = fopen("./alphabeat.txt", "r");
    if (f == NULL) {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
    }
    unsigned int in = 100, out = 36;
    char expectedChar[out];
    double expectedResults[out * out];
    double trainingSet[out * in];
    for (size_t i = 0; i < out; i++) {
        char *l = NULL;
        size_t size;
        getline(&l, &size, f);
        if (i == 0)
            printf("%s\n", l);
        expectedChar[i] = *l;
        for (size_t j = 0; j < out; j++) {
            expectedResults[i * out + j] = j == i;  
        }
        for (size_t j = 0; j < in; j++) {
            trainingSet[i * in + j] = *(l + 1 + j) - '0';
        }
    }

    //////////////////////////////////
    ////////// NETWORK INIT //////////
    //////////////////////////////////

    srand(time(NULL));

    Network n;
    Network *net = &n;

    unsigned int count_nr[] = {in, 100, out}; 

    initNetwork(net, count_nr);
    
    //printArr(net->weights, net->count_weight[0] * net->count_nr[1] + net->count_weight[1] * net->count_nr[2], "weights");
    //printArr(net->bias, net->count_nr[1] + net->count_nr[2], "bias");

    //////////////////////////////////
    ///////// INITALIZATION //////////
    //////////////////////////////////


    size_t testMaxCount = sizeof(expectedResults) / sizeof(expectedResults[0]) / net->count_nr[2];

    // Weights: [ in0.0,  in1.0, hid0.0, hid0.1, hid1.0, hid1.1, out0.0, out0.1]
    //          [ neur0,  neur1,  neur2,  neur2,  neur3,  neur3,  neur4,  neur4]
    //          [    w0,     w1,     w2,     w3,     w4,     w5,     w6,     w7]
    //          [i -> 0, i -> 1, 0 -> 2, 0 -> 3, 1 -> 2, 1 -> 3, 2 -> 4, 3 -> 4]


    //net->computed[0] = 1;
    //net->computed[1] = 1;
    /*double w[6] = {1.0, -1.0, -1.0, 1.0, 1.0, 1.0};
    net->weights = w;*/

    //forwardPropagation(net);
    //printf("prop(1,1) = %f\n", net->computed[4]);
    //printArr(net->computed, net->count_nr[0] + net->count_nr[1] + net->count_nr[2], "(1, 1)");    
    //net->computed[1] = 0;
    //forwardPropagation(net);
    //printf("prop(1,0) = %f\n", net->computed[4]);
    //printArr(net->computed, net->count_nr[0] + net->count_nr[1] + net->count_nr[2], "(1, 0)");

    //backPropagation(net, expectedResults, 1, .1);

    //return 0;
    
    size_t iter = 1000;
    
    struct timespec t0, t1;
    double totalTime = 0;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    printf("Training %lu times with %f training step\n", iter, trainingStep);
    for (size_t i = 0; i < iter; i++)
    {
        if (i % (iter / 10) == 0) {
            
            clock_gettime(CLOCK_MONOTONIC, &t1);
            printf("[%2g/10]: \t%fs\n", (double) i / (iter / 10), time_gdiff(t0, t1));
            totalTime += time_gdiff(t0, t1);
            clock_gettime(CLOCK_MONOTONIC, &t0);
        
            // printf("[%2g/10]\n",(double) i / (iter / 10));
        }
        //printf("Iter %lu: ", i);
        for (size_t testIndex = 0; testIndex < out; testIndex++) {
            //if (i % (iter / 10) == 0) {
            //    printArr(expectedResults + testIndex * net->count_nr[2], net->count_nr[2], "expected");
            //}
            //printf("%lu ", testIndex + 1);
            //net->computed[0] = trainingSet[2 * testIndex];
            //net->computed[1] = trainingSet[2 * testIndex + 1];
            for (size_t i = 0; i < net->count_nr[0]; i++)
                net->computed[i] = trainingSet[testIndex * net->count_nr[0] + i];

            // for (size_t i = 0; i < 5; i++)
            //     printf("computed[%lu] = %f  ", i, net->computed[i]);

            // printf("\t i = %lu\n", i);

            forwardPropagation(net);
            backPropagation(net, expectedResults, testIndex * net->count_nr[2], trainingStep);
        }
        //printf("\n");

    }
    clock_gettime(CLOCK_MONOTONIC, &t1);
    printf("[10/10]: \t%fs\n", time_gdiff(t0, t1));
    totalTime += time_gdiff(t0, t1);
    printf("Total time: \t%fs\n", totalTime);


    //////////////////////////////////
    ////////// FINAL TESTS ///////////
    //////////////////////////////////
    printArr(net->computed, net->count_nr[2] + net->count_nr[1] + net->count_nr[0], "computed Before");

    for (size_t i = 0; i < 2; i++) {
        testNetwork(net, trainingSet + i * in, expectedResults + (i * out), expectedChar, 1);
        //printArr(net->computed + net->count_nr[0] + net->count_nr[1], net->count_nr[2], "result");
    }
    printArr(net->computed, net->count_nr[2] + net->count_nr[1] + net->count_nr[0], "computed After");

    /*net->computed[0] = 0;
    net->computed[1] = 0;
    forwardPropagation(net);
    // printf("(0, 0) = %f\n", net->computed[4]);
    printArr(net->computed, net->count_nr[0] + net->count_nr[1] + net->count_nr[2], "(0, 0)");

    net->computed[0] = 0;
    net->computed[1] = 1;
    forwardPropagation(net);
    // printf("(0, 1) = %f\n", net->computed[4]);
    printArr(net->computed, net->count_nr[0] + net->count_nr[1] + net->count_nr[2], "(0, 1)");

    net->computed[0] = 1;
    net->computed[1] = 0;
    forwardPropagation(net);
    // printf("(1, 0) = %f\n", net->computed[4]);
    printArr(net->computed, net->count_nr[0] + net->count_nr[1] + net->count_nr[2], "(1, 0)");

    net->computed[0] = 1;
    net->computed[1] = 1;
    forwardPropagation(net);
    // printf("(1, 1) = %f\n", net->computed[4]);
    printArr(net->computed, net->count_nr[0] + net->count_nr[1] + net->count_nr[2], "(1, 1)");

    printArr(net->weights, net->count_nr[1] * (net->count_nr[0] + net->count_nr[2]), "weights");
    printArr(net->bias, 2, "bias");*/

    return 0;
}

    //////////////////////////////////
    ///// Network Initialization //
    //////////////////////////////////

void initNetwork(Network *net, unsigned int *count_nr) {
    net->computed = calloc(count_nr[0] + count_nr[1] + count_nr[2], sizeof(double));
    net->count_nr = count_nr;
    net->weights = calloc(count_nr[0] * count_nr[1] + count_nr[1] * count_nr[2], sizeof(double));
    net->bias = calloc(count_nr[1] + count_nr[2], sizeof(double));
    net->count_weight = calloc(2, sizeof(unsigned int));
    
    net->count_weight[0] = count_nr[0];
    net->count_weight[1] = count_nr[1];
    for (size_t i = 0; i < count_nr[0] * count_nr[1] + count_nr[1] * count_nr[2]; i++) {
        double r = (double)rand() / (double)(RAND_MAX / 1);
        net->weights[i] = r;
    }
    for (size_t i = 0; i < 2/*count_nr[1] + count_nr[2]*/; i++) {
        double r = (double)rand() / (double)(RAND_MAX / 1);        
        net->bias[i] = r;
    }
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
        net->computed[net->count_nr[0] + i] = sigmoid(sum + net->bias[0]);
    }

    // Output Layer
    
    for (size_t i = 0; i < net->count_nr[2]; i++) {
        double sum = 0.0;
        for (size_t j = 0; j < net->count_weight[1]; j++) {
            sum += net->computed[net->count_nr[0] + j] * net->weights[net->count_weight[0] * net->count_nr[1] + i * net->count_weight[1] + j];
        }
        net->computed[net->count_nr[0] + net->count_nr[1] + i] = sum + net->bias[/*net->count_nr[1] + i*/1];
    }

    softmax(net);
}

    //////////////////////////////////
    //////// BACKPROPAGATION /////////
    //////////////////////////////////

void backPropagation(Network *net, double expectedResults[], size_t resStart, double trainingStep) {
    double newWeights[net->count_weight[0] * net->count_nr[1] + net->count_weight[1] * net->count_nr[2]];
    double newBias[2] = {0, 0};
    double outputErrors[net->count_nr[2]];
    double hiddenErrors[net->count_nr[1]];
    
    // 1 - Output error
    size_t outputPos = net->count_nr[0] + net->count_nr[1];
    size_t outputWeightPos = net->count_nr[1] * net->count_weight[0];

    for (size_t i = 0; i < net->count_nr[2]; i++) {
        outputErrors[i] = (expectedResults[resStart + i] - net->computed[outputPos + i]) * transferDeriv(net->computed[outputPos + i]) ;
    }

    // 2 - Hidden layer errors

    for (size_t i = 0; i < net->count_nr[1]; i++) {
        double e = 0.0;
        for (size_t j = 0; j < net->count_nr[2]; j++) {
            e += net->weights[outputWeightPos + i + j * net->count_weight[1]] * outputErrors[j];
        }
        hiddenErrors[i] = e  * transferDeriv(net->computed[net->count_nr[0] + i]);
    }

    // 3 - Output new weights
    
    for (size_t i = 0; i < net->count_nr[2]; i++) {
        double w = trainingStep * outputErrors[i];
        for (size_t j = 0; j < net->count_weight[1]; j++)
            newWeights[outputWeightPos + i * net->count_weight[1] + j] = w * net->computed[net->count_nr[0] + j];
        newBias[/*net->count_nr[1] + i*/1] += w;
    }

    // 4 - Hidden new weights

    for (size_t i = 0; i < net->count_nr[1]; i++) {
        double w = trainingStep * hiddenErrors[i];
        for (size_t j = 0; j < net->count_weight[0]; j++)
            newWeights[i * net->count_weight[0] + j] = w * net->computed[j];
        newBias[/*i*/0] += w;
    }

    //printArr(newWeights, sizeof(newWeights) / sizeof(double), "newWeights");
    //printArr(newBias, sizeof(newBias) / sizeof(double), "newBias");

    for (size_t i = 0; i < sizeof(newWeights) / sizeof(double); i++) {
        net->weights[i] += newWeights[i];
    }
    for (size_t i = 0; i < sizeof(newBias) / sizeof(double); i++) {
        net->bias[i] += newBias[i] / net->count_nr[i + 1];
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

void softmax(Network *net) {

    double sum = 0.0;
    size_t pos = net->count_nr[0] + net->count_nr[1];
    for (size_t i = 0; i < net->count_nr[2]; i++) {
        sum += exp(net->computed[pos + i]);
    }

    for (size_t i = 0; i < net->count_nr[2]; i++) {
        net->computed[pos + i] = exp(net->computed[pos + i]) / sum;
    }

}

// Test
int testNetwork(Network *net, double *input, double *expectedResult, char *charList, int print) {
    for (size_t i = 0; i < net->count_nr[0]; i++)
        net->computed[i] = input[i];
    forwardPropagation(net);
    double *res = (net->computed) + net->count_nr[0] + net->count_nr[1];
    if (print) {
        printArr(input, net->count_nr[0], "input");
        printArr(res, net->count_nr[2], "output");
        printArr(expectedResult, net->count_nr[2], "expected");
    }
    size_t r = 0, e = 0;
    for (size_t i = 1; i < net->count_nr[2]; i++) {
        r = res[i] > res[r] ? i : r;
        e = expectedResult[i] > expectedResult[e] ? i : e;
    }
    printf("expected: %c, result: %c\n", charList[e], charList[r]);
    return charList[e] == charList[r];
}

// Save
/*
void saveNetwork(Network *net) {
    FILE *saveFile;
    saveFile = fopen("./network/save.txt", "w");

    if(saveFile == NULL){
        mkdir("./network", 0700);
        saveFile = fopen("./network/save.txt", "w");
    }

    //TODO
}*/

// Load