#pragma once

#include <cstddef>
#include <vector>

namespace Algorithms::Generic
{
	/**
	 * Evaluates sum of polynomial using Horner's Rule (C-Style Array Overload).
	 * Note: If you don't align elements, the sum will not be correct. That is for equation that 0 coefficient polynomials, you must pass in the 0.
	 * EG: 2x^2 + 4x + 1 => {2, 4, 1}
	 *     4x^4 + 1 => {4, 0, 0, 0, 1}
	 * @tparam T Type of array. NOTE: Only supports numbers like integers or floats.
	 * @tparam Size Size of the array.
	 * @param array array of coefficient. Needs to be aligned with zero.
	 * @param x Value for x.
	 * @return sum of the polynomial
	 */
	template<typename T, std::size_t Size>
	T hornersRule(const T(&array)[Size], T x);

	/**
	 * Evaluates sum of polynomial using Horner's Rule (Vector Overload).
	 * Note: If you don't align elements, the sum will not be correct. That is for equation that 0 coefficient polynomials, you must pass in the 0.
	 * EG: 2x^2 + 4x + 1 => {2, 4, 1}
	 *     4x^4 + 1 => {4, 0, 0, 0, 1}
	 * @tparam T Type of array. NOTE: Only supports numbers like integers or floats.
	 * @param x Value for x.
	 * @return sum of the polynomial
	 */
	template<typename T>
	T hornersRule(const std::vector<T>& vector, T x);
}

#include "HornersRule.tpp"