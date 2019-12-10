#pragma once

#include "sga.h"

#include <vector>

namespace sga
{

	class Genotype
	{

	public:

		template<typename T>
		std::vector<T> GetAttrib(unsigned int index)
		{
			static_assert(false);
		}

		template<>
		BoolGene GetAttrib<bool>(unsigned int index)
		{
			return m_BoolGenes[index];
		}

		template<>
		UintGene GetAttrib<unsigned int>(unsigned int index)
		{
			return m_UintGenes[index];
		}

		template<>
		IntGene GetAttrib<int>(unsigned int index)
		{
			return m_IntGenes[index];
		}

		template<>
		FloatGene GetAttrib<float>(unsigned int index)
		{
			return m_FloatGenes[index];
		}

	private:

		BoolGeneList m_BoolGenes;
		UintGeneList m_UintGenes;
		IntGeneList m_IntGenes;
		FloatGeneList m_FloatGenes;
	};
}