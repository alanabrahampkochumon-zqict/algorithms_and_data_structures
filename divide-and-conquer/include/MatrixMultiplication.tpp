#pragma once

#include <algorithm>

#include "MatrixMultiplication.h"

namespace Algorithms
{
	template <Arithmetic T>
	Matrix<T>::Matrix(std::size_t rows, std::size_t cols) : m_Rows(rows), m_Columns(cols)
	{
		m_Data.reserve(rows * cols);
		for (std::size_t i = 0; i < m_Rows; ++i)
			for (std::size_t j = 0; j < m_Columns; ++j)
				m_Data[i * m_Columns + j] = static_cast<T>(i == j);
	}

	template <Arithmetic T>
	Matrix<T>::Matrix(const std::vector<std::vector<T>>& list)
	{
		const std::size_t rowCount = list.size();
		std::size_t colCount = 0;
		for (std::size_t i = 0; i < rowCount; ++i)
			colCount = std::max(colCount, list[i].size());

		m_Rows = rowCount;
		m_Columns = colCount;

		m_Data = std::vector(m_Rows * m_Columns, T(0));
		for (std::size_t i = 0; i < list.size(); ++i)
			std::copy(list[i].begin(), list[i].end(), m_Data.begin() + (i * colCount));
	}

	template <Arithmetic T>
	T& Matrix<T>::operator()(std::size_t row, std::size_t col)
	{
		if (row < 0 || row >= m_Rows || col < 0 || col >= m_Columns)
			throw std::runtime_error("Invalid index");
		return m_Data[row * m_Columns + col];
	}

	template <Arithmetic T>
	const T& Matrix<T>::operator()(std::size_t row, std::size_t col) const
	{
		if (row < 0 || row >= m_Rows || col < 0 || col >= m_Columns)
			throw std::runtime_error("Invalid index");
		return m_Data[row * m_Columns + col];
	}

	template <Arithmetic T>
	template <Arithmetic U>
	auto Matrix<T>::multiply(const Matrix<U>& other, MultiplicationAlgorithmType algo) const
	{
		return Matrix(m_Rows, other.m_Columns);
	}

	template <Arithmetic T>
	template <Arithmetic U>
	auto Matrix<T>::multiply(const Matrix& matA, const Matrix<U>& matB, MultiplicationAlgorithmType algo)
	{
		return Matrix<T>(matA.m_Rows, matB.m_Columns);
	}
}
