//
//  network.h
//  OCR Project
//

# ifndef NETWORK_H
# define NETWORK_H
#include <stddef.h>
#include <time.h>

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
void initNetwork(Network *net, unsigned int *count_nr);

static inline
double time_gdiff(struct timespec t0, struct timespec t1)
{
  double s = t1.tv_sec - t0.tv_sec;
  return s + (t1.tv_nsec - t0.tv_nsec) * 1e-9;
}

double sigmoid(double z);
double transferDeriv(double x);
void printArr(double arr[], size_t count, char name[]);
#endif
