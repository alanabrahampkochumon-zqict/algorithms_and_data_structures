#pragma once
/**
 * @file TwoSum.h
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Algorithm that finds if a pair of numbers adding to the target sum exists.
 * @note Only supports C-style arrays and std::vector.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cstddef>
#include <optional>
#include <utility>
#include <vector>


namespace algorithms
{
    /**
     * Finds if a pair of numbers that sum to `target` exist in the `elements` array.
     * @tparam T Integral or Floating Number
     * @param elements Array of number to search for.
     * @param target The sum to look for in the array.
     * @return If two numbers add up to the target, they are returned in ascending order, else `std::nullopt` is
     * returned. Not the first found elements are returned.
     */
    template <typename T, std::size_t Size>
    std::optional<std::pair<T, T>> twoSum(const T (&elements)[Size], T target);

    /**
     * Finds if a pair of numbers that sum to `target` exist in the `elements` vector.
     * @tparam T Integral or Floating Number
     * @param elements Vector of numbers to search for.
     *					Elements are passed in by value since internal merge sort mutates them.
     * @param target The sum to look for in the array.
     * @return If two numbers add up to the target, they are returned in ascending order, else `std::nullopt` is
     *returned. Not the first found elements are returned.
     */
    template <typename T>
    std::optional<std::pair<T, T>> twoSum(std::vector<T> elements, T target);
} // namespace algorithms

#include "TwoSum.tpp"