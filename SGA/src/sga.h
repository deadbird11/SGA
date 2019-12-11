#pragma once

#include "Simulation.h"
#include "GenotypeLayout.h"

#include <vector>

#define BIND_SGA_FN(x) std::bind(&x, this, std::placeholders::_1)

using BoolGene = std::vector<bool>;
using UintGene = std::vector<unsigned int>;
using IntGene = std::vector<int>;
using FloatGene = std::vector<float>;

namespace sga
{
	struct GenotypeBlueprint
	{
		unsigned int BoolGeneCount = 0;
		unsigned int UintGeneCount = 0;
		unsigned int IntGeneCount = 0;
		unsigned int FloatGeneCount = 0;
	};

}