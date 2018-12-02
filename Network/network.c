//
//  network.c
//  OCR Project
//

#include "network.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

int main(){

    //////////////////////////////////
    ///////// TRAINING DATA //////////
    //////////////////////////////////

    int trainingSet[] = {0, 0, 0, 1, 1, 0, 1, 1};
    double expectedResults[] = {0, 1, 1, 0, 1, 0, 0, 1};
    double trainingStep = 0.1;

    //////////////////////////////////
    ////////// NETWORK INIT //////////
    //////////////////////////////////

    srand(time(NULL));

    Network n;
    Network *net = &n;

    unsigned int count_nr[] = {2, 2, 1}; 

    initNetwork(net, count_nr);
    
    printArr(net->weights, net->count_weight[0] * net->count_weight[0] + net->count_weight[1] * net->count_nr[1] + net->count_weight[2] * net->count_nr[2], "weights");
    printArr(net->bias, net->count_nr[0] + net->count_nr[1] + net->count_nr[2], "bias");
    
    printf("%s: [%i","count_nr", count_nr[0]);
    for (size_t i = 1; i < 3; i++)
        printf(", %i", count_nr[i]);
    printf("]\n");

    printf("%s: [%i","count_weight", net->count_weight[0]);
    for (size_t i = 1; i < 3; i++)
        printf(", %i", net->count_weight[i]);
    printf("]\n");


    //////////////////////////////////
    ///////// INITALIZATION //////////
    //////////////////////////////////


    size_t testMaxCount = sizeof(expectedResults) / sizeof(expectedResults[0]) / net->count_nr[2];

    // Weights: [ in0.0,  in1.0, hid0.0, hid0.1, hid1.0, hid1.1, out0.0, out0.1]
    //          [ neur0,  neur1,  neur2,  neur2,  neur3,  neur3,  neur4,  neur4]
    //          [    w0,     w1,     w2,     w3,     w4,     w5,     w6,     w7]
    //          [i -> 0, i -> 1, 0 -> 2, 0 -> 3, 1 -> 2, 1 -> 3, 2 -> 4, 3 -> 4]


    // net->computed[0] = 1;
    // net->computed[1] = 1;

    net->inputs = (trainingSet + 3 * net->count_nr[0]);

    /*double w[6] = {1.0, -1.0, -1.0, 1.0, 1.0, 1.0};
    net->weights = w;*/

    forwardPropagation(net);
    //printf("prop(1,1) = %f\n", net->computed[4]);
    printf("(%i, %i)", net->inputs[0], net->inputs[1]); // (1, 1)
    printArr(net->computed, net->count_nr[0] + net->count_nr[1] + net->count_nr[2], "");
    //net->computed[1] = 0;
    net->inputs = (trainingSet + 2 * net->count_nr[0]);
    forwardPropagation(net);
    //printf("prop(1,0) = %f\n", net->computed[4]);
    printf("(%i, %i)", net->inputs[0], net->inputs[1]); // (1, 0)
    printArr(net->computed, net->count_nr[0] + net->count_nr[1] + net->count_nr[2], "");

    //backPropagation(net, expectedResults, 1, .1);

    //return 0;

    size_t iter = 1000000;  //10000000;

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    printf("Training %lu times with %f training step\n", iter, trainingStep);
    for (size_t i = 0; i < iter; i++)
    {

        // trainingStep -= 0.0000001;

        if (net->global_error < 0.001)
            break;

        if (i % (iter / 10) == 0) {
            
            clock_gettime(CLOCK_MONOTONIC, &t1);
            printf("[%2g/10]: \t%f s\n", (double) i / (iter / 10), time_gdiff(t0, t1));
            clock_gettime(CLOCK_MONOTONIC, &t0);

        }
        
        for (size_t testIndex = 0; testIndex < testMaxCount; testIndex++) {
            net->inputs = (trainingSet + testIndex * net->count_nr[0]);

            net->global_error = 0.0;

            forwardPropagation(net);
            backPropagation(net, expectedResults, testIndex * net->count_nr[2], trainingStep);
        }
        
    }
    clock_gettime(CLOCK_MONOTONIC, &t1);
    printf("[10/10]: \t%f s\n", time_gdiff(t0, t1));

    //////////////////////////////////
    ////////// FINAL TESTS ///////////
    //////////////////////////////////

    for (size_t testIndex = 0; testIndex < 4; testIndex++) {

        net->inputs = (trainingSet + testIndex * net->count_nr[0]);

        forwardPropagation(net);
        printf("(%i, %i)", trainingSet[testIndex * 2], trainingSet[testIndex * 2 + 1]);
        printArr(net->computed, net->count_nr[0] + net->count_nr[1] + net->count_nr[2], "");
    }
    
    printArr(net->weights, net->count_nr[1] * (net->count_nr[0] + net->count_nr[2]) + net->count_nr[0], "weights");
    printArr(net->bias, 2, "bias");

    printf("Global Error = %f\n", net->global_error);

    return 0;
}


