#include "Simulation.h"

#include "MutableGenotype.h"

#include <cassert>
#include <iostream>
#include <algorithm>
#include <random>

#define ASSERT_NOT_RUNNING assert(!m_Running && "Cannot change this value while Simulation is running.")
#define MAX_GENERATION 5


namespace sga
{

	Simulation::Simulation(unsigned int popSize, unsigned int matingPoolCount, GenotypeBlueprint blueprint, RandomGenFunc randomGenFunc)
		: m_MatingPoolCount(matingPoolCount), m_Blueprint(blueprint), m_RandomGenFunc(randomGenFunc)
	{
		// TODO: move this to Run 
		GeneratePopulation(popSize);
	}

	Simulation::Simulation(unsigned int popSize, GenotypeBlueprint blueprint, RandomGenFunc randomGenFunc,
						   FitnessFunc fitnessFunc)
		: m_Blueprint(blueprint), m_RandomGenFunc(randomGenFunc), m_FitnessFunc(fitnessFunc)
	{
		// TODO: move this to Run 
		GeneratePopulation(popSize);
	}

	Simulation::Simulation(unsigned int popSize, GenotypeBlueprint blueprint,
						   FitnessFunc fitnessFunc, MutationFunc mutationFunc,
						   CrossoverFunc crossoverFunc, RandomGenFunc randomGenFunc)
	: m_Blueprint(blueprint),	      m_FitnessFunc(fitnessFunc),	 m_MutationFunc(mutationFunc),
	  m_CrossoverFunc(crossoverFunc), m_RandomGenFunc(randomGenFunc)
	{
		// TODO: move this to Run
		GeneratePopulation(popSize);
	}

	// The method that holds the simulation
	void Simulation::Run()
	{
		m_Running = true;

		// TODO: add acceptance criteria
		for (unsigned int generation = 0; generation < MAX_GENERATION; ++generation)
		{
			// calculating fitness
			auto fitnesses = CalcPopulationFitness();

			// TODO: Give different options, or just leave this up to the user,
			//		 this could possibly turn into its own library that would be nice to have
			std::vector<Genotype> elite = GetMatingPool();

		}
	}

	std::vector<float> Simulation::CalcPopulationFitness()
	{
		std::vector<float> result{};
		// keeping track to normalize fitnesses
		float min;
		float max = 0;
		// using this to output current best Genotype
		unsigned int bestIndex;

		for (unsigned int i = 0; i < m_Population.size(); ++i)
		{
			// User defined FitnessFunc
			float fitness = m_FitnessFunc(m_Population[i]);
			result.push_back(fitness);

			if (i == 0 || fitness < min)
				min = fitness;
			else if (fitness > max)
			{
				max = fitness;
				bestIndex = i;
			}
		}

		// output best gene
		std::cout << "Best Genotype of this generation:" << std::endl;
		std::cout << m_Population[bestIndex].ToString() << std::endl;

		// normalizing values between 0 and 1
		std::for_each(std::begin(result), std::end(result),
			[min, max](float& val)
		{
			val = (val - min) / (max - min);
		});

		return result;
	}


	void Simulation::GeneratePopulation(unsigned int n)
	{
		m_Population = std::vector<Genotype>{};
		for (unsigned int i = 0; i < n; ++i)
		{
			MutableGenotype blank = Construct();
			m_RandomGenFunc(blank);
			// Population consists of const Genotypes
			m_Population.push_back(blank.GetConstGenotype());
		}
	}

	MutableGenotype Simulation::Construct()
	{
		return MutableGenotype(m_Blueprint);
	}

}