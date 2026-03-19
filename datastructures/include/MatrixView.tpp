#pragma once
/**
 * @file MatrixView.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 14, 2026
 *
 * @brief MatrixView implementation.
 *        This file contains the implementation of member functions defined in MatrixView.h.
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
    MatrixView<T>::MatrixView(T* data, std::size_t size, std::size_t rows, std::size_t cols, std::size_t rowBlock,
                              std::size_t colBlock, std::size_t stride, bool bitCeil)
        : m_Data(data),
          m_Size(size),
          m_ViewRows(rows),
          m_ViewColumns(cols),
          m_RowBlock(rowBlock),
          m_ColumnBlock(colBlock),
          m_Stride(stride),
          m_BitCeil(bitCeil)
    {
        // Size stride validation
        if (m_Size < 1)
            throw std::out_of_range("Size must be greater than 0");

        if (m_Stride < 1 || m_Stride > m_Size)
            throw std::out_of_range(std::string("Stride must be greater than 0 and less than ") + std::to_string(m_Size));
             


        // Row Column Validation
        std::size_t maxRows = m_BitCeil ? std::bit_ceil(m_Size / m_Stride) : m_Size / m_Stride;
        std::size_t maxCols = m_BitCeil ? std::bit_ceil(m_Stride) : m_Stride;

        if (m_ViewRows > maxRows || m_ViewRows < 1)
            throw std::out_of_range(
                std::string("MatrixView cannot be initialized with rows greater than ") +
                std::to_string(maxRows) + std::string(" or less than 1"));
        if (m_ViewColumns > maxCols || m_ViewColumns < 1)
            throw std::out_of_range(std::string("MatrixView cannot be initialized with columns greater than ") +
                                        std::to_string(maxCols) + std::string(" or less than 1"));


        // Offset Validation
        if (m_ViewRows * m_RowBlock >= maxRows)
            throw std::out_of_range("Invalid row offset");

        if (m_ViewColumns * m_ColumnBlock >= maxCols)
            throw std::out_of_range("Invalid column offset");

        // Calculating offset for the real matrix
        m_Offset = m_RowBlock * m_Stride + m_ColumnBlock;
    }


    template <Arithmetic T>
    T& MatrixView<T>::operator()(std::size_t i, std::size_t j)
    {
        return T(0);
    }


    template <Arithmetic T>
    const T& MatrixView<T>::operator()(std::size_t i, std::size_t j) const
    {
        if (i >= m_ViewColumns || j >= m_ViewRows)
            throw std::out_of_range("Invalid row/column access");

        std::size_t actualRow = m_RowBlock * m_ViewRows + i;
        std::size_t actualColumn = m_ColumnBlock * m_ViewColumns + j;
        std::size_t maxRow = m_Size / m_Stride;

        if (!m_BitCeil && (actualRow >= maxRow || actualColumn >= m_Stride))
            throw std::out_of_range("Cannot access out-of-bounds region of original matrix with bitCeil = off");
        
        if (actualRow >= maxRow)
            return s_Zero;

        if (actualColumn >= m_Stride)
            return s_Zero;

        std::size_t index = actualRow * m_Stride + actualColumn;
        return m_Data[index];
    }

} // namespace datastructures