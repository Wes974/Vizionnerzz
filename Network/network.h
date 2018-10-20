//
//  network.h
//  OCR Project
//

# ifndef NETWORK_H
# define NETWORK_H
#include <stddef.h>


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

};

Network createXOR();

double sigmoid();

Malo * fillNeurons(size_t count);

#endif
