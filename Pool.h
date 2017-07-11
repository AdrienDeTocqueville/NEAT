#ifndef POOL_H
#define POOL_H

#include "Species.h"
#include "Network.h"

#include <functional>

class Pool
{
    public:
        Pool(unsigned _population, unsigned _inputSize, unsigned _outputSize);
        Pool(unsigned _generation);
        ~Pool();

        void saveToFolder();


        unsigned getCurrentOrganism();
        unsigned getInnovation();

        bool computeGenerationFitness(std::function< float(Network&, bool&) > _fitnessFunction);

        void addToSpecies(const Genome& _genome);
        void buildNewGeneration(bool _saveToFolder);

        void assignGlobalRank();

        void removeStaleSpecies();
        void removeWeakSpecies();

        float totalAverageFitness();

        Genome* nextGenome();


    static const unsigned maxStaleness;

    vector<Species> species;

    unsigned population;

    unsigned generation;
    unsigned innovation;

    int currentGenome;
    unsigned currentSpecies;
    unsigned currentOrganism;

    float maxFitness;

    unsigned inputSize;
    unsigned outputSize;
};

#endif // POOL_H
