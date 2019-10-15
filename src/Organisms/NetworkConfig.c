#include <NeuralNetwork.h>
#include <Life.h>
#include <Windows.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static NeuralNetwork *NNS;

NeuralNetwork *GetNN(size_t ID)
{
    if (NNS + ID)
        return (NNS + ID);

    return (NeuralNetwork *)0x00;
}

void UpdateNeuralNetwork(NeuralNetwork *N)
{
    if (NNS + N->ID)
        memcpy(NNS + N->ID, N, sizeof(NeuralNetwork));
    else
        Log("UNABLE TO UPDATE NEURAL NETWORK ID %d\n", N->ID);
}

void Destroy_NNS(bool EXIT)
{
    size_t ptr = 1;

    while ((NNS + ptr))
    {
        for (size_t i = 0; i <= sizeof((NNS + ptr)->HNN) / sizeof((NNS + ptr)->HNN[0]); i++)
            free((NNS + ptr)->HNN[i].Synapse_Weight);
        for (size_t i = 0; i <= sizeof(NNS->INN) / sizeof(NNS->INN[0]); i++)
            free((NNS + ptr)->INN[i].Synapse_Weight);

        free((NNS + ptr));
        ptr++;
    }

    if (EXIT)
        free((NNS + 0));
    else
        memset((NNS + 0), 0, sizeof(NeuralNetwork));
}

NeuralNetwork *NewNN(size_t Organism_ID)
{
    NeuralNetwork *x = NULL;
    size_t ptr = Organism_ID;

    x = GetNN(Organism_ID);

    if (x)
        return x;

    if (ptr == 0)
        NNS = (NeuralNetwork *)malloc(sizeof(NeuralNetwork));

    (NNS + ptr)->next = (NeuralNetwork *)malloc(sizeof(NeuralNetwork));
    (NNS + ptr)->ID = Organism_ID;
    (NNS + ptr)->Fitness = 0;

    srand((size_t)time(NULL));

    for (size_t j = 0, z = 0; j <= sizeof((NNS + ptr)->INN) / sizeof((NNS + ptr)->INN[0]); j++)
    {
        (NNS + ptr)->INN[j].Synapse_Weight = calloc(defaultHiddenLayerSize - 1, sizeof(float) + 10);
        while (z <= defaultHiddenLayerSize - 1)
        {
            (NNS + ptr)->INN[j].Synapse_Weight[z] = getrandom(0, 100);
            z++;
        }
        z = 0;
    }
    for (size_t j = 0, z = 0; j <= sizeof((NNS + ptr)->HNN) / sizeof((NNS + ptr)->HNN[0]); j++)
    {
        (NNS + ptr)->HNN[j].Synapse_Weight = calloc(defaultOutputLayerSize - 1, sizeof(float) + 10);
        while (z <= defaultOutputLayerSize - 1)
        {
            (NNS + ptr)->HNN[j].Synapse_Weight[z] = getrandom(0, 100);
            z++;
        }
        z = 0;
    }

    (NNS + ptr)->Made = true;
    return (NNS + ptr);
}
