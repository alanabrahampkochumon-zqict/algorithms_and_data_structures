#pragma once
/**
 * @file DoxygenGroups.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 19, 2026
 *
 * @brief Categorical organization of test suite for documentation in Doxygen.
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
     *   @defgroup T_Mat_Init Matrix Initialization
     *   @defgroup T_Mat_Access Matrix Access
     *   @defgroup T_Mat_Mutation Matrix Mutation
     *   @defgroup T_Mat_Add Matrix Addition
     *   @defgroup T_Mat_Sub Matrix Subtraction
     *   @defgroup T_Mat_Mul Matrix Multiplication
     *   @defgroup T_Mat_View Matrix View
     * @}
     */

    /**
     * @defgroup MatrixViewTests Matrix View Test Suite
     * @brief Test suite for all MatrixView-related validation.
     * @ingroup TestHarness
     * @{
     *   @defgroup T_Mat_Init Matrix Initialization
     *   @defgroup T_Mat_Access Matrix Access
     *   @defgroup T_Mat_Mutation Matrix Mutation
     * @}
     */

    /**
     * @defgroup RO_MatrixViewTests Read Only Matrix View Test Suite
     * @brief Test suite for all Readonly MatrixView-related validation.
     * @ingroup TestHarness
     * @{
     *   @defgroup T_RO_Mat_Init Matrix Initialization
     *   @defgroup T_RO_Mat_Access Matrix Access
     *   @defgroup T_RO_Mat_Subview Matrix Subview
     * @}
     */
    
    /**
     * @defgroup TestUtils Validation Utilities
     * @brief Validation utilities to the complete DSA test suite.
     */
    


/** @} */ // End of TestHarness
// clang-format on
