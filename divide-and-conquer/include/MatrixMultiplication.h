#pragma once

#include <concepts>
#include <vector>


namespace Algorithms
{

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

		T& operator()(std::size_t row, std::size_t col);
		const T& operator()(std::size_t row, std::size_t col) const;


	};

}

#include "MatrixMultiplication.tpp"