#pragma once

#include "Genotype.h"
#include "MutableGenotype.h"

#include <vector>
#include <functional>

namespace sga
{	

	using FitnessFunc = std::function<float(const Genotype&)>;
	using MutationFunc = std::function<void(MutableGenotype&)>;
	using CrossoverFunc = std::function<Genotype(const Genotype&, const Genotype&, MutableGenotype&)>;
	using RandomGenFunc = std::function<void(MutableGenotype&)>;

	class Simulation
	{
	public:
		Simulation(unsigned int popSize, GenotypeBlueprint blueprint,
			FitnessFunc fitnessFunc, MutationFunc mutationFunc,
			CrossoverFunc crossoverFunc, RandomGenFunc randomGenFunc);

		// for debugging
		Simulation(unsigned int popSize, GenotypeBlueprint blueprint, RandomGenFunc randomGenFunc);

		// Setters
		void SetFitnessFunc(FitnessFunc func);
		void SetMutationFunc(MutationFunc func);
		void SetCrossoverFunc(CrossoverFunc func);
		void SetRandomGenFunc(RandomGenFunc func);
		void SetLayout(GenotypeBlueprint blueprint);
		void SetPopulationSize(unsigned int n);

	private:

		MutableGenotype Construct();

		void GeneratePopulation();

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