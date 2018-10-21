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

    double *computed;       // Tableau des valeurs calculées
    double *weights;        // Tableau des poids
    double *bias;           // Tableau des bias
    double *count_nr;       // Tableau des nombres de neuronnes par couches
    double *count_weight;   // Tableau des nombres de weights par neuronnes
    
};

void forwardPropagation(Network net, unsigned int propPrint);

double sigmoid(double z);
void printArr(double arr[], size_t count, char name[]);
#endif
