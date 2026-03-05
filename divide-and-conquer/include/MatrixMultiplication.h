#pragma once

#include <concepts>
#include <vector>


namespace Algorithms
{
	enum class MultiplicationAlgorithmType
	{
		BRUTE_FORCE, DIVIDE_AND_CONQUER, STRASSENS
	};

	template <typename T>
	concept Arithmetic = std::integral<T> || std::floating_point<T>;

	template <Arithmetic T>
	struct Matrix
	{
		using value_type = T;

		std::size_t m_Rows, m_Columns;
		std::vector<T> m_Data;

		Matrix(std::size_t rows, std::size_t cols);
		Matrix(const std::vector<std::vector<T>>& list);

		/**
		 * Assignment operator overload.
		 * @param row row to be accessed.
		 * @param col column to be accessed.
		 * @return element<T> if it exists.
		 * @throws runtime_exception if the row or columns are out of bounds.
		 */
		T& operator()(std::size_t row, std::size_t col);

		/**
		 * Access operator overload.
		 * @param row row to be accessed.
		 * @param col column to be accessed.
		 * @return element<T> if it exists.
		 * @throws runtime_exception if the row or columns are out of bounds.
		 */
		const T& operator()(std::size_t row, std::size_t col) const;

		
		template<Arithmetic U>
		auto multiply(const Matrix<U>& other, MultiplicationAlgorithmType algo = MultiplicationAlgorithmType::DIVIDE_AND_CONQUER) const;

		template<Arithmetic U>
		static auto multiply(const Matrix& matA, const Matrix<U>& matB, MultiplicationAlgorithmType algo = MultiplicationAlgorithmType::DIVIDE_AND_CONQUER);

	};

}

#include "MatrixMultiplication.tpp"