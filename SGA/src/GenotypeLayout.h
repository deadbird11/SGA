#pragma once

#include "sga.h"

#include "Genotype.h"

namespace sga
{

	class GenotypeLayout
	{
	public:
		template<typename T>
		void Push(unsigned int geneLength)
		{
			m_Blueprint.PushGene<T>(geneLength);
		}

		void Construct(Genotype& other)
		{
			other = m_Blueprint;
		}

	private:
		Genotype m_Blueprint;
	};
}