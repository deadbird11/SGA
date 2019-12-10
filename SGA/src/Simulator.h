#pragma once

#include "sga.h"

#include "Genotype.h"

#include <vector>
#include <functional>
#include <map>

namespace sga
{	
	
	

	class Simlulator
	{

	public:
		
		template<typename T>
		std::vector<T> GetAttrib(unsigned int index)
		{
			return m_CurrentGenotype.GetAttrib<T>();
		}

	private:

		std::vector<Genotype> m_Population;
		Genotype& m_CurrentGenotype;

	};
	
	

}