//
//  network.c
//  OCR Project
//

#define _GNU_SOURCE
#include "network.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){

    //////////////////////////////////
    ///////// TRAINING DATA //////////
    //////////////////////////////////

    /*int trainingSet[] = {0, 0, 0, 1, 1, 0, 1, 1};
    double expectedResults[] = {0, 1, 1, 0, 1, 0, 0, 1};*/
    double trainingStep = .1;

    FILE *f;
    f = fopen("./alphabeat.txt", "r");
    if (f == NULL) {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
    }
    unsigned int in = 100, out = 36;
    char expectedChar[36] = "abcdefghijklmnopqrstuvwxyz0123456789";
    double expectedResults[36 * 36]; //= {
    //     1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
    //     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1
    // };
    double trainingSet[100*36]; //= {
    //     0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,
    //     1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,0,
    //     0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,
    //     0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,0,1,0,1,1,1,0,0,0,1,1,1,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,0,1,
    //     0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,
    //     0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
    //     0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,1,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,1,1,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,0,
    //     1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,
    //     0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,
    //     0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,
    //     1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,
    //     1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,
    //     0,0,0,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,1,0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,0,0,1,
    //     0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,
    //     0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,0,
    //     0,0,0,0,0,1,1,0,0,0,1,1,0,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,
    //     0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,1,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,1,1,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
    //     0,0,0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
    //     0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,
    //     0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,
    //     1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,
    //     1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,1,1,0,0,0,
    //     1,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,1,0,0,1,0,0,1,1,0,1,1,0,0,1,0,0,1,1,0,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,1,1,0,1,1,1,0,0,0,1,1,0,0,0,1,1,0,
    //     0,1,1,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,
    //     1,1,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,1,1,0,0,1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,
    //     0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,
    //     0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,0,
    //     0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,
    //     0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,
    //     0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,
    //     0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,
    //     0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,
    //     0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,0,
    //     1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,
    //     0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,
    //     0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,0
    // };
    for (size_t i = 0; i < out; i++) {
        char *l = NULL;
        ssize_t size;
        ssize_t np = getline(&l, &size, f);
        np++;
        if (i == 0)
            printf("%s\n", l);
        expectedChar[i] = *l;
        for (size_t j = 0; j < out; j++) {
            expectedResults[i * out + j] = j == i;  
        }
        for (size_t j = 0; j < in; j++) {
            trainingSet[i * in + j] = *(l + 1 + j) - '0';
        }
    }

    //////////////////////////////////
    ////////// NETWORK INIT //////////
    //////////////////////////////////

    srand(time(NULL));

    Network n;
    Network *net = &n;

    unsigned int count_nr[] = {in, 100, out}; 

    initNetwork(net, count_nr);
    
    //printArr(net->weights, net->count_weight[0] * net->count_nr[1] + net->count_weight[1] * net->count_nr[2], "weights");
    //printArr(net->bias, net->count_nr[1] + net->count_nr[2], "bias");

    //////////////////////////////////
    ///////// INITALIZATION //////////
    //////////////////////////////////


    size_t testMaxCount = sizeof(expectedResults) / sizeof(expectedResults[0]) / net->count_nr[2];

    // Weights: [ in0.0,  in1.0, hid0.0, hid0.1, hid1.0, hid1.1, out0.0, out0.1]
    //          [ neur0,  neur1,  neur2,  neur2,  neur3,  neur3,  neur4,  neur4]
    //          [    w0,     w1,     w2,     w3,     w4,     w5,     w6,     w7]
    //          [i -> 0, i -> 1, 0 -> 2, 0 -> 3, 1 -> 2, 1 -> 3, 2 -> 4, 3 -> 4]


    //net->computed[0] = 1;
    //net->computed[1] = 1;
    /*double w[6] = {1.0, -1.0, -1.0, 1.0, 1.0, 1.0};
    net->weights = w;*/

    //forwardPropagation(net);
    //printf("prop(1,1) = %f\n", net->computed[4]);
    //printArr(net->computed, net->count_nr[0] + net->count_nr[1] + net->count_nr[2], "(1, 1)");    
    //net->computed[1] = 0;
    //forwardPropagation(net);
    //printf("prop(1,0) = %f\n", net->computed[4]);
    //printArr(net->computed, net->count_nr[0] + net->count_nr[1] + net->count_nr[2], "(1, 0)");

    //backPropagation(net, expectedResults, 1, .1);

    //return 0;
    
    size_t iter = 10000;
    
    struct timespec t0, t1;
    double totalTime = 0;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    printf("Training %lu times with %f training step\n", iter, trainingStep);
    for (size_t i = 0; i < iter; i++)
    {
        if (i % (iter / 10) == 0) {
            
            clock_gettime(CLOCK_MONOTONIC, &t1);
            printf("[%2g/10]: \t%fs\n", (double) i / (iter / 10), time_gdiff(t0, t1));
            totalTime += time_gdiff(t0, t1);
            clock_gettime(CLOCK_MONOTONIC, &t0);
        
            // printf("[%2g/10]\n",(double) i / (iter / 10));
        }
        //printf("Iter %lu: ", i);
        for (size_t testIndex = 26; testIndex < 36; testIndex++) {
            //if (i % (iter / 10) == 0) {
            //    printArr(expectedResults + testIndex * net->count_nr[2], net->count_nr[2], "expected");
            //}
            //printf("%lu ", testIndex + 1);
            //net->computed[0] = trainingSet[2 * testIndex];
            //net->computed[1] = trainingSet[2 * testIndex + 1];
            for (size_t i = 0; i < net->count_nr[0]; i++)
                net->computed[i] = trainingSet[testIndex * net->count_nr[0] + i];

            // for (size_t i = 0; i < 5; i++)
            //     printf("computed[%lu] = %f  ", i, net->computed[i]);

            // printf("\t i = %lu\n", i);
            //printArr(net->computed, net->count_nr[2] + net->count_nr[1] + net->count_nr[0], "computed Before");
            forwardPropagation(net);
            backPropagation(net, expectedResults, testIndex * 36, trainingStep);
            //printArr(net->computed, net->count_nr[2] + net->count_nr[1] + net->count_nr[0], "computed After");
        }
        //printf("\n");

    }
    clock_gettime(CLOCK_MONOTONIC, &t1);
    printf("[10/10]: \t%fs\n", time_gdiff(t0, t1));
    totalTime += time_gdiff(t0, t1);
    printf("Total time: \t%fs\n", totalTime);


    //////////////////////////////////
    ////////// FINAL TESTS ///////////
    //////////////////////////////////
    printArr(net->computed, net->count_nr[2] + net->count_nr[1] + net->count_nr[0], "computed Before");

    for (size_t i = 26; i < 36; i++) {
        testNetwork(net, trainingSet + i * in, expectedResults + (i * 36), expectedChar, 1);
        //printArr(net->computed + net->count_nr[0] + net->count_nr[1], net->count_nr[2], "result");
    }
    printArr(net->computed, net->count_nr[2] + net->count_nr[1] + net->count_nr[0], "computed After");
    printArr(net->weights, net->count_nr[1] * (net->count_nr[0] + net->count_nr[2]), "weights");
    printArr(net->bias, net->count_nr[1] + net->count_nr[2], "bias");

    saveNetwork(net);
    /*net->computed[0] = 0;
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

    printArr(net->weights, net->count_nr[1] * (net->count_nr[0] + net->count_nr[2]), "weights");
    printArr(net->bias, 2, "bias");*/

    return 0;
}

    //////////////////////////////////
    ///// Network Initialization //
    //////////////////////////////////

