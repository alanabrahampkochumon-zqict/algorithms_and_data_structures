#pragma once
/**
 * @file LinearSearch.h
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Algorithm that searches for an element in a contiguous data structure.
 * @note Supports only C-style array and std::vector.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cstddef>


namespace algorithms
{
    template <typename T, std::size_t Size>
    std::optional<size_t> linearSearch(const T (&array)[Size], const T& element);

    template <typename T>
    std::optional<size_t> linearSearch(const std::vector<T>& vector, const T& element);
} // namespace algorithms


#include "LinearSearch.tpp"