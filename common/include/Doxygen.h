#pragma once
/**
 * @file Doxygen.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 21, 2026
 *
 * @brief Categorical organization of Algorithms and Data Structures for documentation in Doxygen.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


// clang-format off
/**
 * @defgroup DSA Data Structures and Algorithms.
 * @brief Master collection of all data structures and algorithms.
 * @{
 */

    /**
     * @defgroup DataStructures Data Structures
     * @brief Master suite for all data structures.
     * @ingroup DSA
     * @{
     *   @defgroup Matrix Matrix
     * @}
     */
    
    /**
     * @defgroup Algorithms Algorithms
     * @brief Master suite for all algorithms.
     * @ingroup DSA
     * @{
     */
    
        /**
         * @defgroup SortingAlgo Sorting Algorithms
         * @brief Collection of sorting algorithms.
         * @ingroup TestHarness
         * @{
         *   @defgroup SA_BinaryInsertionSort Binary Insertion Sort
         *   @defgroup SA_BubbleSort Bubble Sort
         *   @defgroup SA_HybridSort Hybrid Sort (Merge + Insertion Sort)
         *   @defgroup SA_InsertionSort Insertion Sort
         *   @defgroup SA_InsertionSort_Recursive Insertion Sort (Recursive)
         *   @defgroup SA_MergeSort Merge Sort
         *   @defgroup SA_MergeSort_Recursive Merge Sort (Recursive)
         *   @defgroup SA_SelectionSort Selection Sort
         * @}
         */

    /** @} */ // End of Algorithms
    
    /**
     * @defgroup Concepts Concepts
     * @brief Constraints (C++ Concepts) used in DSA.
     * @ingroup DSA
     */

/** @} */ // End of DSA
// clang-format on
