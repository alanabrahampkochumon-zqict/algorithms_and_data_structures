#pragma once

namespace Algorithms::Generic
{
	template <typename T, std::size_t Size>
	std::optional<std::pair<T, T>> twoSum(const T(&elements)[Size], T target)
	{
		return std::nullopt;
	}

	template <typename T>
	std::optional<std::pair<T, T>> twoSum(const std::vector<T>& elements, T target)
	{
		return std::nullopt;
	}
}
