#pragma once

#include "sga.h"

#include "Genotype.h"

namespace sga
{

	class GenotypeLayout
	{
		friend class Genotype;
	public:
		template<typename T>
		void Push(unsigned int geneLength)
		{
			m_Blueprint.Push<T>(length);
		}

		void Construct(Genotype& other)
		{
			other = m_Blueprint;
		}

	private:
		Genotype m_Blueprint;
	};
}