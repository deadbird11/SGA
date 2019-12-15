#pragma once

#include <random>

namespace sga
{
	namespace detail
	{

		class Random
		{
		public:
			static float GetRandomInRange(float a, float b);

		private:
			static std::default_random_engine s_Engine;
		};
	}
}