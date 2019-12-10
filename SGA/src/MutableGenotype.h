#pragma once

#include "sga.h"

#include "Genotype.h"

namespace sga
{

	class MutableGenotype : public Genotype
	{
		friend class GenotypeLayout;
		friend class Simulator;
	public:
		template<typename T>
		void SetGene(unsigned int id, std::vector<bool> value)
		{
			static_assert(false);
		}

		template<>
		void SetGene<bool>(unsigned int id, BoolGene value)
		{
			m_BoolGenes[id] = value;
		}

	private:
	
		MutableGenotype(unsigned int boolGeneCount, unsigned int uintGeneCount,
			unsigned int intGeneCount, unsigned int floatGeneCount)
		{
			m_BoolGenes = BoolGeneList(boolGeneCount);
			m_UintGenes = UintGeneList(uintGeneCount);
			m_IntGenes = IntGeneList(intGeneCount);
			m_FloatGenes = FloatGeneList(floatGeneCount);
		}

		Genotype GetConstGenotype()
		{
			return (Genotype)(*this);
		}
	};

}
