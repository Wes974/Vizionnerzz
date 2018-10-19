//
//  network.c
//  OCR Project
//

#include "network.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(){

    Network n;

    n.NumHidden = 0;



}


struct Network createXOR() {

    Network xor;
    xor.NumInput = 2;
    xor.NumHidden = 2;
    xor.NumOutput = 1;
    
    

}

double sigmoid(double z) {
    return 1.0 / (1.0 + exp(- z));
}

void fillNeurons(Malo arr[], int count) {

    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        Malo neur;
        neur.bias = (float)rand()/(float)(RAND_MAX/5) 
    }

}
