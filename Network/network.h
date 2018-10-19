//
//  network.h
//  OCR Project
//

# ifndef NETWORK_H
# define NETWORK_H

typedef struct Malo Malo;
struct Malo {

    float *bias;
    float *weight;

};

typedef struct Network Network;
struct Network {
    
    int NumInput;   // Number of input neurons
    int NumHidden;  // Number of hidden neurons
    int NumOutput;  // Number of output neurons
    // NumOutput = number of chars ?

    Malo input[];
    Malo output[];
    Malo hidden[];

};


struct Network createXOR();

double sigmoid();

void fillNeurons(Malo arr[]; int count);

#endif
