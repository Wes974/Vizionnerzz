//
//  network.h
//  OCR Project
//

# ifndef NETWORK_H
# define NETWORK_H
#include <stddef.h>

/*

typedef struct Malo Malo;
struct Malo {

    float bias;
    float weight;

};

typedef struct Network Network;
struct Network {
    
    size_t NumInput;   // Number of input neurons
    size_t NumHidden;  // Number of hidden neurons
    size_t NumOutput;  // Number of output neurons

    Malo *input;
    Malo *hidden;
    Malo *output;

    float **biasArray;
    
};


Network createXOR();

double sigmoid();

Malo *fillNeurons(size_t count);

float *forwardPropagation(Network net);

*/

// Structure for the Neural Network
typedef struct Network Network;
struct Network {

    double *computed;       // Tableau des valeurs calculées
    double *weights;        // Tableau des poids
    double *bias;          // Tableau des biais
    double *count_nr;       // Tableau des nombres de neuronnes par couches
    double *count_weight;   // Tableau des nombres de weights par neuronnes
    


};


Network createXOR();
void fillArray(double *arr[], size_t count, size_t inputSize);
void InitXOR();
/*
 * TEMPORARY TYPES
 */
void forwardPropagation();


#endif
