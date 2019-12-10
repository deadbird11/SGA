#pragma once

#include "sga.h"

#include "Genotype.h"
#include "MutableGenotype.h"

namespace sga
{

	class GenotypeLayout
	{
		friend class Simulator;
	public:
		template<typename T>
		void PushGene()
		{
			static_assert(false);
		}

		template<>
		void PushGene<bool>()
		{
			++m_BoolGeneCount;
		}

		template<>
		void PushGene<unsigned int>()
		{
			++m_UintGeneCount;
		}

		template<>
		void PushGene<int>()
		{
			++m_IntGeneCount;
		}

		template<>
		void PushGene<float>()
		{
			++m_FloatGeneCount;
		}

	private:

		MutableGenotype Construct()
		{
			return MutableGenotype(m_BoolGeneCount, m_UintGeneCount, 
								   m_IntGeneCount, m_FloatGeneCount);
		}

		unsigned int m_BoolGeneCount = 0;
		unsigned int m_UintGeneCount = 0;
		unsigned int m_IntGeneCount = 0;
		unsigned int m_FloatGeneCount = 0;
	};
}