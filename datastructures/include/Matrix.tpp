#pragma once
/**
 * @file Matrix.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 09, 2026
 *
 * @brief Matrix implementation.
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
     *            MATRIX VIEW             *
     *                                    *
     **************************************/

    template <Arithmetic T>
    MatrixView<T>::MatrixView(T* data, std::size_t size, std::size_t rows, std::size_t cols, std::size_t rowOffset,
                              std::size_t colOffset, std::size_t stride, bool bitCeil)
        : m_Data(data),
          m_Size(size),
          m_ViewRows(rows),
          m_ViewColumns(cols),
          m_RowOffset(rowOffset),
          m_ColumnOffset(colOffset),
          m_Stride(stride),
          m_BitCeil(bitCeil)
    {
        // Row Column Validation
        std::size_t maxSize = m_BitCeil ? std::bit_ceil(m_Size) : m_Size;
        std::size_t maxStride = m_BitCeil ? std::bit_ceil(m_Stride) : m_Stride;
        if (m_ViewRows * m_ViewColumns > maxSize)
            throw std::runtime_error(
                "Invalid view matrix. View matrix should be initialized with rows and cols <= size of the matrix, "
                "or nearest power of 2, if bit_Ceil is true");

        // Offset Validation
        if (m_ViewRows * m_RowOffset >= maxSize / maxStride)
            throw std::runtime_error("Invalid row offset");

        if (m_ViewColumns * m_ColumnOffset >= maxStride)
            throw std::runtime_error("Invalid column offset");

        // Calculating offset for the real matrix
        m_Offset = m_RowOffset * m_Stride + m_ColumnOffset;
    }

    template <Arithmetic T>
    T& MatrixView<T>::operator()(std::size_t i, std::size_t j)
    {
        return T(0);
    }


    template <Arithmetic T>
    const T& MatrixView<T>::operator()(std::size_t i, std::size_t j) const
    {
        static const T zero = T(0);
        return zero;
        //// Out of bounds check for submatrix
        // if (i < 0 || i >= m_ViewRows || j < 0 || j >= m_ViewColumns)
        //     throw std::runtime_error("Invalid index for submatrix");

        // std::size_t size = m_Size, stride = m_Stride;
        // if (m_BitCeil)
        //{
        //     size = std::bit_ceil(size);
        //     stride = std::bit_ceil(m_Stride);
        // }


        // std::size_t globalOffset = m_Offset * stride; // How much to move per submatrix in 4x4 mat, with offset of 1
        // and
        //                                               // stride of 4, it will return the data store from 4th index.
        // std::size_t index = globalOffset + (i * m_ViewColumns) + j;

        //// Out of bound check for matrix
        // if (index >= size)
        //     throw std::runtime_error("Invalid bit ceiling. Check your passed in stride and offset");

        //// Returning Zero if bit ceil is on and out of bound of original matrix
        // static const T zero = T(0);
        // if (index >= m_Size)
        //     return zero;
        // return m_Data[index];
    }



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


    /**************************************
     *                                    *
     *         MATRIX OPERATIONS          *
     *                                    *
     **************************************/

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


    template <Arithmetic T>
    template <Arithmetic U>
    auto Matrix<T>::operator-(const Matrix<U>& other) const -> Matrix<std::common_type_t<T, U>>
    {
        if (m_Rows != other.m_Rows && m_Columns != other.m_Columns)
            throw std::runtime_error("Matrices of different dimensions cannot be subtracted");

        Matrix result(m_Rows, m_Columns);

        for (std::size_t row = 0; row < m_Rows; ++row)
            for (std::size_t col = 0; col < m_Columns; ++col)
                result(row, col) = (*this)(row, col) - other(row, col);

        return result;
    }


    template <Arithmetic T>
    template <Arithmetic U>
    Matrix<T>& Matrix<T>::operator-=(const Matrix<U>& other)
    {
        if (m_Rows != other.m_Rows && m_Columns != other.m_Columns)
            throw std::runtime_error("Matrices of different dimensions cannot be subtracted");

        for (std::size_t row = 0; row < m_Rows; ++row)
            for (std::size_t col = 0; col < m_Columns; ++col)
                (*this)(row, col) -= other(row, col);
        return *this;
    }


    template <Arithmetic T>
    template <Arithmetic U>
    MatrixView<T>& Matrix<T>::getView(std::size_t rowStart, std::size_t colStart, std::size_t rowEnd,
        std::size_t colEnd, bool bitCeilMatrix)
    {
        return MatrixView<int>(nullptr, 0, 0, 0, 0, 0, 0, false);
    }


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
    auto Matrix<T>::multiply(const Matrix<U>& other, MultiplicationAlgorithmType algo) const
        -> Matrix<std::common_type_t<T, U>>
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
    auto Matrix<T>::multiply(const Matrix& matA, const Matrix<U>& matB, MultiplicationAlgorithmType algo)
        -> Matrix<std::common_type_t<T, U>>
    {
        return matA.multiply(matB, algo);
    }


    template <typename T>
    std::ostream& operator<<(std::ostream& os, const MatrixView<T>& mv)
    {
        os << "Data: ";
        for (std::size_t i = 0; i < mv.m_Size; ++i)
            os << mv.m_Data[i] << (i < mv.m_Size - 1 ? ", " : "");

        os << "\nSize: " << mv.m_Size << " View(Row, Col): (" << mv.m_ViewRows << ", " << mv.m_ViewColumns
           << "), Offset(Row, Col): " << mv.m_Offset << ", " << mv.m_ColumnOffset << "), Stride: " << mv.m_Stride
           << " BitCeil Status: " << mv.m_BitCeil << "\n";

        return os;
    }
} // namespace datastructures
