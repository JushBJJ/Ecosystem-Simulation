#include <NeuralNetwork.h>
#include <Life.h>
#include <Windows.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

static NeuralNetwork *NNS;
static size_t idptr;
static bool initNN;

NeuralNetwork *GetNN(size_t ID)
{
    NeuralNetwork *x;
    while (NNS->prev)
    {
        x = NNS->prev;
        NNS = x;
    }
    while (NNS->next)
    {
        if (NNS->ID == ID)
            return ID;
        x = NNS->next;
        NNS = x;
    }

    if (NNS->ID != ID)
        return 0;
}

void UpdateNeuralNetwork(NeuralNetwork *N)
{
    NeuralNetwork *x;

    while (NNS->prev)
    {
        x = NNS->prev;
        NNS = x;
    }
    while (NNS->next)
    {
        x = NNS->next;
        if (NNS->ID == N->ID)
        {
            NNS = N;
            return;
        }
        NNS = x;
    }

    debug(("ERROR: COULDN'T UPDATE NEURALNETWORK %d", N->ID));
}

void Destroy_NNS(bool EXIT)
{
    debug(("Destroying Neural Networks..."));
    NeuralNetwork *x;

    while (NNS->prev)
    {
        x = NNS->prev;
        NNS = x;
    }
    while (NNS->next)
    {
        debug(("Destroyed Neural Network %d", NNS->ID));
        x = NNS->next;
        free(NNS);
        NNS = x;
    }

    if (EXIT)
        free(NNS);
    else
        NNS = NULL;

    debug(("Destroyed Neural Networks."));
}

NeuralNetwork *NewNN(void)
{
    NeuralNetwork *x;

    if (!initNN)
    {
        NNS = NULL;
        x = NULL;

        NNS = malloc(sizeof *NNS);
        NNS->next = NULL;
        initNN = true;
        debug(("Initialized Neural Network"));
    }

    while (NNS->next)
    {
        x = NNS->next;
        x->prev = NNS;
        NNS = x;
    }

    idptr++;
    NNS->ID = idptr;
    NNS->TotalPoints = 0;
    NNS->next = malloc(sizeof *NNS);
    for (int i = 0; i <= 8; i++)
        NNS->Range[i] = 0;

    return NNS;
}