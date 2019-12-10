#pragma once

#include "sga.h"

#include <vector>

namespace sga
{

	class Genotype
	{
	public:
	private:

		template<typename T>
		void PushGene(unsigned int geneLength)
		{
			static_assert(false);
		}

		template<>
		void PushGene<bool>(unsigned int geneLength)
		{
			m_BoolGenes.push_back(BoolGene(geneLength));
		}

		template<>
		void PushGene<unsigned int>(unsigned int geneLength)
		{
			m_UintGenes.push_back(UintGene(geneLength));
		}

		template<>
		void PushGene<int>(unsigned int geneLength)
		{
			m_IntGenes.push_back(IntGene(geneLength));
		}

		template<>
		void PushGene<float>(unsigned int geneLength)
		{
			m_FloatGenes.push_back(FloatGene(geneLength));
		}

		template<typename T>
		std::vector<T> GetGene(unsigned int id) const
		{
			static_assert(false);
		}

		template<>
		BoolGene GetGene<bool>(unsigned int id) const
		{
			return m_BoolGenes[id];
		}

		template<>
		UintGene GetGene<unsigned int>(unsigned int id) const
		{
			return m_UintGenes[id];
		}

		template<>
		IntGene GetGene<int>(unsigned int id) const
		{
			return m_IntGenes[id];
		}

		template<>
		FloatGene GetGene<float>(unsigned int id) const
		{
			return m_FloatGenes[id];
		}

	private:

		BoolGeneList m_BoolGenes;
		UintGeneList m_UintGenes;
		IntGeneList m_IntGenes;
		FloatGeneList m_FloatGenes;
	};
}