#pragma once

#include "sga.h"

#include "Genotype.h"
#include "GenotypeLayout.h"
#include "MutableGenotype.h"

#include <vector>
#include <functional>
#include <cassert>
#include <string>

namespace sga
{	
	using FitnessFunc = std::function<float(const Genotype&)>;
	using MutationFunc = std::function<Genotype(Genotype)>;
	using CrossoverFunc = std::function<Genotype(const Genotype&, const Genotype&)>;
	using RandomGenFunc = std::function<void(MutableGenotype&)>;
	
	class Simulator
	{
		friend class GenotypeLayout;
	public:

		Simulator(unsigned int popSize, GenotypeLayout layout,
				  FitnessFunc fitnessFunc, MutationFunc mutationFunc,
			      CrossoverFunc crossoverFunc, RandomGenFunc randomGenFunc)
			: m_Layout(layout),
			  m_FitnessFunc(fitnessFunc), m_MutationFunc(mutationFunc),
			  m_CrossoverFunc(crossoverFunc) , m_RandomGenFunc(randomGenFunc)
		{
			for (unsigned int i = 0; i < popSize; ++i)
			{
				MutableGenotype newGenotype = m_Layout.Construct();
				randomGenFunc(newGenotype);
				m_Population.push_back(newGenotype.GetConstGenotype());
			}
		}

		// for debugging
		Simulator(unsigned int popSize, GenotypeLayout layout, RandomGenFunc randomGenFunc)
			: m_Layout(layout), m_RandomGenFunc(randomGenFunc)
		{
			for (unsigned int i = 0; i < popSize; ++i)
			{
				MutableGenotype newGenotype = m_Layout.Construct();
				randomGenFunc(newGenotype);
				m_Population.push_back(newGenotype.GetConstGenotype());
			}
		}

	private:

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