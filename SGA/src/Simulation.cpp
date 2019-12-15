#include "Simulation.h"

#include "MutableGenotype.h"

#include "detail/Random.h"

#include <cassert>
#include <iostream>
#include <algorithm>
#include <random>
#include <map>

#define ASSERT_NOT_RUNNING assert(!m_Running && "Cannot change this value while Simulation is running.")
#define MAX_GENERATION 500


namespace sga
{
	CrossoverFunc Simulation::BasicCrossover = [](const Genotype& first, const Genotype& second, MutableGenotype& canvas)
	{
		
	};

	Simulation::Simulation(unsigned int popSize, unsigned int matingPoolCount, float mutationChance, GenotypeBlueprint blueprint, RandomGenFunc randomGenFunc)
		: m_PopulationSize(popSize), m_MatingPoolCount(matingPoolCount), m_MutationChance(mutationChance),
		  m_Blueprint(blueprint), m_RandomGenFunc(randomGenFunc)
	{
		// TODO: move this to Run 
		GeneratePopulation();
	}

	Simulation::Simulation(unsigned int popSize, unsigned int matingPoolCount, float mutationChance, GenotypeBlueprint blueprint, RandomGenFunc randomGenFunc,
						   FitnessFunc fitnessFunc)
		: m_PopulationSize(popSize), m_MatingPoolCount(matingPoolCount), m_MutationChance(mutationChance),
		  m_Blueprint(blueprint),	 m_RandomGenFunc(randomGenFunc),	 m_FitnessFunc(fitnessFunc)
	{
		// TODO: move this to Run 
		GeneratePopulation();
	}

	Simulation::Simulation(unsigned int popSize, unsigned int matingPoolCount, float mutationChance, 
						   GenotypeBlueprint blueprint, RandomGenFunc randomGenFunc,
						   FitnessFunc fitnessFunc, CrossoverFunc crossoverFunc, MutationFunc mutationFunc)
	:	m_PopulationSize(popSize), m_MatingPoolCount(matingPoolCount), m_Blueprint(blueprint), m_FitnessFunc(fitnessFunc),
		m_MutationChance(mutationChance), m_MutationFunc(mutationFunc),m_CrossoverFunc(crossoverFunc), m_RandomGenFunc(randomGenFunc)
	{
		// TODO: move this to Run
		GeneratePopulation();
	}

	// The method that holds the simulation
	void Simulation::Run()
	{
		m_Running = true;

		// TODO: add acceptance criteria
		for (unsigned int generation = 0; generation < MAX_GENERATION; ++generation)
		{
			std::cout << "Generation #" << generation + 1 << std::endl;
			// calculating fitness
			auto fitnesses = CalcPopulationFitness();

			// TODO: Give different options, or just leave this up to the user,
			//		 this could possibly turn into its own library that would be nice to have
			// TODO!!: This should happen sooner than later, this is getting difficult to use already
			std::vector<Genotype> elite = GetMatingPoolRandom(fitnesses);

			m_Population = BreedGenotypes(elite);

		}
	}

	std::vector<float> Simulation::CalcPopulationFitness()
	{
		std::vector<float> result{};
		// keeping track to normalize fitnesses
		float min;
		float max = 0;
		// using this to output current best Genotype
		unsigned int bestIndex = 0;

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
		std::cout << "Best Genotype of this generation with fitness (" << result[bestIndex] << "):" << std::endl;
		std::cout << m_Population[bestIndex].ToString() << std::endl;

		// normalizing values between 0 and 1
		std::for_each(std::begin(result), std::end(result),
			[min, max](float& val)
		{
			val = (val - min) / (max - min);
		});

		return result;
	}

	// choosing from population, with chance of getting chosen proportional to fitness
	std::vector<Genotype> Simulation::GetMatingPoolRandom(std::vector<float>& fitnesses)
	{
		std::vector<Genotype> result;

		// slow version, will come up with faster one eventually
		float totalCount = 0;
		for (const float val : fitnesses)
		{
			totalCount += val;
		}

		float randomPick = detail::Random::GetRandomInRange<float>(0.0f, totalCount);
		
		// possible optimization with binary search, look at StackOverflow
		unsigned int i = 0;
		while (result.size() < m_MatingPoolCount)
		{
			if (randomPick < fitnesses[i]) {
				// this is our biasedly-picked Genotype
				result.push_back(m_Population[i]);

				// remove this genotype from the selection pool
				totalCount -= fitnesses[i];
				randomPick = detail::Random::GetRandomInRange<float>(0.0f, totalCount);

				fitnesses.erase(fitnesses.begin() + i);
				m_Population.erase(m_Population.begin() + i);

				// starting over
				i = 0;
			}
			randomPick -= fitnesses[i];
			++i;
		}

		return result;
	}

	std::vector<Genotype> Simulation::BreedGenotypes(std::vector<Genotype>& genotypes)
	{
		// TODO: This should only be if single mating event can happen
		std::vector<Genotype> result{};

		// building the next generation
		while (result.size() < m_PopulationSize)
		{
			// random mating, haven't analyzed this very much yet
			unsigned int upperRange = genotypes.size();
			while (upperRange > 0)
			{
				// random one to be bread
				int randomIndex = detail::Random::GetRandomInRange<int>(0, upperRange-1);

				// moving random choice to the back with a swap
				const Genotype& g1 = genotypes[randomIndex];
				std::swap(genotypes[randomIndex], genotypes[upperRange - 1]);

				// breeding last two in vector
				MutableGenotype canvas = Construct();
				m_CrossoverFunc(genotypes[upperRange - 1], genotypes[upperRange - 2], canvas);

				// maybe mutating
				float mutationPick = detail::Random::GetRandomInRange<float>(0, 1);
				if (mutationPick < m_MutationChance) m_MutationFunc(canvas);

				// new individual added to next generation
				result.push_back(canvas.GetConstGenotype());

				// not using already bred individuals
				upperRange -= 2;

			}
		}
		// shaving off extras
		while (result.size() > m_PopulationSize)
		{
			result.pop_back();
		}

		return result;
	}

	void Simulation::GeneratePopulation()
	{
		m_Population = std::vector<Genotype>{};
		for (unsigned int i = 0; i < m_PopulationSize; ++i)
		{
			MutableGenotype canvas = Construct();
			m_RandomGenFunc(canvas);
			// Population consists of const Genotypes
			m_Population.push_back(canvas.GetConstGenotype());
		}
	}

	MutableGenotype Simulation::Construct()
	{
		return MutableGenotype(m_Blueprint);
	}

}