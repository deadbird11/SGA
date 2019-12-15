#pragma once

#include "Genotype.h"

namespace sga
{

	class MutableGenotype : public Genotype
	{
		friend class Simulation;
	public:
		// Setters, for user use in RandomGenFunc, CrossoverFunc, and MutationFunc
		template<typename T>
		void SetGene(unsigned int id, std::vector<T> value)
		{
			static_assert(false, "SGA does not support this type.");
		}

		template<>
		void SetGene<bool>(unsigned int id, BoolGene value)
		{
			m_BoolGenes[id] = value;
		}

		template<>
		void SetGene<unsigned int>(unsigned int id, UintGene value)
		{
			m_UintGenes[id] = value;
		}

		template<>
		void SetGene<int>(unsigned int id, IntGene value)
		{
			m_IntGenes[id] = value;
		}

		template<>
		void SetGene<float>(unsigned int id, FloatGene value)
		{
			m_FloatGenes[id] = value;
		}

	private:
	
		MutableGenotype(GenotypeBlueprint blueprint);

		MutableGenotype(Genotype other);

		Genotype GetConstGenotype();
	};

}
