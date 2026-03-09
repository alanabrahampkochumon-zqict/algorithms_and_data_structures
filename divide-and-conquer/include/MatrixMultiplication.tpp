#pragma once

#include <algorithm>
#include <cstddef>

#include "MatrixMultiplication.h"
#include "../../vendors/googlebenchmark/src/arraysize.h"


namespace Algorithms
{
	template <Arithmetic T>
	Matrix<T>::Matrix(std::size_t rows, std::size_t cols) : m_Rows(rows), m_Columns(cols)
	{
		m_Data.reserve(rows * cols);
		for (std::size_t i = 0; i < m_Rows; ++i)
			for (std::size_t j = 0; j < m_Columns; ++j)
				m_Data[i * m_Columns + j] = T(0);
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
    auto Matrix<T>::operator+(const Matrix<U>& other) const -> Matrix<std::common_type_t<T, U>>
	{
        if (m_Rows != other.m_Rows && m_Columns != other.m_Columns)
            throw std::runtime_error("Matrices of different dimensions cannot be added together");

		Matrix result(m_Rows, m_Columns);

		for (std::size_t row = 0; row < m_Rows; ++row)
            for (std::size_t col = 0; col < m_Columns; ++col)
                result(row, col) = (*this)(row, col) + other(row, col);

		return result;
	}


    template <Arithmetic T>
    template <Arithmetic U>
    Matrix<T>& Matrix<T>::operator+=(const Matrix<U>& other)
	{
        if (m_Rows != other.m_Rows && m_Columns != other.m_Columns)
            throw std::runtime_error("Matrices of different dimensions cannot be added together");

        for (std::size_t row = 0; row < m_Rows; ++row)
            for (std::size_t col = 0; col < m_Columns; ++col)
                (*this)(row, col) += other(row, col);
        return *this;
	}


    template <Arithmetic T, Arithmetic U>
	static auto bruteForce(const Matrix<T>& matA, const Matrix<U>& matB)
	{
		using R = std::common_type_t<T, U>;
		Algorithms::Matrix<R> result(matA.m_Rows, matB.m_Columns);
		for (std::size_t i = 0; i < matA.m_Rows; ++i)
			for (std::size_t j = 0; j < matB.m_Columns; ++j)
			{
				for (std::size_t k = 0; k < matB.m_Rows; ++k)
					result(i, j) += matA(i, k) * matB(k, j);
			}

		return result;
	}

	template <Arithmetic T>
	template <Arithmetic U>
	auto Matrix<T>::multiply(const Matrix<U>& other, MultiplicationAlgorithmType algo) const -> Matrix<std::common_type_t<T, U>>
	{
		if (this->m_Columns != other.m_Rows)
			throw std::runtime_error("Invalid matrix size");

		switch (algo)
		{
		case MultiplicationAlgorithmType::BRUTE_FORCE:
			return bruteForce(*this, other);
		case MultiplicationAlgorithmType::DIVIDE_AND_CONQUER:
			break;
		case MultiplicationAlgorithmType::STRASSENS:
			break;
		default:
			break;
		}
		return Matrix(m_Rows, other.m_Columns); // TODO: Replace
	}

	template <Arithmetic T>
	template <Arithmetic U>
	auto Matrix<T>::multiply(const Matrix& matA, const Matrix<U>& matB, MultiplicationAlgorithmType algo) -> Matrix<std::common_type_t<T, U>>
	{
		return matA.multiply(matB, algo);
	}
}
