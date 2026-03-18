#pragma once
/**
 * @file MatrixView.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 14, 2026
 *
 * @brief Matrix view for @ref datastructures::Matrix to enable viewing and performing operations on a Submatrix.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Concepts.h>
#include <cstddef>
#include <iomanip>

namespace datastructures
{
    template <Arithmetic T>
    struct MatrixView
    {
        T* m_Data;                 ///< Pointer to the data of the original matrix
        std::size_t m_Size;        ///< Size of matrix data(1D)
        std::size_t m_ViewRows;    ///< Number of rows in the MatrixView
        std::size_t m_ViewColumns; ///< Number of columns in the Matrix View
        std::size_t m_RowBlock;    ///< Row block of the Matrix View
        std::size_t m_ColumnBlock; ///< Column block of the Matrix View
        std::size_t m_Offset;      ///< Calculated offset of the current view
        std::size_t m_Stride;      ///< Length of each strip of data(usually the column count of an NxN Matrix)

        bool m_BitCeil; ///< Flag that returns a T(0) instead of throwing runtime_exception when passed in an index
                        ///< larger
                        // than the size of matrix.


        MatrixView(T* data, std::size_t size, std::size_t rows, std::size_t cols, std::size_t rowOffset,
                   std::size_t colOffset, std::size_t stride, bool bitCeil = false);

        /**
         * @brief Access the element at (i, j) index of the matrix view for write operation.
         *
         * @param i Row index of the view matrix.
         * @param j Column index of the view matrix.
         * @return const reference to value at the (@p i, @p j) or 0 if out of bounds and @p bitCeil is true.
         *
         * @throws `std::invalid_argument` if access is out of bounds (i < 0 or i >= m_Rows) or access is in bounds of
         * the submatrix but out of bounds for the original matrix.
         *
         * @par Example
         * 3x3 matrix with a m_RowBlock of 1 and m_ColumnBlock of 1 (last 2x2 submatrix) and trying to access (1, 1) ->
         * throws
         * @ref `std::invalid_argument`.
         */
        T& operator()(std::size_t i, std::size_t j);

        /**
         * @brief Access the element at (i, j) of the MatrixView for read operation.
         *
         * @param i Row index of the view matrix.
         * @param j Column index of the view matrix.
         * @return Reference to the value at the (@p i, @p j).
         *
         * @throws `std::invalid_argument` if access is out of bounds (i < 0 or i >= m_Rows) of the **original matrix**.
         *
         * @par Example
         * 3x3 matrix with a m_RowBlock of 1 and m_ColumnBlock of 1 (last 2x2 submatrix) and trying to access (1, 1) ->
         * throws @ref `std::invalid_argument` if @ref m_BitCeil = false and 0 if @ref m_BitCeil = true.
         */
        const T& operator()(std::size_t i, std::size_t j) const;

        /**
         * @brief Write the matrix view to an output stream.
         * Formats the matrix view as a string representation for debugging or logging.
         *
         * @tparam T Numeric type of the matrix.
         * @param os The output stream to write to
         * @param mv The matrix to be streamed.
         * @return A reference to the output stream @p os.
         */
        friend std::ostream& operator<<(std::ostream& os, const MatrixView<T>& mv)
        {
            for (std::size_t i = 0; i < mv.m_ViewRows; ++i)
            {
                for (std::size_t j = 0; j < mv.m_ViewColumns; ++j)
                    os << std::fixed << std::setprecision(2) << mv(i, j);
                os << "\n";
            }
            return os;
        }
        
        private:
        static inline const T s_Zero = T(0); ///< Shared null object for BitCeil
    };
} // namespace datastructures


#include "MatrixView.tpp"