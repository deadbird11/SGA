#include "Simulation.h"

#include "MutableGenotype.h"

#include <cassert>

#define ASSERT_NOT_RUNNING assert(!m_Running && "Cannot change FitnessFunc while Simulation is running.")

namespace sga
{
	void Simulation::GeneratePopulation()
	{
		m_Population = std::vector<Genotype>{};
		for (unsigned int i = 0; i < m_PopulationSize; ++i)
		{
			MutableGenotype newGenotype = m_Layout.Construct();
			m_RandomGenFunc(newGenotype);
			// Population consists of const Genotypes
			MutableGenotype test = MutableGenotype(newGenotype.GetConstGenotype());
			m_Population.push_back(newGenotype.GetConstGenotype());
		}
	}

	Simulation::Simulation(unsigned int popSize, GenotypeLayout layout, RandomGenFunc randomGenFunc)
		: m_PopulationSize(popSize), m_Layout(layout), m_RandomGenFunc(randomGenFunc)
	{
		// TODO: must move this to Run 
		GeneratePopulation();
	}

	void Simulation::SetFitnessFunc(FitnessFunc func)
	{
		ASSERT_NOT_RUNNING;
		m_FitnessFunc = func;
	}

	void Simulation::SetMutationFunc(MutationFunc func)
	{
		ASSERT_NOT_RUNNING;
		m_MutationFunc = func;
	}

	void Simulation::SetCrossoverFunc(CrossoverFunc func)
	{
		ASSERT_NOT_RUNNING;
		m_CrossoverFunc = func;
	}

	void Simulation::SetRandomGenFunc(RandomGenFunc func)
	{
		ASSERT_NOT_RUNNING;
		m_RandomGenFunc = func;
	}

	Simulation::Simulation(unsigned int popSize, GenotypeLayout layout,
		FitnessFunc fitnessFunc, MutationFunc mutationFunc,
		CrossoverFunc crossoverFunc, RandomGenFunc randomGenFunc)
		: m_PopulationSize(popSize),      m_Layout(layout),
		  m_FitnessFunc(fitnessFunc),     m_MutationFunc(mutationFunc),
		  m_CrossoverFunc(crossoverFunc), m_RandomGenFunc(randomGenFunc)
	{
		// TODO: move this to Run
		GeneratePopulation();
	}
}