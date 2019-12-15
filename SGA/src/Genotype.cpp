#include "Genotype.h"

#include <sstream>

namespace sga
{
	// outputting a Genotype
	std::string Genotype::ToString() const
	{
		std::stringstream stream;

		stream << "Boolean Genes:" << std::endl;
		for (const BoolGene& boolGene : m_BoolGenes)
		{
			stream << "\t";
			for (const bool& val : boolGene)
			{
				stream << std::to_string((val) ? 1 : 0) << " ";
			}
			stream << std::endl;
		}

		stream << "Uint Genes:" << std::endl;
		for (const UintGene& uintGene : m_UintGenes)
		{
			stream << "\t";
			for (const unsigned int& val : uintGene)
			{
				stream << std::to_string(val) << " ";
			}
			stream << std::endl;
		}

		stream << "Int Genes:" << std::endl;
		for (const IntGene& intGene : m_IntGenes)
		{
			stream << "\t";
			for (const int& val : intGene)
			{
				stream << std::to_string(val) << " ";
			}
			stream << std::endl;
		}

		stream << "Float Genes:" << std::endl;
		for (const FloatGene& floatGene : m_FloatGenes)
		{
			stream << "\t";
			for (const float& val : floatGene)
			{
				stream << std::to_string(val) << " ";
			}
			stream << std::endl;
		}
		
		return stream.str();
	}
}