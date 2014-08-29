
#pragma once 

#include <random>
namespace core
{
	template <typename T>
	class RandomGenerator
	{
	public:
		RandomGenerator(T min, T max)
		{
			static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "base type must be integral or floating point");

			random_engine = std::default_random_engine(rd());
			uniform_dist = std::uniform_int_distribution<T>(min, max);
		}

		T GetRand()
		{
			return uniform_dist(random_engine);
		}

	private:
		std::random_device rd;
		std::default_random_engine random_engine;
		std::uniform_int_distribution<T> uniform_dist;
	};
}