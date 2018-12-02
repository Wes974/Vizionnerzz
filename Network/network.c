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
    double trainingStep = .01;

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
    
    size_t iter = 10000000;
    
    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    printf("Training %lu times with %f training step\n", iter, trainingStep);
    for (size_t i = 0; i < iter; i++)
    {

        // trainingStep -= 0.0000001;

        if (i % (iter / 10) == 0) {
            
            clock_gettime(CLOCK_MONOTONIC, &t1);
            printf("[%2g/10]: \t%f s\n", (double) i / (iter / 10), time_gdiff(t0, t1));
            clock_gettime(CLOCK_MONOTONIC, &t0);

            printf("training step = %f\n", trainingStep);

            printf("Weights");

            for (size_t i = 0; i < net->count_weight[0] * net->count_nr[0] + net->count_weight[1] * net->count_nr[1] + net->count_weight[2] * net->count_nr[2]; i++)
            {
                printf("W[%lu] = %f  ", i, net->weights[i]);
            }

            printf("\nBias\n");

            for (size_t i = 0; i < net->count_nr[0] + net->count_nr[1] + net->count_nr[2]; i++)
            {
                printf("B[%lu] = %f  ", i, net->bias[i]);
            }

            printf("\nComputed\n");

            for (size_t i = 0; i < net->count_nr[0] + net->count_nr[1] + net->count_nr[2]; i++) {
                printf("C[%lu] = %f  ", i, net->computed[i]);
            }

            printf("\n");

            // printf("[%2g/10]\n",(double) i / (iter / 10));
        }
        //printf("Iter %lu: ", i);
        for (size_t testIndex = 0; testIndex < testMaxCount; testIndex++) {
            //printf("%lu ", testIndex + 1);
            // net->computed[0] = trainingSet[2 * testIndex];
            // net->computed[1] = trainingSet[2 * testIndex + 1];

            net->inputs = (trainingSet + testIndex * net->count_nr[0]);

            // for (size_t i = 0; i < 5; i++)
            //     printf("computed[%lu] = %f  ", i, net->computed[i]);

            // printf("\t i = %lu\n", i);

            forwardPropagation(net);
            backPropagation(net, expectedResults, testIndex * net->count_nr[2], trainingStep);
        }
        //printf("\n");

    }
    clock_gettime(CLOCK_MONOTONIC, &t1);
    printf("[10/10]: \t%f s\n", time_gdiff(t0, t1));


    //////////////////////////////////
    ////////// FINAL TESTS ///////////
    //////////////////////////////////

    net->computed[0] = 0;
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

    printArr(net->weights, net->count_nr[1] * (net->count_nr[0] + net->count_nr[2]) + net->count_nr[0], "weights");
    printArr(net->bias, net->count_nr[0] + net->count_nr[1] + net->count_nr[2], "bias");

    return 0;
}


void initNetwork(Network *net, unsigned int *count_nr) {
    net->computed = calloc(count_nr[0] + count_nr[1] + count_nr[2], sizeof(double));
    net->count_nr = count_nr;
    net->weights = calloc(count_nr[1] *(count_nr[0] + count_nr[2]) + count_nr[0], sizeof(double));
    net->bias = calloc(count_nr[0] + count_nr[1] + count_nr[2], sizeof(double));
    net->count_weight = calloc(3, sizeof(unsigned int));

    net->count_weight[0] = 1;
    net->count_weight[1] = count_nr[0];
    net->count_weight[2] = count_nr[1];

    for (size_t i = 0; i < count_nr[1] *(count_nr[0] + count_nr[2]) + count_nr[0]; i++)
    {
        double r = (double)rand() / (double)(RAND_MAX / 10);
        // double r = fmod((double) rand() / (double)RAND_MAX, 3) + (-1);
        net->weights[i] = r;
    }
    for (size_t i = 0; i < count_nr[0] + count_nr[1] + count_nr[2]; i++) {
        double r = (double)rand() / (double)(RAND_MAX / 10);
        // double r = fmod((double)rand() / (double)RAND_MAX, 3) + (-1);
        net->bias[i] = r;
    }
}

    //////////////////////////////////
    // Forward Propagation function //
    //////////////////////////////////

