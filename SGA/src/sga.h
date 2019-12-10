#pragma once

#include "Simulator.h"

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

}