#pragma once
#include <array>
#include <cstddef>

namespace Algorithms::Generic
{
	template<typename T, std::size_t Size>
	std::array<T, Size + 1> binaryAdd(std::array<T, Size> first, std::array<T, Size> second);

}

#include "BinaryAdder.tpp"