void forwardPropagation(Network *net) {

    // Input Layer
    for (size_t i = 0; i < net->count_nr[0]; i++) {
        net->computed[i] = sigmoid(net->weights[i] * net->inputs[i] + net->bias[i]);
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
    
    double newWeights[net->count_nr[1] * (net->count_nr[0] + net->count_nr[2]) + net->count_nr[0]];
    double newBias[net->count_nr[0] + net->count_nr[1] + net->count_nr[2]];
    double outputErrors[net->count_nr[2]];
    double hiddenErrors[net->count_nr[1]];
    double inputErrors[net->count_nr[0]];


    // 1 - Output Layer error and Hidden layer weight change:
    
        // 1.1 - Output layer error

    for (size_t i = 0; i < net->count_nr[2]; i++) {
        double e = 0.0;
        for (size_t j = 0; j < net->count_nr[2]; j++) {
            double target = expectedResults[resStart + i];
            double output = net->computed[net->count_nr[0] + net->count_nr[1] + i];
            e += -(target - output) * transferDeriv(output);
        }
        outputErrors[i] = e;
    }

        // 1.2 - Hidden layer weight update

    for (size_t i = 0; i < net->count_nr[2]; i++) {
        for (size_t j = 0; j < net->count_nr[1]; j++) {
            int pos = net->count_nr[0] * net->count_weight[0] + j * net->count_weight[1];
            net->weights[pos] = net->weights[pos] - trainingStep * outputErrors[i];
        }
    }

    // 2 - Hidden layer error and Input layer weight change:

        // 2.1 - Hidden layer error

    // double etotal = 0.0;
    
    // for (size_t i = 0; i < net->count_nr[2]; i++) {
    //     double e;
    //     e = outputErrors[i] * net->weights[net->count_nr[0] * net->count_weight[0] + net->count_nr[1] * net->count_weight[1] + i * net->count_weight[2]];
    //     hiddenErrors[i] = e;
    //     etotal += e;
    // }

    for (size_t i = 0; i < net->count_nr[1]; i++) {
        double e = 0.0;
        for (size_t j = 0; j < net->count_nr[2]; j++) {
            e += outputErrors[j] * net->weights[net->count_nr[0] * net->count_weight[0] + net->count_nr[1] * net->count_weight[1] + i * net->count_weight[2]];
        }

        double outh = transferDeriv(sigmoid(net->computed[net->count_nr[0] + i]));

        double neth = net->computed[0 + i];

        hiddenErrors[i] = e * outh * neth;
    }

    // double outh1 = transferDeriv(sigmoid(net->computed[net->count_nr[0]]));

    // double neth1 = net->computed[0];

    // etotal = etotal * outh1 * neth1;

        // 2.2 - Hidden layer weight update

    for (size_t i = 0; i < net->count_nr[1]; i++) {
        for (size_t j = 0; i < net->count_nr[0]; j++) {
            int pos = j * net->count_nr[0];
            net->weights[pos] = net->weights[pos] - trainingStep * hiddenErrors[i];
        }
    }


    /*

    // 1 - Output error
    size_t outputPos = net->count_nr[0] + net->count_nr[1];
    size_t outputWeightPos = net->count_nr[0] * net->count_weight[0] + net->count_nr[1] * net->count_weight[1];

    

    for (size_t i = 0; i < net->count_nr[2]; i++) {
        outputErrors[i] = (expectedResults[resStart + i] - net->computed[outputPos + i]) * transferDeriv(net->computed[outputPos + i]) ;
    }

    // 2 - Hidden layer errors

    for (size_t i = 0; i < net->count_nr[1]; i++) {
        double e = 0.0;
        for (size_t j = 0; j < net->count_nr[2]; j++) {
            e += net->weights[outputWeightPos + i + j * net->count_weight[2]] * outputErrors[j];
        }
        hiddenErrors[i] = e  * transferDeriv(net->computed[net->count_nr[0] + i]);
    }

    // 3 - Input layer errors

    for (size_t i = 0; i < net->count_nr[0]; i++) {
        double e = 0.0;
        for (size_t j = 0; j < net->count_nr[1]; j++) {
            e += net->weights[net->count_nr[0] + i + j * net->count_weight[1]] * hiddenErrors[j];
        }
        inputErrors[i] = e  * transferDeriv(net->computed[i]);
    }

    // 4 - Output new weights
    
    for (size_t i = 0; i < net->count_nr[2]; i++) {
        double w = trainingStep * outputErrors[i];
        for (size_t j = 0; j < net->count_weight[2]; j++)
            newWeights[outputWeightPos + i * net->count_weight[2] + j] = w * net->computed[net->count_nr[0] + j];
        newBias[net->count_nr[0] + net->count_nr[1] + i] = w;
    }

    // 5 - Hidden new weights

    for (size_t i = 0; i < net->count_nr[1]; i++) {
        double w = trainingStep * hiddenErrors[i];
        for (size_t j = 0; j < net->count_weight[1]; j++)
            newWeights[net->count_nr[0] * net->count_weight[0] + net->count_weight[1] * i + j] = w * net->computed[j];
        newBias[net->count_nr[0] + i] = w;
    }

    // 6 - Input new weights

    for (size_t i = 0; i < net->count_nr[0]; i++) {
        double w = trainingStep * inputErrors[i];
        for (size_t j = 0; j < net->count_weight[0]; j++)
            newWeights[net->count_weight[0] * i + j] = w * net->inputs[j];
        newBias[i] = w;
    }

    for (size_t i = 0; i < sizeof(newWeights) / sizeof(double); i++) {
        net->weights[i] = net->weights[i] + newWeights[i];
    }
    for (size_t i = 0; i < sizeof(newBias) / sizeof(double); i++) {
        net->bias[i] = (net->bias[i] + newBias[i]);
    }

    */

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
