#pragma once
/**
 * @file TestUtils.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 06, 2026
 *
 * @brief Utilities for testing.
 * 
 * @par Utilities
 * Matrix utilities for comparing equality and inequality.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Matrix.h>

namespace testutils
{
	/**
	 * Compares if two matrices are equals.
	 * @tparam T Type of first matrix.
	 * @tparam U Type of second matrix.
	 * @param expected matrix that is compared against.
	 * @param actual matrix being compared.
	 */
	template <typename T, typename U>
		requires (std::integral<T> || std::floating_point<T>) && (std::integral<U> || std::floating_point<U>)
	constexpr void EXPECT_MAT_EQ(const datastructures::Matrix<T>& expected, const datastructures::Matrix<U>& actual)
	{
		assert(expected.m_Rows == actual.m_Rows && expected.m_Columns == actual.m_Columns && "Only matrices with same dimension(eg: 3x3) can be compared");
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
	 * Compares if two matrices are not equal. "Passes" if at least one element mismatch.
	 * @tparam T Type of first matrix.
	 * @tparam U Type of second matrix.
	 * @param expected matrix that is compared against.
	 * @param actual matrix being compared.
	 */
	template<typename T, typename U>
		requires (std::integral<T> || std::floating_point<T>) && (std::integral<U> || std::floating_point<U>)
    constexpr void EXPECT_MAT_NE(const datastructures::Matrix<T>& expected, const datastructures::Matrix<U>& actual)
	{
		assert(expected.m_Rows == actual.m_Rows && expected.m_Columns == actual.m_Columns && "Only matrices with same dimension(eg: 3x3) can be compared");
		using R = std::common_type_t<T, U>;
		for (std::size_t i = 0; i < expected.m_Rows; ++i)
			for (std::size_t j = 0; j < expected.m_Columns; ++j)
				if (static_cast<R>(expected(i, j)) != static_cast<R>(actual(i, j)))
					return SUCCEED();
	}
}