void initNetwork(Network *net, unsigned int *count_nr) {
    net->computed = calloc(count_nr[0] + count_nr[1] + count_nr[2], sizeof(double));
    net->count_nr = count_nr;
    net->weights = calloc(count_nr[0] * count_nr[1] + count_nr[1] * count_nr[2], sizeof(double));
    net->deltaw = calloc(count_nr[0] * count_nr[1] + count_nr[1] * count_nr[2], sizeof(double));
    net->bias = calloc(count_nr[1] + count_nr[2], sizeof(double));
    net->deltab = calloc(count_nr[1] + count_nr[2], sizeof(double));
    net->count_weight = calloc(count_nr[1] + count_nr[2], sizeof(unsigned int));
    
    net->count_weight[0] = count_nr[0];
    net->count_weight[1] = count_nr[1];
    for (size_t i = 0; i < count_nr[0] * count_nr[1] + count_nr[1] * count_nr[2]; i++) {
        double r = (double)rand() / (double)(RAND_MAX / 1);
        net->weights[i] = r;
    }
    for (size_t i = 0; i < count_nr[1] + count_nr[2]; i++) {
        double r = (double)rand() / (double)(RAND_MAX / 1);        
        net->bias[i] = r;
    }
}

    //////////////////////////////////
    // Forward Propagation function //
    //////////////////////////////////

