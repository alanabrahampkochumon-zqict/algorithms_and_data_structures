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
#include <type_traits>


namespace datastructures
{


    /**************************************
     *                                    *
     *       MATRIX INITIALIZATION        *
     *                                    *
     **************************************/

    template <Arithmetic T>
    Matrix<T>::Matrix(const std::size_t rows, const std::size_t cols): m_Rows(rows), m_Columns(cols)
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
    T& Matrix<T>::operator()(const std::size_t row, const std::size_t col)
    {
        if (row < 0 || row >= m_Rows || col < 0 || col >= m_Columns)
            throw std::out_of_range("Invalid index");
        return m_Data[row * m_Columns + col];
    }

    template <Arithmetic T>
    const T& Matrix<T>::operator()(const std::size_t row, const std::size_t col) const
    {
        if (row < 0 || row >= m_Rows || col < 0 || col >= m_Columns)
            throw std::out_of_range("Invalid index");
        return m_Data[row * m_Columns + col];
    }


    template <Arithmetic T>
    constexpr Matrix<T> Matrix<T>::getSubmatrix(const std::size_t rowStart, const std::size_t colStart,
                                                const std::size_t rowSize, const std::size_t colSize,
                                                const bool bitCeil) const
    {
        const std::size_t maxRows = bitCeil ? std::bit_ceil(m_Rows) : m_Rows;
        const std::size_t maxCols = bitCeil ? std::bit_ceil(m_Columns) : m_Columns;

        if (rowStart + rowSize > maxRows)
            throw std::out_of_range("Invalid row index and size!");
        if (colSize + colStart > maxCols)
            throw std::out_of_range("Invalid column index and size!");

        Matrix matrix(rowSize, colSize);

        for (std::size_t i = rowStart; i < rowStart + rowSize; ++i)
            for (std::size_t j = colStart; j < colStart + colSize; ++j)
                if (i < m_Rows && j < m_Columns)
                    matrix(i - rowStart, j - colStart) = m_Data[i * m_Columns + j];
                else
                    matrix(i - rowStart, j - colStart) = T(0);

        return matrix;
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
    ReadOnlyMatrixView<T> Matrix<T>::getView(std::size_t blockSize, std::size_t rowBlock, std::size_t colBlock,
                                             bool bitCeilMatrix) const
    {
        std::cout << m_Data.size() << "flat size \n";
        return ReadOnlyMatrixView<T>(m_Data.data(), m_Data.size(), blockSize, blockSize, rowBlock, colBlock, m_Columns,
                                     bitCeilMatrix);
    }

    template <Arithmetic T, Arithmetic U>
    static auto bruteForce(const Matrix<T>& matA, const Matrix<U>& matB)
    {
        using R = std::common_type_t<T, U>;
        Matrix<R> result(matA.m_Rows, matB.m_Columns);
        for (std::size_t i = 0; i < matA.m_Rows; ++i)
            for (std::size_t j = 0; j < matB.m_Columns; ++j)
                for (std::size_t k = 0; k < matB.m_Rows; ++k)
                    result(i, j) += matA(i, k) * matB(k, j);

        return result;
    }


    /**
     * @brief Combine the four quadrants of a matrix to form a matrix of the passed-in size.
     *        Ideally, all the quadrants needs to be of the same dimension.
     *
     * @tparam T The numeric type of the matrix elements.
     *
     * @param rows   The total number of rows in the resulting matrix.
     * @param cols   The total number of columns in the resulting matrix.
     * @param quad00 The top-left quadrant of the matrix.
     * @param quad01 The top-right quadrant of the matrix.
     * @param quad10 The bottom-left quadrant of the matrix.
     * @param quad11 The bottom-right quadrant of the matrix.
     *
     * @return A new matrix of size @p rows by @p cols with elements combined from the four quadrants.
     */
    template <Arithmetic T>
    static Matrix<T> mergeQuadrantsAndFlatten(const std::size_t rows, const std::size_t cols, const Matrix<T>& quad00,
                                              const Matrix<T>& quad01, const Matrix<T>& quad10, const Matrix<T>& quad11)
    {
        // TODO: Add size checking to ensure the quads are mergeable when exposing as an API
        // TODO: Add tests when exposed as API
        Matrix<T> mat(rows, cols);
        for (std::size_t i = 0; i < quad00.m_Rows; ++i)
            for (std::size_t j = 0; j < quad00.m_Columns; ++j)
                mat(i, j) = quad00(i, j);

        for (std::size_t i = 0; i < quad01.m_Rows; ++i)
            for (std::size_t j = 0; j < (cols - quad01.m_Columns); ++j)
                mat(i, j + quad00.m_Columns) = quad01(i, j);

        for (std::size_t i = 0; i < (rows - quad00.m_Rows); ++i)
            for (std::size_t j = 0; j < quad10.m_Columns; ++j)
                mat(quad00.m_Rows + i, j) = quad10(i, j);

        for (std::size_t i = 0; i < (rows - quad00.m_Rows); ++i)
            for (std::size_t j = 0; j < (cols - quad10.m_Columns); ++j)
                mat(quad00.m_Rows + i, quad10.m_Columns + j) = quad11(i, j);

        return mat;
    }

    template <Arithmetic T, Arithmetic U>
    static Matrix<std::common_type_t<T, U>> divideAndConquer(const ReadOnlyMatrixView<T>& lhs,
                                                             const ReadOnlyMatrixView<U>& rhs)
    {
        using R = std::common_type_t<T, U>;
        if (lhs.m_ViewColumns == 1 && lhs.m_ViewRows == 1)
            return Matrix<T>({ { lhs(0, 0) * rhs(0, 0) } });


        const auto halfRows = lhs.m_ViewRows / 2;       // Symmetric
        const auto halfColumns = lhs.m_ViewColumns / 2; // Symmetric

        // c00 = a00 * b00 + a01 * b10
        const Matrix<R> c00 =
            divideAndConquer(lhs.getSubview(0, 0, halfRows, halfColumns), rhs.getSubview(0, 0, halfRows, halfColumns)) +
            divideAndConquer(lhs.getSubview(0, 1, halfRows, halfColumns), rhs.getSubview(1, 0, halfRows, halfColumns));
        // c01 = a00 * b01 + a01 * b11
        const Matrix<R> c01 =
            divideAndConquer(lhs.getSubview(0, 0, halfRows, halfColumns), rhs.getSubview(0, 1, halfRows, halfColumns)) +
            divideAndConquer(lhs.getSubview(0, 1, halfRows, halfColumns), rhs.getSubview(1, 1, halfRows, halfColumns));
        // c10 = a10 * b00 + a11 * b10
        const Matrix<R> c10 =
            divideAndConquer(lhs.getSubview(1, 0, halfRows, halfColumns), rhs.getSubview(0, 0, halfRows, halfColumns)) +
            divideAndConquer(lhs.getSubview(1, 1, halfRows, halfColumns), rhs.getSubview(1, 0, halfRows, halfColumns));
        // c11 = a10 * b01 + a11 * b11
        const Matrix<R> c11 =
            divideAndConquer(lhs.getSubview(1, 0, halfRows, halfColumns), rhs.getSubview(0, 1, halfRows, halfColumns)) +
            divideAndConquer(lhs.getSubview(1, 1, halfRows, halfColumns), rhs.getSubview(1, 1, halfRows, halfColumns));
        // clang-format on

        const auto realRows = std::min(lhs.m_Size / lhs.m_Stride, lhs.m_ViewRows);
        const auto realCols = std::min(rhs.m_Stride, rhs.m_ViewColumns);

        return mergeQuadrantsAndFlatten(realRows, realCols, c00, c01, c10, c11);
    }

    template <Arithmetic T, Arithmetic U>
    static Matrix<std::common_type_t<T, U>> strassens(const Matrix<T>& lhs, const Matrix<U>& rhs)
    {
        using R = std::common_type_t<T, U>;
        if (lhs.m_Columns == 1 && lhs.m_Rows == 1)
            return Matrix<T>({ { lhs(0, 0) * rhs(0, 0) } });

        const auto lHalfRows = lhs.m_Rows / 2;
        const auto lHalfColumns = lhs.m_Columns / 2;
        const auto rHalfRows = rhs.m_Rows / 2;
        const auto rHalfColumns = rhs.m_Columns / 2;

        // Using 1-based indexing to be inline with CLRS
        const auto a11 = lhs.getSubmatrix(0, 0, lHalfRows, lHalfColumns);
        const auto a12 = lhs.getSubmatrix(0, lHalfColumns, lHalfRows, lhs.m_Columns - lHalfColumns);
        const auto a21 = lhs.getSubmatrix(lHalfRows, 0, lhs.m_Rows - lHalfRows, lHalfColumns);
        const auto a22 =
            lhs.getSubmatrix(lHalfRows, lHalfColumns, lhs.m_Rows - lHalfRows, lhs.m_Columns - lHalfColumns);

        const auto b11 = rhs.getSubmatrix(0, 0, rHalfRows, rHalfColumns);
        const auto b12 = rhs.getSubmatrix(0, rHalfColumns, rHalfRows, lhs.m_Columns - rHalfColumns);
        const auto b21 = rhs.getSubmatrix(rHalfRows, 0, lhs.m_Rows - rHalfRows, rHalfColumns);
        const auto b22 =
            rhs.getSubmatrix(rHalfRows, rHalfColumns, lhs.m_Rows - rHalfRows, lhs.m_Columns - rHalfColumns);

        // TODO: Update to use view with add and subtract support
        const auto s1 = b12 - b22;
        const auto s2 = a11 + a12;
        const auto s3 = a21 + a22;
        const auto s4 = b21 - b11;
        const auto s5 = a11 + a22;
        const auto s6 = b11 + b22;
        const auto s7 = a12 - a22;
        const auto s8 = b21 + b22;
        const auto s9 = a11 - a21;
        const auto s10 = b11 + b12;

        const auto p1 = strassens(a11, s1);
        const auto p2 = strassens(s2, b22);
        const auto p3 = strassens(s3, b11);
        const auto p4 = strassens(a22, s4);
        const auto p5 = strassens(s5, s6);
        const auto p6 = strassens(s7, s8);
        const auto p7 = strassens(s9, s10);

        const auto c11 = p5 + p4 - p2 + p6;
        const auto c12 = p1 + p2;
        const auto c21 = p3 + p4;
        const auto c22 = p5 + p1 - p3 - p7;

        return mergeQuadrantsAndFlatten(lhs.m_Rows, rhs.m_Columns, c11, c12, c21, c22);
    }


    /**
     * @brief Reduce a matrix into a smaller @p targetRowSize x @p targetColumnSize matrix.
     *
     * @tparam T The numeric type of the matrix. Must satisfy @ref Arithmetic concept.
     *
     * @param mat              The matrix to reduce.
     * @param targetRowSize    The row size of the resulting matrix.
     * @param targetColumnSize The column size of the resulting matrix.
     *
     * @return A new @ref Matrix instance having the first entries  @p targetRowSize by @p targetColumnSize 
     *         of the original matrix.
     */
    template <Arithmetic T>
    Matrix<T> reduce(const Matrix<T>& mat, std::size_t targetRowSize, std::size_t targetColumnSize)
    {
        if (targetRowSize > mat.m_Rows)
            throw std::out_of_range("Invalid row size. Must be less than the matrix's row count");
        if (targetColumnSize > mat.m_Columns)
            throw std::out_of_range("Invalid column size. Must be less than the matrix's column count");

        Matrix<T> reducedMatrix(targetRowSize, targetColumnSize);

        for (std::size_t i = 0; i < targetRowSize; ++i)
            for (std::size_t j = 0; j < targetColumnSize; ++j)
                reducedMatrix(i, j) = mat(i, j);

        return reducedMatrix;
    }

    template <Arithmetic T>
    template <Arithmetic U>
    auto Matrix<T>::multiply(const Matrix<U>& rhs, const MultiplicationAlgorithmType algo) const
        -> Matrix<std::common_type_t<T, U>>
    {
        if (this->m_Columns != rhs.m_Rows)
            throw std::invalid_argument("Invalid matrix size");

        switch (algo)
        {
            case MultiplicationAlgorithmType::BRUTE_FORCE:
                return bruteForce(*this, rhs);
            case MultiplicationAlgorithmType::DIVIDE_AND_CONQUER:
                return divideAndConquer(getView(std::bit_ceil(std::max(m_Rows, m_Columns)), 0, 0, true),
                                        rhs.getView(std::bit_ceil(std::max(rhs.m_Rows, rhs.m_Columns)), 0, 0, true));
            case MultiplicationAlgorithmType::STRASSENS:
                return strassens(*this, rhs);
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
