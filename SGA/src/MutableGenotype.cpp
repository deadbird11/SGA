#include "MutableGenotype.h"

#include "Types.h"

namespace sga
{
	// For injection into RandomGenFunc and CrossoverFunc
	// as a blank slate
	MutableGenotype::MutableGenotype(GenotypeBlueprint blueprint)
	{
		m_BoolGenes = BoolGeneList(blueprint.BoolGeneCount);
		m_UintGenes = UintGeneList(blueprint.UintGeneCount);
		m_IntGenes	= IntGeneList(blueprint.IntGeneCount);
		m_FloatGenes = FloatGeneList(blueprint.FloatGeneCount);
	}

	// For injection into MutationFunc
	MutableGenotype::MutableGenotype(Genotype other)
		: Genotype(other)
	{
	}

	Genotype MutableGenotype::GetConstGenotype()
	{
		// Using object slicing on purpose to return a const version of this object
		// for injection into CrosserOverFunc and FitnessFunc
		return (Genotype)(*this);
	}
}