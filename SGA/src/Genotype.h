#pragma once

#include "Types.h"

#include <string>

namespace sga
{
	
	class Genotype
	{

	public:
		template<typename T>
		auto GetGene(unsigned int id) const -> std::vector<T>
		{
			static_assert(false, "SGA does not support this type.");
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

		std::string ToString() const;

	protected:

		using BoolGeneList = std::vector<BoolGene>;
		using UintGeneList = std::vector<UintGene>;
		using IntGeneList = std::vector<IntGene>;
		using FloatGeneList = std::vector<FloatGene>;

		Genotype() = default;
		
		BoolGeneList m_BoolGenes;
		UintGeneList m_UintGenes;
		IntGeneList m_IntGenes;
		FloatGeneList m_FloatGenes;
	};

}