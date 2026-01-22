#pragma once
#include <array>
#include <cstddef>

namespace Algorithms::Generic
{
	template<std::size_t Size>
	std::optional<std::array<int, Size + 1>> binaryAdd(std::array<int, Size> first, std::array<int, Size> second);

}

#include "BinaryAdder.tpp"