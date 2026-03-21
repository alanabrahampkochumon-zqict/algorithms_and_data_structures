#pragma once
/**
 * @file Matrix.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 09, 2026
 *
 * @brief Matrix template implementation.
 * @details This file contains the definitions of the template members declared in @ref datastructures::Matrix.h
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <algorithm>
#include <bit>
#include <cstddef>


namespace datastructures
{


    /**************************************
     *                                    *
     *       MATRIX INITIALIZATION        *
     *                                    *
     **************************************/

    template <Arithmetic T>
    Matrix<T>::Matrix(std::size_t rows, std::size_t cols): m_Rows(rows), m_Columns(cols)
    {
        m_Data.resize(rows * cols);
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




    /**************************************
     *                                    *
     *           MATRIX ACCESS            *
     *                                    *
     **************************************/

    template <Arithmetic T>
    T& Matrix<T>::operator()(std::size_t row, std::size_t col)
    {
        if (row < 0 || row >= m_Rows || col < 0 || col >= m_Columns)
            throw std::out_of_range("Invalid index");
        return m_Data[row * m_Columns + col];
    }

    template <Arithmetic T>
    const T& Matrix<T>::operator()(std::size_t row, std::size_t col) const
    {
        if (row < 0 || row >= m_Rows || col < 0 || col >= m_Columns)
            throw std::out_of_range("Invalid index");
        return m_Data[row * m_Columns + col];
    }




    /**************************************
     *                                    *
     *         MATRIX OPERATIONS          *
     *                                    *
     **************************************/

    template <Arithmetic T>
    template <Arithmetic U>
    auto Matrix<T>::operator+(const Matrix<U>& rhs) const -> Matrix<std::common_type_t<T, U>>
    {
        if (m_Rows != rhs.m_Rows && m_Columns != rhs.m_Columns)
            throw std::invalid_argument("Matrices of different dimensions cannot be added together");

        Matrix result(m_Rows, m_Columns);

        for (std::size_t row = 0; row < m_Rows; ++row)
            for (std::size_t col = 0; col < m_Columns; ++col)
                result(row, col) = (*this)(row, col) + rhs(row, col);

        return result;
    }


    template <Arithmetic T>
    template <Arithmetic U>
    Matrix<T>& Matrix<T>::operator+=(const Matrix<U>& rhs)
    {
        if (m_Rows != rhs.m_Rows && m_Columns != rhs.m_Columns)
            throw std::invalid_argument("Matrices of different dimensions cannot be added together");

        for (std::size_t row = 0; row < m_Rows; ++row)
            for (std::size_t col = 0; col < m_Columns; ++col)
                (*this)(row, col) += rhs(row, col);
        return *this;
    }


    template <Arithmetic T>
    template <Arithmetic U>
    auto Matrix<T>::operator-(const Matrix<U>& rhs) const -> Matrix<std::common_type_t<T, U>>
    {
        if (m_Rows != rhs.m_Rows && m_Columns != rhs.m_Columns)
            throw std::invalid_argument("Matrices of different dimensions cannot be subtracted");

        Matrix result(m_Rows, m_Columns);

        for (std::size_t row = 0; row < m_Rows; ++row)
            for (std::size_t col = 0; col < m_Columns; ++col)
                result(row, col) = (*this)(row, col) - rhs(row, col);

        return result;
    }


    template <Arithmetic T>
    template <Arithmetic U>
    Matrix<T>& Matrix<T>::operator-=(const Matrix<U>& rhs)
    {
        if (m_Rows != rhs.m_Rows && m_Columns != rhs.m_Columns)
            throw std::invalid_argument("Matrices of different dimensions cannot be subtracted");

        for (std::size_t row = 0; row < m_Rows; ++row)
            for (std::size_t col = 0; col < m_Columns; ++col)
                (*this)(row, col) -= rhs(row, col);
        return *this;
    }


    template <Arithmetic T>
    MatrixView<T> Matrix<T>::getView(std::size_t blockSize, std::size_t rowBlock,
        std::size_t colBlock, bool bitCeilMatrix) const
    {
        return MatrixView<int>(nullptr, 0, 0, 0, 0, 0, 0, false);
    }


    // template <Arithmetic T>
    // template <Arithmetic U>
    // MatrixView<T>& Matrix<T>::getView(std::size_t rowStart, std::size_t colStart, std::size_t rowEnd,
    //     std::size_t colEnd, bool bitCeilMatrix)
    //{
    //     return MatrixView<int>(nullptr, 0, 0, 0, 0, 0, 0, false);
    // }


    /*template <Arithmetic T>
    template <Arithmetic U>
    MatrixView<T>& Matrix<T>::getView(std::size_t rowStart, std::size_t colStart, std::size_t rowEnd,
        std::size_t colEnd, bool bitCeilMatrix)
    {
        return MatrixView();
    }*/


    // template <Arithmetic T>
    // template <Arithmetic U>
    // Matrix<T>& Matrix<T>::getView(std::size_t rowStart, std::size_t colStart, std::size_t rowEnd, std::size_t colEnd,
    //     bool bitCeilMatrix)
    //{
    //     // TODO: Stub
    //     return Matrix(rowEnd - rowStart, colEnd - colStart);
    // }


    template <Arithmetic T, Arithmetic U>
    static auto bruteForce(const Matrix<T>& matA, const Matrix<U>& matB)
    {
        using R = std::common_type_t<T, U>;
        Matrix<R> result(matA.m_Rows, matB.m_Columns);
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
    auto Matrix<T>::multiply(const Matrix<U>& rhs, MultiplicationAlgorithmType algo) const
        -> Matrix<std::common_type_t<T, U>>
    {
        if (this->m_Columns != rhs.m_Rows)
            throw std::invalid_argument("Invalid matrix size");

        switch (algo)
        {
            case MultiplicationAlgorithmType::BRUTE_FORCE:
                return bruteForce(*this, rhs);
            case MultiplicationAlgorithmType::DIVIDE_AND_CONQUER:
                break;
            case MultiplicationAlgorithmType::STRASSENS:
                break;
            default:
                break;
        }
        return Matrix(m_Rows, rhs.m_Columns); // TODO: Replace
    }

    template <Arithmetic T>
    template <Arithmetic U>
    auto Matrix<T>::multiply(const Matrix& lhs, const Matrix<U>& rhs, MultiplicationAlgorithmType algo)
        -> Matrix<std::common_type_t<T, U>>
    {
        return lhs.multiply(rhs, algo);
    }
} // namespace datastructures
