#pragma once
/**
 * @file MaxSumSubarray.h
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Algorithm for finding the maximum sum subarray from a given array.
 * @note Supports 4 algorithms. See `AlgorithmType` for details.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <concepts>
#include <cstddef>
#include <ranges>
#include <tuple>


namespace algorithms
{
    template <typename T>
    concept Arithmetic = std::integral<T> || std::floating_point<T>;

    template <typename T>
    using WideType = std::conditional_t<std::is_floating_point_v<T>, double, long long>;

    enum AlgorithmType
    {
        BRUTE_FORCE,        // theta(n^2)
        DIVIDE_AND_CONQUER, // theta(nlgn)
        HYBRID,             // theta(nlgn)
        KADANES             // theta(n)
    };

    /**
     * Finds the maximum sum subarray in the given array or vector.
     * @tparam Range A contiguous container type (e.g., std::vector, std::array, std::span, or C-array) whose elements
     * satisfy the Arithmetic concept.
     * @param elements C-style array, std::array or std::vector elements in which to find the max sum subarray.
     * @param size Size of the container, NOT Byte Size.
     * @param algorithm Algorithm to use. Options are AlgorithmType::BRUTE_FORCE, DIVIDE_AND_CONQUER, and HYBRID.
     * Default is DIVIDE_AND_CONQUER
     * @param limit	Cut off limit for using divide and conquer algorithm. Only applies to HYBRID SORT
     * @return std::tuple(start, end, maxSum)
     */
    template <std::ranges::contiguous_range Range>
        requires Arithmetic<std::ranges::range_value_t<Range>>
    std::tuple<std::size_t, std::size_t, WideType<std::ranges::range_value_t<Range>>> maxSumSubarray(
        const Range& elements, std::size_t size, AlgorithmType algorithm = DIVIDE_AND_CONQUER, std::size_t limit = 40);
} // namespace algorithms

#include "MaxSumSubarray.tpp"