void forwardPropagation(Network *net) {

    // Hidden Layer
    
    for (size_t i = 0; i < net->count_nr[1]; i++) {
        double sum = net->bias[i];
        for (size_t j = 0; j < net->count_weight[0]; j++) {
            sum += net->computed[j] * net->weights[i * net->count_weight[0] + j];
        }
        double temp = sum / net->count_nr[1] * 2;
        net->computed[net->count_nr[0] + i] = 1.0/(1.0 + exp(-temp));
        // printf("IN : temp: %f, exp: %f, compute: %f\n", temp, exp(-(temp)), net->computed[net->count_nr[0] + i]);
    }
    

    // Output Layer
    
    for (size_t i = 0; i < net->count_nr[2]; i++) {
        double sum = net->bias[net->count_nr[1] + i];
        for (size_t j = 0; j < net->count_weight[1]; j++) {
            sum += net->computed[net->count_nr[0] + j] * net->weights[net->count_weight[0] * net->count_nr[1] + i * net->count_weight[1] + j];
        }
        sum /= net->count_nr[2] / 2;
        net->computed[net->count_nr[0] + net->count_nr[1] + i] = 1.0 / (1.0 + exp(-sum));
        // printf("OUT: temp: %f, exp: %f, compute: %f\n", sum, exp(-(sum)), net->computed[net->count_nr[0] + net->count_nr[1] + i]);
    }

    //softmax(net);
}

    //////////////////////////////////
    //////// BACKPROPAGATION /////////
    //////////////////////////////////

