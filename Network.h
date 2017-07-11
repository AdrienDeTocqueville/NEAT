#ifndef NETWORK_H
#define NETWORK_H

#include "Genome.h"

struct Neuron
{
    Neuron();

    vector<Neuron*> inputs;
    vector<float> weights;

    float output;

    float compute();
};

struct Network
{
    Network(Genome* _genome);
    ~Network();

    vector<float> evaluate(vector<float> _input);

    void display();

    vector<Neuron*> inputLayer;
    vector<Neuron*> hiddenLayer;
    vector<Neuron*> outputLayer;
};

#endif // NETWORK_H
