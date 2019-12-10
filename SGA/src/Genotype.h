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
		friend class GenotypeLayout;
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
		auto GetGene(unsigned int id) const -> std::vector<T>
		{
			static_assert(false);
		}

		template<>
		auto GetGene<bool>(unsigned int id) const -> sga::BoolGene
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

	private:

		BoolGeneList m_BoolGenes;
		UintGeneList m_UintGenes;
		IntGeneList m_IntGenes;
		FloatGeneList m_FloatGenes;
	};
}