void backPropagation(Network *net, double expectedResults[], size_t resStart, double trainingStep) {
    double newWeights[net->count_weight[0] * net->count_nr[1] + net->count_weight[1] * net->count_nr[2]];
    double newBias[net->count_nr[1] + net->count_nr[2]];
    double outputErrors[net->count_nr[2]];
    double hiddenErrors[net->count_nr[1]];
    
    // 1 - Output error
    size_t outputPos = net->count_nr[0] + net->count_nr[1];
    size_t outputWeightPos = net->count_nr[1] * net->count_weight[0];

    for (size_t i = 0; i < net->count_nr[2]; i++) {
        outputErrors[i] = (expectedResults[resStart + i] - net->computed[outputPos + i]) * transferDeriv(net->computed[outputPos + i]) ;
    }

    // 2 - Hidden layer errors

    for (size_t i = 0; i < net->count_nr[1]; i++) {
        double e = 0.0;
        /*for (size_t j = 0; j < net->count_nr[2]; j++) {
            e += net->weights[outputWeightPos + i + j * net->count_weight[1]] * outputErrors[j];
        }
        hiddenErrors[i] = e  * transferDeriv(net->computed[net->count_nr[0] + i]);*/
        for (size_t j = 0; j < net->count_nr[2]; j++) {
            e += net->weights[outputWeightPos + i + j * net->count_weight[1]] * outputErrors[j];
        }
        hiddenErrors[i] = e * net->computed[net->count_nr[0] + i] * (1.0 - net->computed[net->count_nr[0] + i]);
        net->deltab[i] = trainingStep * hiddenErrors[i] + 0.9 * net->deltab[i];
        net->bias[i] += net->deltab[i];

        for (size_t j = 0; j < net->count_nr[0]; j++) {
            net->deltaw[net->count_nr[0] * i + j] = trainingStep * hiddenErrors[i] * net->computed[j] + 0.9 * net->deltaw[net->count_nr[0] * i + j];
            net->weights[net->count_nr[0] * i + j] += net->deltaw[i];
        }
    }

    for (size_t i = 0; i < net->count_nr[2]; i++) {
        net->deltab[net->count_nr[1] + i] = trainingStep * outputErrors[i] + 0.9 * net->deltab[net->count_nr[1] + i];
        net->bias[net->count_nr[1] + i] += net->deltab[net->count_nr[1] + i];
        for (size_t j = 0; j < net->count_nr[1]; j++) {
            net->deltaw[net->count_nr[0] * net->count_nr[1] + net->count_nr[1] * i + j] = trainingStep * net->computed[net->count_nr[0] + j] * outputErrors[i] + 0.9 * net->deltaw[net->count_nr[0] * net->count_nr[1] + net->count_nr[1] * i + j];
            net->weights[net->count_nr[0] * net->count_nr[1] + net->count_nr[1] * i + j] += net->deltaw[net->count_nr[0] * net->count_nr[1] + net->count_nr[1] * i + j];
        }
    }
/*
    // 3 - Output new weights
    
    for (size_t i = 0; i < net->count_nr[2]; i++) {
        double w = trainingStep * outputErrors[i];
        for (size_t j = 0; j < net->count_weight[1]; j++)
            newWeights[outputWeightPos + i * net->count_weight[1] + j] = w; // * net->computed[net->count_nr[0] + j];
        newBias[net->count_nr[1] + i] = w;
    }

    // 4 - Hidden new weights

    for (size_t i = 0; i < net->count_nr[1]; i++) {
        double w = trainingStep * hiddenErrors[i];
        for (size_t j = 0; j < net->count_weight[0]; j++)
            newWeights[i * net->count_weight[0] + j] = w; // * net->computed[j];
        newBias[i] = w;
    }

    //printArr(newWeights, sizeof(newWeights) / sizeof(double), "newWeights");
    //printArr(newBias, sizeof(newBias) / sizeof(double), "newBias");

    for (size_t i = 0; i < sizeof(newWeights) / sizeof(double); i++) {
        net->deltaw[i] = newWeights[i] + 0.9 * net->deltaw[i];
        net->weights[i] += net->deltaw[i];
    }
    for (size_t i = 0; i < sizeof(newBias) / sizeof(double); i++) {
        net->deltab[i] = newBias[i] + 0.9 * net->deltab[i];
        net->bias[i] += net->deltab[i];
    }*/
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

// Test
int testNetwork(Network *net, double *input, double *expectedResult, char *charList, int print) {
    for (size_t i = 0; i < net->count_nr[0]; i++)
        net->computed[i] = input[i];
    forwardPropagation(net);
    double *res = (net->computed) + net->count_nr[0] + net->count_nr[1];
    if (print) {
        printArr(input, net->count_nr[0], "input");
        printArr(res, net->count_nr[2], "output");
        printArr(expectedResult, net->count_nr[2], "expected");
    }
    size_t r = 0, e = 0;
    for (size_t i = 1; i < net->count_nr[2]; i++) {
        r = res[i] > res[r] ? i : r;
        e = expectedResult[i] > expectedResult[e] ? i : e;
    }
    printf("expected: %c, result: %c\n", charList[e], charList[r]);
    return charList[e] == charList[r];
}

// Save

void saveInt(FILE *file, unsigned int number){
    unsigned int temp = number;
    unsigned int nb = 0;
    while (temp > 0){
        temp /=10;
        nb++;
    }
    temp = number;
    while(nb > 1){
        fputc(temp / (unsigned int) powl(10, nb - 1) + 48, file);
        temp %= (unsigned int) powl(10, nb - 1);
        nb--;
    }
    fputc(temp % 10 + 48, file);
}

void saveFloat(FILE *file, double number){
    //NEG
    if (number < 0){
        fprintf(file, "-");
        number = -number;
    }

    unsigned int ipart = (unsigned int)number;
    double fpart = number - (double)ipart;

    saveInt(file, ipart);
    fprintf(file, ".");

    //FLOAT
    unsigned int afterpoint = 6;
    if (afterpoint != 0){
        fpart = fpart * powl(10, afterpoint);
        saveInt(file, (unsigned int)fpart);
    }
}

void saveNetwork(Network *net) {
    FILE *saveFile;
    saveFile = fopen("./save.txt", "w");

    for (size_t i = 0; i < 3; i++){
        saveInt(saveFile, net->count_nr[i]);
        fprintf(saveFile, "\n");
    }

    for (size_t i = 0; i < net->count_nr[1] + net->count_nr[2]; i++){
        saveFloat(saveFile, net->bias[i]);
        fprintf(saveFile, "\n");
    }

    for (size_t i = 0; i < net->count_nr[1] * (net->count_nr[0] + net->count_nr[2]); i++){
        saveFloat(saveFile, net->weights[i]);
        fprintf(saveFile, "\n");
    }
}

// Load

void loadNetwork (Network *network){
    FILE *loadFile;
    loadFile = fopen("./save.txt", "r");

    for (size_t i = 0; i < 3; i++){
        char *line = NULL;
        ssize_t len = 0;
        ssize_t np = getline(&line, &len, loadFile);
        np++;
        sscanf(line, "%d", &network->count_nr[i]);
    }

    for (size_t i = 0; i < network->count_nr[1] + network->count_nr[2]; i++){
        char *line = NULL;
        ssize_t len = 0;
        ssize_t np = getline(&line, &len, loadFile);
        np++;
        sscanf(line, "%le", &network->bias[i]);
    }

    for (size_t i = 0; i < network->count_nr[1] * (network->count_nr[0] + network->count_nr[2]); i++){
        char *line = NULL;
        ssize_t len = 0;
        ssize_t np = getline(&line, &len, loadFile);
        np++;
        sscanf(line, "%le", &network->weights[i]);
    }
}