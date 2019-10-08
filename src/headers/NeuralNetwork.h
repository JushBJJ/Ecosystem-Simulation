#ifndef NN_H
#define NN_H
#include <stdio.h>
#include <stdbool.h>
#include <Organisms.h>

typedef struct NeuralNetwork
{

    // (3*2) + 2
    /*
          #
          #
      ####O####
          #
          #
    */
    size_t ID;
    size_t TotalPoints;
    wchar_t Range[4]; // Input

    struct NeuralNetwork *next;
    struct NeuralNetwork *prev;
} NeuralNetwork;

float Sigmoid(float x);
int NN(Organism *o, NeuralNetwork *LocalNN);
NeuralNetwork *GetNN(size_t ID);
void UpdateNeuralNetwork(NeuralNetwork *N);
void Destroy_NNS(bool EXIT);
NeuralNetwork *NewNN(void);

#endif