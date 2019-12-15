#include "Random.h"

namespace sga
{
	namespace detail
	{

		
		float Random::GetRandomInRange(float a, float b)
		{
			std::uniform_real_distribution<float> distribution(a, b);
			return distribution(s_Engine);
		}

	}
}