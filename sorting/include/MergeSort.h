#pragma once
/**
 * @file MergeSort.h
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Sorting algorithm that sorts a data structure by dividing it into subproblems, and then, sorting and combining
 * them.
 * @note Only supports C-style array and std::vector.
 *
 * @par Time Complexity
 * Runs in O(N.(logN)), Θ(N.(logN)), Ω(N.(logN))
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cstddef>
#include <vector>


namespace algorithms
{
    /**
     * Sorts an array of elements in-place using Merge Sort.
     * @tparam T Type of elements to be sorted.
     * @tparam Size Size of the array.
     * @tparam Comparator Comparator to use for comparison of elements.
     * @param array Array to be sorted(psuedo in-place).
     * @param comp Comparator function that compares element when sorting.
     */
    template <typename T, std::size_t Size, typename Comparator>
    void mergeSort(T (&array)[Size], Comparator comp);


    /**
     * Sorts an array of elements in-place using Merge Sort.
     * @tparam T Type of elements to be sorted.
     * @tparam Size Size of the array.
     * @param array Array to be sorted(psuedo in-place).
     */
    template <typename T, std::size_t Size>
    void mergeSort(T (&array)[Size]);


    /**
     * Sorts a vector of elements in-place using Merge Sort.
     * @tparam T Type of elements to be sorted.
     * @tparam Comparator Comparator to use for comparison of elements.
     * @param vector Vector to be sorted(psuedo in-place).
     * @param comp Comparator function that compares element when sorting.
     */
    template <typename T, typename Comparator>
    void mergeSort(std::vector<T>& vector, Comparator comp);


    /**
     * Sorts a vector of elements in-place using Merge Sort.
     * @tparam T Type of elements to be sorted.
     * @param vector Vector to be sorted(psuedo in-place).
     */
    template <typename T>
    void mergeSort(std::vector<T>& vector);
} // namespace algorithms


#include "MergeSort.tpp"