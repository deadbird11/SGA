#pragma once

#include "detail/Random.h"

#include <vector>
#include <functional>
#include <optional>
#include <iostream>
#include <cmath>

namespace sga
{
	template<typename T>
	using FitnessFunc = std::function<float(const T&)>;

	template<typename T>
	using MutationFunc = std::function<void(T&)>;

	template<typename T>
	using CrossoverFunc = std::function<T(const T&, const T&)>;

	template<typename T>
	using RandomGenFunc = std::function<T()>;

	template<typename T>
	class Simulation
	{
	private:

		unsigned int m_PopulationSize;
		unsigned int m_MatingPoolCount;
		float m_MutationChance;
		unsigned int m_Polarization = 1;
		std::optional<float> m_OptimalFitness;
		std::vector<T> m_Population;

		FitnessFunc<T>		m_FitnessFunc;
		MutationFunc<T>		m_MutationFunc;
		CrossoverFunc<T>	m_CrossoverFunc;
		RandomGenFunc<T>	m_RandomGenFunc;

		// To disable Setters
		bool m_Running = false;

	public:
		Simulation(unsigned int popSize, unsigned int matingPoolCount, float mutationChance, RandomGenFunc<T> randomGenFunc,
			FitnessFunc<T> fitnessFunc, CrossoverFunc<T> crossoverFunc, MutationFunc<T> mutationFunc)
			: m_PopulationSize(popSize), m_MatingPoolCount(matingPoolCount), m_FitnessFunc(fitnessFunc), m_MutationChance(mutationChance),
			m_MutationFunc(mutationFunc), m_CrossoverFunc(crossoverFunc), m_RandomGenFunc(randomGenFunc)
		{
			// TODO: move this to Run
			GeneratePopulation();
		}

		//TODO: add acceptance criteria, return a Genotype
		void Run()
		{
			m_Running = true;

			unsigned int generation = 0;
			// TODO: add acceptance criteria
			while (m_Running)
			{
				std::cout << "Generation #" << ++generation << std::endl;
				// calculating fitness
				auto fitnesses = CalcPopulationFitness();

				// TODO: Give different options, or just leave this up to the user,
				//		 this could possibly turn into its own library that would be nice to have
				// TODO!!: This should happen sooner than later, this is getting difficult to use already
				std::vector<T> elite = GetMatingPoolRandom(fitnesses);

				m_Population = BreedGenotypes(elite);

			}
		}

		void SetPolarization(unsigned int scl) { m_Polarization = scl; }

		void SetOptimalFitness(float val) { m_OptimalFitness = std::make_optional(val); }

	private:

		void GeneratePopulation()
		{
			m_Population = std::vector<T>{};
			for (unsigned int i = 0; i < m_PopulationSize; ++i)
			{
				m_Population.push_back(m_RandomGenFunc());
			}
		}

		std::vector<float> CalcPopulationFitness()
		{
			std::vector<float> result{};
			// keeping track to normalize fitnesses
			float min;
			float max = 0;
			float total = 0;
			// using this to output current best Genotype
			unsigned int bestIndex = 0;

			for (unsigned int i = 0; i < m_Population.size(); ++i)
			{
				// User defined FitnessFunc
				float fitness = m_FitnessFunc(m_Population[i]);
				result.push_back(fitness);
				total += fitness;

				if (i == 0 || fitness < min)
					min = fitness;
				else if (fitness > max)
				{
					max = fitness;
					bestIndex = i;
				}
			}

			// output best gene
			std::cout << "Average fitness: (" << total / m_PopulationSize << ")" << std::endl;
			std::cout << "Best Genotype of this generation has fitness (" << max << "):" << std::endl;
			//std::cout << m_Population[bestIndex].ToString() << std::endl;

			if (m_OptimalFitness.has_value() && max >= m_OptimalFitness)
			{
				m_Running = false;
				std::cout << "Has met fitness criteria." << std::endl;
			}

			// normalizing values between 0 and 1

			for (float& val : result)
			{
				val = (val - min) / (max - min);
				val = std::pow(val, m_Polarization);
			}

			return result;
		}

		// maybe make this an option for users
		// std::vector<Genotype> GetMatingPoolTopN(std::vector<float>& fitnesses);

		std::vector<T> GetMatingPoolRandom(std::vector<float>& fitnesses)
		{
			std::vector<T> result;

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

		std::vector<T> BreedGenotypes(std::vector<T>& genotypes)
		{
			// TODO: This should only be if single mating event can happen
			std::vector<T> result{};

			// building the next generation
			while (result.size() < m_PopulationSize)
			{
				// random mating, haven't analyzed this very much yet
				unsigned int upperRange = genotypes.size();
				while (upperRange > 1)
				{
					// random one to be bread
					int randomIndex = detail::Random::GetRandomInRange<int>(0, upperRange - 1);

					// moving random choice to the back with a swap
					const T& g1 = genotypes[randomIndex];
					std::swap(genotypes[randomIndex], genotypes[upperRange - 1]);

					// breeding last two in vector
					T canvas = m_CrossoverFunc(genotypes[upperRange - 1], genotypes[upperRange - 2]);

					// maybe mutating
					float mutationPick = detail::Random::GetRandomInRange<float>(0, 1);
					if (mutationPick < m_MutationChance) m_MutationFunc(canvas);

					// new individual added to next generation
					result.push_back(canvas);

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

	};
}
