#pragma once

#include "Genotype.h"
#include "MutableGenotype.h"

#include <vector>
#include <functional>

namespace sga
{	

	using FitnessFunc = std::function<float(const Genotype&)>;
	using MutationFunc = std::function<void(MutableGenotype&)>;
	using CrossoverFunc = std::function<void(const Genotype&, const Genotype&, MutableGenotype&)>;
	using RandomGenFunc = std::function<void(MutableGenotype&)>;

	class Simulation
	{

	public:
		Simulation(unsigned int popSize, GenotypeBlueprint blueprint,
			FitnessFunc fitnessFunc, MutationFunc mutationFunc,
			CrossoverFunc crossoverFunc, RandomGenFunc randomGenFunc);

		//TODO: add acceptance criteria, return a Genotype
		void Run();

		// for debugging
		Simulation(unsigned int popSize, GenotypeBlueprint blueprint, RandomGenFunc randomGenFunc);
		Simulation(unsigned int popSize, GenotypeBlueprint blueprint, RandomGenFunc randomGenFunc, FitnessFunc fitnessFunc);

	private:
		MutableGenotype Construct();

		void GeneratePopulation();

		std::vector<float> CalcPopulationFitness();

	private:
		unsigned int m_PopulationSize;
		std::vector<Genotype> m_Population;
		Genotype* m_CurrentGenotype = nullptr;
		GenotypeBlueprint m_Blueprint;

		FitnessFunc m_FitnessFunc;
		MutationFunc m_MutationFunc;
		CrossoverFunc m_CrossoverFunc;
		RandomGenFunc m_RandomGenFunc;

		// To disable Setters
		bool m_Running = false;

	};	

}