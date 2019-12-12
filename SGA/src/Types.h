#pragma once

#include <vector>

namespace sga
{
	using BoolGene = std::vector<bool>;
	using UintGene = std::vector<unsigned int>;
	using IntGene = std::vector<int>;
	using FloatGene = std::vector<float>;

	struct GenotypeBlueprint
	{
		unsigned int BoolGeneCount = 0;
		unsigned int UintGeneCount = 0;
		unsigned int IntGeneCount = 0;
		unsigned int FloatGeneCount = 0;
	};

}