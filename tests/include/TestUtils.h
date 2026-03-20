#pragma once
/**
 * @file TestUtils.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 06, 2026
 *
 * @brief Validation utilities for DSA test suite.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Matrix.h>

namespace testutils
{

    /**
     * @addtogroup TestUtils
     * @{
     */

    /**
     * @brief Asserts that two matrices are element-wise identical.
     *        If any of the elements are not within the epsilon threshold, the test will fail.
     *
     * @tparam T Type of reference matrix.
     * @tparam U Type of comparison matrix.
     *
     * @param expected Reference matrix.
     * @param actual   Matrix to evaluate.
     * @pre Matrices must have identical dimensions.
     *
     * @note Uses Google Test internally. It will fail if any of element comparison fails.
     */

    template <typename T, typename U>
        requires(std::integral<T> || std::floating_point<T>) && (std::integral<U> || std::floating_point<U>)
    constexpr void EXPECT_MAT_EQ(const datastructures::Matrix<T>& expected, const datastructures::Matrix<U>& actual)
    {
        assert(expected.m_Rows == actual.m_Rows && expected.m_Columns == actual.m_Columns &&
               "Only matrices with same dimension(eg: 3x3) can be compared");
        using R = std::common_type_t<T, U>;
        for (std::size_t i = 0; i < expected.m_Rows; ++i)
        {
            for (std::size_t j = 0; j < expected.m_Columns; ++j)
            {
                if constexpr (std::is_same_v<R, double>)
                    EXPECT_DOUBLE_EQ(static_cast<R>(expected(i, j)), static_cast<R>(actual(i, j)));
                else if constexpr (std::is_floating_point_v<R>)
                    EXPECT_FLOAT_EQ(static_cast<R>(expected(i, j)), static_cast<R>(actual(i, j)));
                else
                    EXPECT_EQ(static_cast<R>(expected(i, j)), static_cast<R>(actual(i, j)));
            }
        }
    }

    /**
     * @brief Asserts that two matrices are NOT element-wise identical.
     *        This check passes as soon as the first mismatching element is found.
     *        If all elements are equal, the test will fail.
     *
     * @tparam T Type of reference matrix.
     * @tparam U Type of comparison matrix.
     *
     * @param expected Reference matrix.
     * @param actual   Matrix to evaluate.
     * @pre Matrices must have identical dimensions.
     *
     * @note Uses Google Test internally. It will fail if all the element-wise comparison succeeds.
     */
    template <typename T, typename U>
        requires(std::integral<T> || std::floating_point<T>) && (std::integral<U> || std::floating_point<U>)
    constexpr void EXPECT_MAT_NE(const datastructures::Matrix<T>& expected, const datastructures::Matrix<U>& actual)
    {
        assert(expected.m_Rows == actual.m_Rows && expected.m_Columns == actual.m_Columns &&
               "Only matrices with same dimension(eg: 3x3) can be compared");
        using R = std::common_type_t<T, U>;
        for (std::size_t i = 0; i < expected.m_Rows; ++i)
            for (std::size_t j = 0; j < expected.m_Columns; ++j)
                if (static_cast<R>(expected(i, j)) != static_cast<R>(actual(i, j)))
                    return SUCCEED();
    }

    /** @} */


} // namespace testutils