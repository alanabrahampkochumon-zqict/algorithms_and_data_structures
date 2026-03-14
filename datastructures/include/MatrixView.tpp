#pragma once
/**
 * @file MatrixView.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 14, 2026
 *
 * @brief MatrixView implementation.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <bit>

namespace datastructures
{

    /**************************************
     *                                    *
     *          INITIALIZATION            *
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

} // namespace datastructures