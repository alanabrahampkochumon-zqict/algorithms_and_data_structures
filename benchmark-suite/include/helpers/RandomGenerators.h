#pragma once

#include <chrono>
#include <random>
#include <concepts>
#include <vector>

namespace Helpers
{
	template <typename T>
		requires std::integral<T> || std::floating_point<T>
	T generateRandom(T min = T(1), T max = T(1000), std::size_t seed = std::chrono::system_clock::now().time_since_epoch().count())
	{
		thread_local std::mt19937 engine(static_cast<unsigned int>(seed));


		if constexpr (std::is_integral_v<T>)
		{
			std::uniform_int_distribution<T> dist(min, max);
			return dist(engine);
		}
		else
		{
			std::uniform_real_distribution<T> dist(min, max);
			return dist(engine);
		}

	}
	template <typename T>
		requires std::integral<T> || std::floating_point<T>
	std::vector<T> generateRandomVector(std::size_t size, T min = T(-100), T max = T(1000))
	{
		std::vector<T> vec(size);

		for (auto& v: vec)
			v = generateRandom(min, max);

		return vec;
	}
}
