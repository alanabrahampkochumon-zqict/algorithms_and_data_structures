#pragma once
/**
 * @file BinarySearch.h
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Algorithm that searches for an element in a sorted contiguous data structure.
 * @note Only supports C-style array and std::vector.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cstddef>
#include <optional>
#include <vector>


namespace algorithms
{
    template <typename T, std::size_t Size>
    std::optional<std::size_t> binarySearch(const T (&array)[Size], T searchElement);

    template <typename T>
    std::optional<std::size_t> binarySearch(const std::vector<T>& vector, T searchElement);


} // namespace algorithms

#include "BinarySearch.tpp"