#pragma once

#include "sga.h"

#include "Genotype.h"
#include "GenotypeLayout.h"
#include "MutableGenotype.h"

#include <vector>
#include <functional>

namespace sga
{	
	using FitnessFunc = std::function<float(const Genotype&)>;
	using MutationFunc = std::function<Genotype(Genotype)>;
	using CrossoverFunc = std::function<Genotype(const Genotype&, const Genotype&)>;
	using RandomGenFunc = std::function<void(MutableGenotype&)>;
	
	class Simulation
	{
		friend class GenotypeLayout;
	public:

		Simulation(unsigned int popSize, GenotypeLayout layout,
			FitnessFunc fitnessFunc, MutationFunc mutationFunc,
			CrossoverFunc crossoverFunc, RandomGenFunc randomGenFunc);

		// for debugging
		Simulation(unsigned int popSize, GenotypeLayout layout, RandomGenFunc randomGenFunc);

		// Setters
		void SetFitnessFunc(FitnessFunc func);
		void SetMutationFunc(MutationFunc func);
		void SetCrossoverFunc(CrossoverFunc func);
		void SetRandomGenFunc(RandomGenFunc func);
		void SetLayout(GenotypeLayout layout);
		void SetPopulationSize(unsigned int n);

	private:

		void GeneratePopulation();

	private:
		unsigned int m_PopulationSize;
		std::vector<Genotype> m_Population;
		Genotype* m_CurrentGenotype = nullptr;
		GenotypeLayout m_Layout;

		FitnessFunc m_FitnessFunc;
		MutationFunc m_MutationFunc;
		CrossoverFunc m_CrossoverFunc;
		RandomGenFunc m_RandomGenFunc;

		bool m_Running = false;
	};
	
	

}