void initNetwork(Network *net, unsigned int *count_nr) {
    
    net->computed = calloc(count_nr[0] + count_nr[1] + count_nr[2], sizeof(double));
    net->count_nr = count_nr;
    net->weights = calloc(count_nr[1] *(count_nr[0] + count_nr[2]) + count_nr[0], sizeof(double));
    net->bias = calloc(2, sizeof(double)); // calloc(count_nr[0] + count_nr[1] + count_nr[2], sizeof(double));
    net->count_weight = calloc(3, sizeof(unsigned int));

    net->outputErrors = calloc(count_nr[2], sizeof(double));
    net->hiddenErrors = calloc(count_nr[1], sizeof(double));

    net->count_weight[0] = 1;
    net->count_weight[1] = count_nr[0];
    net->count_weight[2] = count_nr[1];

    int nbIn2Hid = net->count_nr[0] * net->count_weight[0] + net->count_nr[1] * net->count_weight[1];
    int nbHid2Out = net->count_nr[1] * net->count_weight[1] + net->count_nr[2] * net->count_weight[2];

    double deltaWeightIn2Hid[nbIn2Hid];
    double deltaWeightHid2Out[nbHid2Out];

    for (size_t i = 0; i < nbIn2Hid; i++) {
        deltaWeightIn2Hid[i] = 0.0;
    }

    for (size_t i = 0; i < nbHid2Out; i++) {
        deltaWeightHid2Out[i] = 0.0;
    }

    net->deltaWeightIn2Hid = deltaWeightIn2Hid;
    net->deltaWeightHid2Out = deltaWeightHid2Out;

    net->global_error = 1.0;

    for (size_t i = 0; i < count_nr[1] *(count_nr[0] + count_nr[2]) + count_nr[0]; i++)
    {
        // double r = (double)rand() / (double)(RAND_MAX / 10);
        // double r = fmod((double) rand() / (double)RAND_MAX, 3) + (-1);
        // double r = (double)rand() / (double)RAND_MAX;        
        // int r = rand() % 2;

        double r = (double)(rand() % 100);

        double neg_rand = 1;
        if (rand() % 2)
            neg_rand = -1;

        net->weights[i] = (r * neg_rand / 100.0); // == 0 ? 1 : -1;
    }
    for (size_t i = 0; i < count_nr[0] + count_nr[1] + count_nr[2]; i++) {
        // double r = (double)rand() / (double)(RAND_MAX / 10);
        // double r = fmod((double)rand() / (double)RAND_MAX, 3) + (-1);
        // double r = (double)rand() / (double)RAND_MAX;
        
        double r = (double)(rand() % 100);

        double neg_rand = 1;
        if (rand() % 2)
            neg_rand = -1;
        
        net->bias[i] = (r * neg_rand / 100.0);
    }
}

    //////////////////////////////////
    // Forward Propagation function //
    //////////////////////////////////

void forwardPropagation(Network *net) {
    
    // Input Layer
    for (size_t i = 0; i < net->count_nr[0]; i++) {
        net->computed[i] = net->inputs[i];
    }

    // Hidden Layer
    
    for (size_t i = 0; i < net->count_nr[1]; i++) {
        double sum = 0.0;
        for (size_t j = 0; j < net->count_weight[1]; j++) {
            sum += net->computed[j] * net->weights[net->count_nr[0] * net->count_weight[0] + i * net->count_weight[1] + j];
        }
        net->computed[net->count_nr[0] + i] = sigmoid(sum + net->bias[net->count_nr[0] + i]);
    }

    // Output Layer
    
    for (size_t i = 0; i < net->count_nr[2]; i++) {
        double sum = 0.0;
        for (size_t j = 0; j < net->count_weight[2]; j++) {
            sum += net->computed[net->count_nr[0] + j] * net->weights[net->count_nr[0] * net->count_weight[0] + net->count_nr[1] * net->count_weight[1] + i * net->count_weight[2] + j];
        }
        // net->computed[net->count_nr[0] + net->count_nr[1] + i] = sum + net->bias[net->count_nr[0] + net->count_nr[1] + i];
        net->computed[net->count_nr[0] + net->count_nr[1] + i] = sigmoid(sum + net->bias[net->count_nr[0] + net->count_nr[1] + i]);
    }

    // softmax(net);

}
    //////////////////////////////////
    //////// BACKPROPAGATION /////////
    //////////////////////////////////

void backPropagation(Network *net, double expectedResults[], size_t resStart, double trainingStep) {

    double alpha = 0.9;
    
    // Delta Output
    for (size_t i = 0; i < net->count_nr[2]; i++) {
        double e = 0.0;
        for (size_t j = 0; j < net->count_nr[2]; j++) {
            double target = expectedResults[resStart + i];
            double output = net->computed[net->count_nr[0] + net->count_nr[1] + i];
            e += (target - output) * transferDeriv(output);
            net->global_error += 0.5 * (target - output) * (target - output);
        }
        net->outputErrors[i] = e;
    }

    for (size_t i = 0; i < net->count_nr[1]; i++) {

        double e = 0.0;

        for (size_t j = 0; j < net->count_nr[2]; j++) {
            e += net->weights[net->count_nr[0] * net->count_weight[0] + net->count_nr[1] * net->count_weight[1] + i * net->count_nr[2] + j] * net->outputErrors[j];
        }

        double delta = e * transferDeriv(net->computed[net->count_nr[0] + i]);

        net->deltaWeightIn2Hid[0] = trainingStep * delta + alpha * net->deltaWeightIn2Hid[0];
        net->weights[net->count_nr[0] * net->count_weight[0]] += net->deltaWeightIn2Hid[0];

        for (size_t j = 0; j < net->count_nr[0]; j++) {
            net->deltaWeightIn2Hid[i] = trainingStep * net->computed[i] * delta + alpha * net->deltaWeightIn2Hid[i];
            net->weights[net->count_nr[0] * net->count_weight[0] + i * net->count_nr[1] + j] += net->deltaWeightIn2Hid[i];
        }
    }

    for (size_t i = 0; i < net->count_nr[2]; i++) {
        for (size_t j = 0; j < net->count_nr[1]; j++) {
            net->deltaWeightHid2Out[j] = trainingStep * net->computed[net->count_nr[0] + j] * net->outputErrors[i] + alpha * net->deltaWeightHid2Out[j];
            net->weights[net->count_nr[0] * net->count_weight[0] + net->count_nr[1] * net->count_weight[1] + i * net->count_nr[2] + j] += net->deltaWeightHid2Out[i];
        }
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
