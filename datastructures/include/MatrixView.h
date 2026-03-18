#pragma once
/**
 * @file MatrixView.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 14, 2026
 *
 * @brief A non-owning view to enable viewing and performing operations on a subset of @ref datastructures::Matrix.
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

        /**
         * @brief Construct a non-owning view into a subset of a Matrix.
         *        This constructor initializes a virtual window into an existing contiguous 1D array.
         *        It uses block-based indexing to support recursive sub-matrix partitioning.
         *
         * @param data      Pointer to the first element of the parent matrix memory.
         * @param size      Total element count of the parent matrix's physical storage.
         * @param rows      The logical height (number of rows) of this view.
         * @param cols      The logical width (number of columns) of this view.
         * @param rowBlock  Vertical block index used to calculate the physical row offset.
         * @param colBlock  Horizontal block index used to calculate the physical column offset.
         * @param stride    The physical width (row-length) of the parent matrix.
         * @param bitCeil   If true, out-of-bounds accesses return T(0) up to the next power of 2.
         * 
         * @throw std::out_of_range If the calculated physical offset exceeds the parent's size.
         */
        MatrixView(T* data, std::size_t size, std::size_t rows, std::size_t cols, std::size_t rowBlock,
                   std::size_t colBlock, std::size_t stride, bool bitCeil = false);

        /**
         * @brief Access the element at (i, j) within the view for mutation.
         * Provides a mutable reference to the underlying matrix data. This operation
         * requires the indices to map to a physical memory location within the parent matrix.
         *
         * @param i Local row index relative to the start of the view.
         * @param j Local column index relative to the start of the view.
         * @return A reference to the element at the mapped physical location.
         *
         * @note Virtual elements (enabled by bitCeil) cannot be mutated and will trigger an exception.
         *
         * @throws std::out_of_range If (i, j) exceeds view dimensions, or if the mapped
         * physical index exceeds the parent matrix storage (even if bitCeil is true).
         *
         * @par Example
         * For a 3x3 parent, a 2x2 view starting at Block(1,1) maps its local(1,1) to parent(3,3).
         * Since parent(3,3) is out of bounds for a 3x3 matrix, this throws std::out_of_range.
         */
        T& operator()(std::size_t i, std::size_t j);

        /**
         * @brief Access the element at (i, j) within the view for mutation.
         * Provides an immutable reference to the underlying matrix data. This operation
         * requires the indices to map to a physical memory location within the parent matrix.
         *
         * @param i Local row index relative to the start of the view.
         * @param j Local column index relative to the start of the view.
         * @return A const reference to the element at the mapped physical location.
         *
         * @note Virtual elements (enabled by bitCeil) returns T(0) when accessed.
         *
         * @throws std::out_of_range If (i, j) exceeds view dimensions, or if the mapped
         * physical index exceeds the parent matrix storage (even if bitCeil is true).
         *
         * @par Example
         * For a 3x3 parent, a 2x2 view starting at Block(1,1) maps its local(1,1) to parent(3,3).
         * Since parent(3,3) is out of bounds for a 3x3 matrix, will return @ref T(0).
         */
        const T& operator()(std::size_t i, std::size_t j) const;

        /**
         * @brief Write the @ref MatrixView to an output stream.
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