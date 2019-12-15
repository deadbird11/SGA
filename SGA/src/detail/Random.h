#pragma once

#include <random>

namespace sga
{
	namespace detail
	{
		// I want to expand on this eventually
		class Random
		{
		public:
		private:
			static std::default_random_engine s_Engine;
			static float GetRandomInRange(float a, float b);
		};
	}
}