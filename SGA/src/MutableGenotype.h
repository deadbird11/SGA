#pragma once

#include "sga.h"

#include "Genotype.h"

namespace sga
{

	class MutableGenotype : public Genotype
	{
		friend class GenotypeLayout;
		friend class Simulation;
	public:
		template<typename T>
		void SetGene(unsigned int id, std::vector<T> value)
		{
			static_assert(false);
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
	
		MutableGenotype(unsigned int boolGeneCount, unsigned int uintGeneCount,
						unsigned int intGeneCount,  unsigned int floatGeneCount)
		{
			m_BoolGenes = BoolGeneList(boolGeneCount);
			m_UintGenes = UintGeneList(uintGeneCount);
			m_IntGenes = IntGeneList(intGeneCount);
			m_FloatGenes = FloatGeneList(floatGeneCount);
		}

		MutableGenotype(Genotype other)
			: Genotype(other)
		{
		}

		Genotype GetConstGenotype()
		{
			return (Genotype)(*this);
		}
	};

}
