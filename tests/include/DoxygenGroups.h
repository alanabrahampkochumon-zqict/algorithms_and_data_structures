#pragma once
/**
 * @file DoxygenGroups.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 19, 2026
 *
 * @brief Define doxygen groups for the entire test harness.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


// clang-format off
/**
 * @defgroup TestHarness Test Suite
 * @brief Master suite for Algorithms and DataStructure.
 * @{
 */

    /**
     * @defgroup MatrixTests Matrix Test Suite
     * @brief Test suite for all matrix-related validation.
     * @ingroup TestHarness
     * @{
     *   @defgroup Mat_Init Matrix Initialization
     *   @defgroup Mat_Access Matrix Access
     *   @defgroup Mat_Mutation Matrix Mutation
     *   @defgroup Mat_Add Matrix Addition
     *   @defgroup Mat_Sub Matrix Subtraction
     *   @defgroup Mat_Mul Matrix Multiplication
     * @}
     */

    /**
     * @defgroup MatrixViewTests Matrix View Test Suite
     * @brief Test suite for all matrix view-related validation.
     * @ingroup TestHarness
     * @{
     *   @defgroup Mat_Init Matrix Initialization
     *   @defgroup Mat_Access Matrix Access
     *   @defgroup Mat_Mutation Matrix Mutation
     * @}
     */


/** @} */ // End of TestHarness
// clang-format on
