#pragma once

#include <type_traits>

namespace Algorithms::Generic
{

	template<typename T>
	T _applyRule(const T* data, std::size_t size, T x)
	{
		//static_assert(st)
		return T(0);
	}

	template<typename T, std::size_t Size>
	T hornersRule(const T(&array)[Size], T x)
	{
		return _applyRule(array, Size, x);
	}

	template<typename T>
	T hornersRule(const std::vector<T>& vector, T x)
	{
		return _applyRule(vector.data(), vector.size(), x);
	}
}
