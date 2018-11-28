//
//  network.h
//  OCR Project
//

# ifndef NETWORK_H
# define NETWORK_H
#include <stddef.h>

// Structure for the Neural Network
typedef struct Network Network;
struct Network {

    double *computed;       // Computed values array
    double *weights;        // Weights array
    double *bias;           // Biases array
    unsigned int *count_nr;       // Neuron count by layer array
    unsigned int *count_weight;   // Weights count by neuron by layer array
 
};

void forwardPropagation(Network  *net);
void backPropagation(Network *net, double expectedResults[], size_t resStart, double trainingStep);

double sigmoid(double z);
double transferDeriv(double x);
void printArr(double arr[], size_t count, char name[]);
#endif
