#pragma once

#include "Genome.h"

#include <list>


class Species
{
    public:
        Species();
        Species(std::string _file);
        Species(const Genome& _genome);

        void saveToFile(std::string _file);

        bool contains(const Genome& _genome);
        void addGenome(Genome _genome);

        Genome breedChild();

        void sort();
        void cull(bool _cutToOne);

        void computeAverageFitness();

    float topFitness, averageFitness;
    unsigned staleness;

    list<Genome> genomes;

    static const float crossoverChance;

    static const float deltaDisjoint, deltaWeights;
    static const float deltaThreshold;
};
