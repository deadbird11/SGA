#pragma once

#include "sga.h"

#include "MutableGenotype.h"

namespace sga
{

	class GenotypeLayout
	{
		friend class Simulation;
	public:

		GenotypeLayout(GenotypeBlueprint blueprint)
			: m_Blueprint(blueprint)
		{}

		template<typename T>
		void PushGene()
		{
			static_assert(false);
		}

		template<>
		void PushGene<bool>()
		{
			++m_Blueprint.BoolGeneCount;
		}

		template<>
		void PushGene<unsigned int>()
		{
			++m_Blueprint.UintGeneCount;
		}

		template<>
		void PushGene<int>()
		{
			++m_Blueprint.IntGeneCount;
		}

		template<>
		void PushGene<float>()
		{
			++m_Blueprint.FloatGeneCount;
		}

	private:

		MutableGenotype Construct()
		{
			return MutableGenotype(m_Blueprint);
		}

		GenotypeBlueprint m_Blueprint;
	};
}