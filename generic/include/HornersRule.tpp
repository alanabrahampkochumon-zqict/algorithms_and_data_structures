#pragma once
/**
 * @file HornersRule.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Horner's rule implementation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <type_traits>


namespace algorithms
{

    template <typename T>
    T _applyRule(const T* data, std::size_t size, T x)
    {
        static_assert(std::is_arithmetic_v<T>, "The data type must be an integral or float");

        T partialSum = 0;

        for (std::size_t i = 0; i < size; ++i)
        {
            partialSum = data[i] + x * partialSum;
        }

        return partialSum;
    }

    template <typename T, std::size_t Size>
    T hornersRule(const T (&array)[Size], T x)
    {
        return _applyRule(array, Size, x);
    }

    template <typename T>
    T hornersRule(const std::vector<T>& vector, T x)
    {
        return _applyRule(vector.data(), vector.size(), x);
    }
} // namespace algorithms
