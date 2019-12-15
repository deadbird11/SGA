#pragma once

#include "Genotype.h"
#include "MutableGenotype.h"

#include <vector>
#include <functional>
#include <random>
#include <optional>

namespace sga
{	

	using FitnessFunc = std::function<float(const Genotype&)>;
	using MutationFunc = std::function<void(MutableGenotype&)>;
	using CrossoverFunc = std::function<void(const Genotype&, const Genotype&, MutableGenotype&)>;
	using RandomGenFunc = std::function<void(MutableGenotype&)>;

	class Simulation
	{

	public:
		Simulation(unsigned int popSize, unsigned int m_MatingPoolCount, float mutationChance,
				   GenotypeBlueprint blueprint, RandomGenFunc randomGenFunc,
				   FitnessFunc fitnessFunc, CrossoverFunc crossoverFunc, MutationFunc mutationFunc);

		//TODO: add acceptance criteria, return a Genotype
		void Run();

		// for debugging
		Simulation(unsigned int popSize, unsigned int m_MatingPoolCount, float mutationChance, GenotypeBlueprint blueprint, RandomGenFunc randomGenFunc);
		Simulation(unsigned int popSize, unsigned int m_MatingPoolCount, float mutationChance, GenotypeBlueprint blueprint, RandomGenFunc randomGenFunc, FitnessFunc fitnessFunc);

		static CrossoverFunc BasicCrossover;

		void SetPolarization(unsigned int scl) { m_Polarization = scl; }

		void SetOptimalFitness(float val) { m_OptimalFitness = std::make_optional(val); }

	private:
		MutableGenotype Construct();

		void GeneratePopulation();

		std::vector<float> CalcPopulationFitness();

		// maybe make this an option for users
		// std::vector<Genotype> GetMatingPoolTopN(std::vector<float>& fitnesses);

		std::vector<Genotype> GetMatingPoolRandom(std::vector<float>& fitnesses);

		std::vector<Genotype> BreedGenotypes(std::vector<Genotype>& genotypes);
		
	private:

		unsigned int m_PopulationSize;
		unsigned int m_MatingPoolCount;
		float m_MutationChance;
		unsigned int m_Polarization = 1;
		std::optional<float> m_OptimalFitness;
		std::vector<Genotype> m_Population;
		Genotype* m_CurrentGenotype = nullptr;
		GenotypeBlueprint m_Blueprint;

		FitnessFunc		m_FitnessFunc;
		MutationFunc	m_MutationFunc;
		CrossoverFunc	m_CrossoverFunc;
		RandomGenFunc	m_RandomGenFunc;

		// To disable Setters
		bool m_Running = false;

	};	
}