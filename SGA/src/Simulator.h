#pragma once

#include "sga.h"

#include "Genotype.h"
#include "GenotypeLayout.h"

#include <vector>
#include <functional>
#include <map>

namespace sga
{	
	
	class Simlulator
	{
		friend class Genotype;

	public:
		
		template<typename T>
		std::vector<T> GetGene(unsigned int index)
		{
			return m_CurrentGenotype.GetGene<T>();
		}

		template<typename T>
		void PushGene(unsigned int geneLength)
		{
			m_Layout.Push<T>(count);
		}

	private:

		std::vector<Genotype> m_Population;
		Genotype& m_CurrentGenotype;

		GenotypeLayout& m_Layout;

	};
	
	

}