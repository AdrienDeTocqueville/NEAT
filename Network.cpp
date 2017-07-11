#include "Network.h"
#include "Pool.h"

#include <map>
#include <cmath>

float sigmoid(float x)
{
    return 2.0f / (1.0f + exp(-4.9f*x))  -1.0f;
}

Neuron::Neuron():
    output(0.0f)
{ }

float Neuron::compute()
{
    float sum = 0.0f;
    for (unsigned i(0) ; i < inputs.size() ; i++)
        sum += weights[i] * inputs[i]->output;

    output = sigmoid(sum);
    return output;
}

Network::Network(Genome* _genome)
{
    map<unsigned, Neuron*> neurons;

    for (const Gene& gene: _genome->genes)
    {
        if (!gene.enabled)
            continue;

        auto it = neurons.find(gene.in);
        if (it == neurons.end())
            neurons[gene.in] = new Neuron();

        it = neurons.find(gene.out);
        if (it == neurons.end())
            neurons[gene.out] = new Neuron();
    }

    for (const Gene& gene: _genome->genes)
    {
        if (!gene.enabled)
            continue;

        Neuron* n = neurons[gene.out];
        n->inputs.push_back(neurons[gene.in]);
        n->weights.push_back(gene.weight);
    }

    inputLayer.resize(Genome::pool->inputSize, nullptr);
    outputLayer.resize(Genome::pool->outputSize, nullptr);

    for (auto it(neurons.begin()) ; it != neurons.end() ; ++it)
    {
        unsigned index = it->first;

        if (index < Genome::pool->inputSize)
            inputLayer[index] = it->second;

        else if (index < Genome::pool->inputSize + Genome::pool->outputSize)
            outputLayer[index - Genome::pool->inputSize] = it->second;

        else
            hiddenLayer.push_back(it->second);
    }
}

Network::~Network()
{
    for (unsigned i(0) ; i < inputLayer.size() ; i++)
        delete inputLayer[i];

    for (unsigned i(0) ; i < hiddenLayer.size() ; i++)
        delete hiddenLayer[i];

    for (unsigned i(0) ; i < outputLayer.size() ; i++)
        delete outputLayer[i];
}


vector<float> Network::evaluate(vector<float> _input)
{
    vector<float> output(outputLayer.size());


    for (unsigned i(0) ; i < inputLayer.size() ; i++)
    {
        if (inputLayer[i] != nullptr)
            inputLayer[i]->output = _input[i];
    }

    for (Neuron* n: hiddenLayer)
        n->compute();

    for (unsigned i(0) ; i < outputLayer.size() ; i++)
    {
        if (outputLayer[i] == nullptr)
            output[i] = -1.0f;
        else
            output[i] = outputLayer[i]->compute();
    }


    return output;
}

void Network::display()
{
    std::cout << "Inputs: " << inputLayer.size() << std::endl;
        for (unsigned i(0) ; i < inputLayer.size() ; i++)
        {
            if (inputLayer[i] == nullptr)
                std::cout << "_" << std::endl;
            else
            std::cout << inputLayer[i]->inputs.size() << std::endl;
        }

    std::cout << "Hidden: " << hiddenLayer.size() << std::endl;
        for (unsigned i(0) ; i < hiddenLayer.size() ; i++)
        {
            std::cout << hiddenLayer[i]->inputs.size() << std::endl;
        }

    std::cout << "Output: " << outputLayer.size() << std::endl;
        for (unsigned i(0) ; i < outputLayer.size() ; i++)
        {
            if (outputLayer[i] == nullptr)
                std::cout << "_" << std::endl;
            else
            std::cout << outputLayer[i]->inputs.size() << std::endl;
        }

}
