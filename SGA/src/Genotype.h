#pragma once

#include "sga.h"

#include <vector>

namespace sga
{
	using BoolGene = std::vector<bool>;
	using UintGene = std::vector<unsigned int>;
	using IntGene = std::vector<int>;
	using FloatGene = std::vector<float>;

	using BoolGeneList = std::vector<BoolGene>;
	using UintGeneList = std::vector<UintGene>;
	using IntGeneList = std::vector<IntGene>;
	using FloatGeneList = std::vector<FloatGene>;
	
	class Genotype
	{
		friend class Simulator;
	public:
		template<typename T>
		auto GetGene(unsigned int id) const -> std::vector<T>
		{
			static_assert(false);
		}

		template<>
		auto GetGene<bool>(unsigned int id) const -> BoolGene
		{
			return m_BoolGenes[id];
		}

		template<>
		auto GetGene<unsigned int>(unsigned int id) const -> UintGene
		{
			return m_UintGenes[id];
		}

		template<>
		auto GetGene<int>(unsigned int id) const -> IntGene
		{
			return m_IntGenes[id];
		}

		template<>
		auto GetGene<float>(unsigned int id) const -> FloatGene
		{
			return m_FloatGenes[id];
		}

	protected:

		Genotype() = default;
		
		BoolGeneList m_BoolGenes;
		UintGeneList m_UintGenes;
		IntGeneList m_IntGenes;
		FloatGeneList m_FloatGenes;
	};


}