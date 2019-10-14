#include <Organisms.h>
#include <NeuralNetwork.h>
#include <signal.h>
#include <stdio.h>
#include <Debug.h>

void Save_Strongest_NN(void *ID)
{
    UNUSED(ID);
    Organism *o = Get_Organisms();
    NeuralNetwork *NN;
    NeuralNetwork *LastNN;
    NeuralNetwork *StrongestNN;

    if (!o)
        return;
    StrongestNN = GetNN(0);

    for (size_t i = 0; i < o->ID; i++)
    {
        o = GetOrganism(i);
        if (!o)
            return;
        NN = GetNN(o->ID);
        LastNN = NN;

        if (LastNN->Fitness >= StrongestNN->Fitness)
            StrongestNN = LastNN;
    }

    FILE *f = fopen("NeuralNetwork.dat", "w");
    if (!f)
    {
        Log("UNABLE TO SAVE NEURAL NETWORK\n");
        raise(2);
        return;
    }

    if (!fwrite(&StrongestNN, sizeof(NeuralNetwork), 1, f))
        Log("Saved Strongest Neural Network: %p\n", &StrongestNN);
    else
    {
        Log("UNABLE TO SAVE NEURAL NETWORK.\n");
        fclose(f);
        raise(2);
    }
}