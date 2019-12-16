#pragma once

#include <random>

namespace sga
{

	template<typename T>
	class Simulation;
	namespace detail
	{
		// I want to expand on this eventually
		class Random
		{
			template<typename T>
			friend class Simulation;
		public:
		private:

			template<typename T>
			friend class Simulation;

			static std::random_device s_Device;
			static std::mt19937 s_Engine;

			template<typename T>
			static T GetRandomInRange(T a, T b)
			{
				static_assert(false, "detail::Random does not support this data type!");
			}

			template<>
			static float GetRandomInRange(float a, float b)
			{
				std::uniform_real_distribution<float> distribution(a, b);
				return distribution(s_Engine);
			}

			template<>
			static int GetRandomInRange(int a, int b)
			{
				std::uniform_int_distribution<int> distribution(a, b);
				return distribution(s_Engine);
			}
		};
	}
}