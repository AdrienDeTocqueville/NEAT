#include "Species.h"

#include <cmath>
#include <fstream>

const float Species::crossoverChance(0.75f);

const float Species::deltaDisjoint(2.0f), Species::deltaWeights(0.4f);
const float Species::deltaThreshold(1.0f);


Species::Species():
    topFitness(0), averageFitness(0),
    staleness(0)
{ }

Species::Species(std::string _file):
    topFitness(0), averageFitness(0),
    staleness(0)
{
    std::ifstream file(_file);
    if (!file)
        return;

    unsigned genSize(0);
    file >> genSize >> topFitness >> averageFitness >> staleness;

    string genomeStr;
    getline(file, genomeStr); // Take care of carriage return

    for (unsigned i(0) ; i < genSize ; i++)
    {
        getline(file, genomeStr);

        genomes.emplace_back();
        genomes.back().loadFromString(genomeStr);
    }
}

Species::Species(const Genome& _genome):
    topFitness(0), averageFitness(0),
    staleness(0)
{
    genomes.push_back(_genome);
}

void Species::saveToFile(std::string _file)
{
    std::ofstream file(_file, std::ofstream::out);

    file << genomes.size() << " " << topFitness << " " << averageFitness << " " << staleness;

    for (auto g(genomes.begin()) ; g != genomes.end() ; ++g)
        file << '\n' << g->saveToString();
}

bool Species::contains(const Genome& _genome)
{
	float dd = deltaDisjoint * disjointGenes(genomes.front(), _genome);
	float dw = deltaWeights * averageWeightDifference(genomes.front(), _genome);

	return dd + dw < deltaThreshold;
}

void Species::addGenome(Genome _genome)
{
    genomes.push_back(_genome);
}

Genome Species::breedChild()
{
	if (random() < crossoverChance)
    {
        auto g1 = genomes.begin();  advance(g1, randomInt(0, genomes.size()-1));
        auto g2 = genomes.begin();  advance(g2, randomInt(0, genomes.size()-1));

		Genome child(*g1, *g2); // Perform crossover

		child.mutate();
		return child;
    }
	else
    {
        auto g = genomes.begin();  advance(g, randomInt(0, genomes.size()-1));

		Genome child(*g); // Copy genome

		child.mutate();
		return child;
    }
}

void Species::sort()
{
    auto decreasingFitness = [](const Genome& a, const Genome& b)
    {
        return a.fitness > b.fitness;
    };

    genomes.sort(decreasingFitness);
}

void Species::cull(bool _cutToOne)
{
    sort();

    unsigned remaining = _cutToOne? 1: ceil(genomes.size() * 0.5f);

    while (genomes.size() > remaining)
        genomes.pop_back();
}

void Species::computeAverageFitness()
{
	float sum = 0.0f;

	for (const Genome& genome: genomes)
		sum += genome.globalRank;

	averageFitness = sum / genomes.size();
}
