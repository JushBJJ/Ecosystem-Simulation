#include <Organisms.h>
#include <NeuralNetwork.h>
#include <signal.h>
#include <stdio.h>
#include <Debug.h>

NeuralNetwork *GetStrongestNeuralNetwork(void)
{
    FILE *f = fopen("NeuralNetwork.dat", "r");
    NeuralNetwork *ret;

    if (!f)
    {
        Log("UNABLE TO OPEN NEURALNETWORK FILE\n");
        raise(2);
        return NULL;
    }

    while (fread(&ret, sizeof(NeuralNetwork), 1, f))
        Log("Getting NN ID: %d\n", ret->ID);
    fclose(f);
    return ret;
}