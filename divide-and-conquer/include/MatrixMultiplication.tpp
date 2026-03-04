#pragma once
namespace Algorithms
{
	template <Arithmetic T>
	Matrix<T>::Matrix(std::size_t rows, std::size_t cols): m_Rows(rows), m_Columns(cols)
	{
		m_Data.reserve(rows * cols);
		for (std::size_t i = 0; i < m_Rows; ++i)
			for (std::size_t j = 0; j < m_Columns; ++j)
				m_Data[i * m_Columns + j] = static_cast<T>(i == j);
	}

	template <Arithmetic T>
	Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list)
	{ }

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
}
