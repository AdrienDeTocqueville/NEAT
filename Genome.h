#ifndef GENOME_H
#define GENOME_H

#include <vector>
#include <iostream>

#include "functions.h"

using namespace std;

class Gene
{
    public:
        Gene(unsigned _in, unsigned _out, float _weight);
        Gene(unsigned _in, unsigned _out, unsigned _innovation, float _weight, bool _enabled);
        ~Gene();

    unsigned in, out;
    unsigned innovation;

    float weight;
    bool enabled;
};

class Pool;

class Genome
{
    public:
        Genome();
        ~Genome();

        Genome(const Genome& g); // Copy constructor
        Genome(const Genome& g1, const Genome& g2); // Crossover

        void copyRates(const Genome& g);

        void mutate();
            void weightMutate();
            void linkMutate(bool _forceBias);
            void nodeMutate();
            void enableDisableMutate(bool _state);

        unsigned randomNeuron(bool _includeInputs);
        bool containsLink(unsigned _neuronIn, unsigned _neuronOut);

        string saveToString();
        void loadFromString(string& _genome);


    unsigned maxNeuron, globalRank;
    float fitness;

    vector<Gene> genes;

    // Mutation rates
    float weightMutationChance;
    float linkMutationChance;
    float biasMutationChance;
    float nodeMutationChance;
    float enableMutationChance;
    float disableMutationChance;
    float perturbChance;
    float stepSize;

    static Pool* pool;
};

unsigned disjointGenes(const Genome& a, const Genome& b);
float averageWeightDifference(const Genome& a, const Genome& b);

#endif // GENOME_H
