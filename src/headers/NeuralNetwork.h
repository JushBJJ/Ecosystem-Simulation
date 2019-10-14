#ifndef NN_H
#define NN_H
#include <stdio.h>
#include <stdbool.h>
#include <Organisms.h>

#define defaultInputLayerSize 8
#define defaultOutputLayerSize 9
#define defaultHiddenLayerSize 16

#define getrandom(min, max) (float)(max - min) * ((float)rand() / RAND_MAX) + (float)min

enum Nodes
{
    UPLEFT_N,
    UP_N,
    UPRIGHT_N,
    LEFT_N,
    RIGHT_N,
    DOWNLEFT_N,
    DOWN_N,
    DOWNRIGHT_N,
    STATIONARY_N
};

typedef struct Input_Node
{
    float *Synapse_Weight;
} Input_Node;

typedef struct Hidden_Node
{
    float *Synapse_Weight;
} Hidden_Node;

typedef struct NNInput
{
    wchar_t Range[defaultInputLayerSize - 1];
} NNInput;

typedef struct NeuralNetwork
{

    // (3*2) + 2
    /*
         ###
         #O#
         ###
    */
    size_t ID;
    size_t Fitness;

    bool Made;

    NNInput Input;
    Hidden_Node HNN[defaultHiddenLayerSize - 1];
    Input_Node INN[defaultInputLayerSize - 1];

    float Weight1[defaultHiddenLayerSize * defaultInputLayerSize - 1];
    float Weight2[defaultHiddenLayerSize * defaultOutputLayerSize - 1];

    struct NeuralNetwork *next;
    struct NeuralNetwork *prev;
} NeuralNetwork;

float Sigmoid(float x);
void UpdateNeuralNetwork(NeuralNetwork *N);
void Destroy_NNS(bool EXIT);
void Forward(NeuralNetwork *LocalNN);
void Save_Strongest_NN(void *ID);
NeuralNetwork *GetStrongestNeuralNetwork(void);
wchar_t ScanCell(SHORT x, SHORT y);

void NN(Organism *o, NeuralNetwork *LocalNN); // Placeholder Name
NeuralNetwork *NewNN(size_t Organism_ID);
NeuralNetwork *GetNN(size_t ID);

#endif