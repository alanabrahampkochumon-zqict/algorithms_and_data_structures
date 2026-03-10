#pragma once
/**
 * @file HybridSort.h
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Sorting algorithm that combines Insertion Sort and Merge Sort.
 * @note Only supports C-style array and std::vector.
 *
 * @par Time Complexity
 * Runs in O(N.(lgN)), Θ(N.(lgN)), Ω(N)
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cstddef>
#include <vector>


namespace algorithms
{
    /**
     * Sorts an array using merge hybridSort and insertion hybridSort, taking advantage of both sorting algorithms.
     * @tparam T Type of array to be sorted.
     * @tparam Size Size of the array.
     * @tparam Comparator Comparator used for sorting like std::less
     * @param array The data to be sorted.
     * @param comp Comparator function passed in.
     * @param kValue Threshold for using insertion sort, stopping merge sort at n/k. Default = 16.
     */
    template <typename T, std::size_t Size, typename Comparator>
    void hybridSort(T (&array)[Size], Comparator comp, unsigned int kValue = 16);

    /**
     * Sorts a vector using merge hybridSort and insertion hybridSort, taking advantage of both sorting algorithms.
     * @tparam T Type of array to be sorted.
     * @tparam Size Size of the array.
     * @param array The data to be sorted.
     * @param kValue Threshold for using insertion sort, stopping merge sort at n/k. Default = 16.
     */
    template <typename T, std::size_t Size>
    void hybridSort(T (&array)[Size], unsigned int kValue = 16);


    /**
     * Sorts a vector using merge hybridSort and insertion hybridSort, taking advantage of both sorting algorithms.
     * @tparam T Type of vector to be sorted.
     * @tparam Comparator Comparator used for sorting like std::less
     * @param vector The data to be sorted.
     * @param comp Comparator function passed in.
     * @param kValue Threshold for using insertion sort, stopping merge sort at n/k. Default = 16.
     */
    template <typename T, typename Comparator>
    void hybridSort(std::vector<T>& vector, Comparator comp, unsigned int kValue = 16);


    /**
     * Sorts a vector using merge hybridSort and insertion hybridSort, taking advantage of both sorting algorithms.
     * @tparam T Type of vector to be sorted.
     * @param vector The data to be sorted.
     * @param kValue Threshold for using insertion sort, stopping merge sort at n/k. Default = 16.
     */
    template <typename T>
    void hybridSort(std::vector<T>& vector, unsigned int kValue = 16);
} // namespace algorithms


#include "HybridSort.tpp"