//
//  network.h
//  OCR Project
//

# ifndef NETWORK_H
# define NETWORK_H
#define _GNU_SOURCE
#include "network.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

// Structure for the Neural Network
typedef struct Network Network;
struct Network {

    double *computed;       // Computed values array
    double *weights;        // Weights array
    double *bias;           // Biases array
    double *deltaw;
    double *deltab;
    unsigned int *count_nr;       // Neuron count by layer array
    unsigned int *count_weight;   // Weights count by neuron by layer array
 
};

void forwardPropagation(Network  *net);
void backPropagation(Network *net, double expectedResults[], size_t resStart, double trainingStep);
void initNetwork(Network *net, unsigned int *count_nr);

static inline
double time_gdiff(struct timespec t0, struct timespec t1)
{
  double s = t1.tv_sec - t0.tv_sec;
  return s + (t1.tv_nsec - t0.tv_nsec) * 1e-9;
}

double sigmoid(double z);
double transferDeriv(double x);
void softmax(Network *net);
void printArr(double arr[], size_t count, char name[]);
int testNetwork(Network *net, double *input, double *expectedResult, char *charList, int print);
void saveNetwork(Network *net);
void loadNetwork (Network *network);
void saveInt(FILE *file, unsigned int number);
void saveFloat(FILE *file, double number);

#endif
