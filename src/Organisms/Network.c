#include <NeuralNetwork.h>
#include <Organisms.h>
#include <windows.h>
#include <Life.h>
#include <stdlib.h>
#include <Simulation.h>
#include <math.h>
#include <signal.h>

float Sigmoid(float x) { return (float)(1 / (1 + exp((double)-x))); }

void NN(Organism *o, NeuralNetwork *LocalNN)
{
    for (size_t i = 0; i <= sizeof(LocalNN->Input.Range) / sizeof(LocalNN->Input.Range[0]); i++)
        LocalNN->Input.Range[i] = 0; // Experimental

    COORD CURRENT = o->CURRENT;

    SHORT x = (SHORT)(CURRENT.X - 1);
    SHORT y = (SHORT)(CURRENT.Y - 1);

    for (size_t i = 0; i <= sizeof(LocalNN->Input.Range) / sizeof(LocalNN->Input.Range[0]); i++)
    {
        if (y > (SHORT)(CURRENT.Y + 1))
        {
            y = (SHORT)(CURRENT.X - 1);
            x++;
        }
        if (x > (SHORT)(CURRENT.X + 1))
            break;
        if (x == CURRENT.X && y == CURRENT.Y)
            y++;

        LocalNN->Input.Range[i] = ScanCell(x, y);
        y++;
    }

    UpdateNeuralNetwork(LocalNN);
}

wchar_t ScanCell(SHORT x, SHORT y)
{
    DWORD dum;
    wchar_t ret;

    COORD Next;
    Next.X = x;
    Next.Y = y;

    ReadConsoleOutputCharacterW(GethConsoleOut(), &ret, 1, Next, &dum);
    return ret;
}

void Forward(NeuralNetwork *LocalNN)
{
#define Input_Weight(INPUT_PTR, WEIGHT_PTR) LocalNN->INN[INPUT_PTR].Synapse_Weight[WEIGHT_PTR]
#define Input_Value(INPUT_PTR) LocalNN->Input.Range[INPUT_PTR]
#define Input_Weight_Size(INPUT_PTR) sizeof(LocalNN->INN[INPUT_PTR].Synapse_Weight) / sizeof(LocalNN->INN[INPUT_PTR].Synapse_Weight[0])
#define Hidden_Weight(HIDDEN_PTR, WEIGHT_PTR) LocalNN->HNN[HIDDEN_PTR].Synapse_Weight[WEIGHT_PTR]
#define Hidden_Weight_Size(HIDDEN_PTR) sizeof(LocalNN->HNN[HIDDEN_PTR].Synapse_Weight) / sizeof(LocalNN->HNN[HIDDEN_PTR].Synapse_Weight[0])

    size_t Hidden_Node_Array_Size = sizeof(LocalNN->HNN) / sizeof(LocalNN->HNN[0]);
    size_t Input_Node_Array_Size = sizeof(LocalNN->Input.Range) / sizeof(LocalNN->Input.Range[0]);
    size_t Output_Node_Array_Size = defaultOutputLayerSize - 1;
    size_t Outptr = 0, INptr = 0, HNptr = 0, Rangeptr = 0;

    float HiddenNode[Hidden_Node_Array_Size]; // Hidden Nodes
    float OutputNode[Output_Node_Array_Size]; // Output Nodes
    float last_value = 0;
    float Bias1 = getrandom(0, 100);
    float Bias2 = getrandom(0,100);
    int Selected_Output_Node = 8;

    for (size_t x = 0; x <= Hidden_Node_Array_Size; x++)
        HiddenNode[x] = 0;
    for (size_t x = 0; x <= Output_Node_Array_Size; x++)
        OutputNode[x] = 0;

    for (size_t z = 0, j = 0; z <= Input_Node_Array_Size; z++)
    {
        for (; j <= Hidden_Node_Array_Size; j++)
        {
            if (LocalNN->INN[z].Synapse_Weight[j] <= 0)
                LocalNN->INN[z].Synapse_Weight[j] = getrandom(0, 100);
        }
        j = 0;
    }

    while (HNptr <= Hidden_Node_Array_Size)
    {
        while (INptr <= Input_Node_Array_Size)
        {
            HiddenNode[HNptr] = HiddenNode[HNptr] + (Input_Weight(INptr, HNptr) * Input_Value(Rangeptr));
            INptr++;
            Rangeptr++;
        }
        HiddenNode[HNptr] = Sigmoid(HiddenNode[HNptr] + Bias1);
        HNptr++;
        INptr = 0;
        Rangeptr = 0;
    }
    HNptr = 0;
    
    while (Outptr <= Output_Node_Array_Size)
    {
        while (HNptr <= Hidden_Node_Array_Size)
        {
            OutputNode[Outptr] = OutputNode[Outptr] + (Hidden_Weight(HNptr, Outptr) * HiddenNode[HNptr]);
            HNptr++;
        }
        OutputNode[Outptr] = Sigmoid(OutputNode[Outptr] + Bias2);
        HNptr = 0;
        Outptr++;
    }

    last_value = OutputNode[0];

    for (size_t x = 0; x <= sizeof(OutputNode) / sizeof(OutputNode[0]); x++)
    {
        if (last_value < OutputNode[x])
        {
            last_value = OutputNode[x];
            Selected_Output_Node = (int)x;
        }
    }

    Outptr = INptr = HNptr = Rangeptr = 0;

    UpdateNeuralNetwork(LocalNN);
    Move(Selected_Output_Node, LocalNN->ID);
}
