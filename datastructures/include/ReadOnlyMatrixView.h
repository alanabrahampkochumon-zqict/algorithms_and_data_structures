#pragma once
/**
 * @file ReadOnlyMatrixView.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 24, 2026
 *
 * @brief A non-owning read-only view to enable viewing and performing operations on a subset of @ref
 * datastructures::Matrix.
 *
 * @note For a view that supports both read-write operations see @ref datastructures::MatrixView.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Concepts.h>
#include <cstddef>
#include <iomanip>

// TODO: Add move offset for moving the block view around non-linear block like rowStart of 1 and end of 3 which is
// technically an even view block.
namespace datastructures
{
    template <Arithmetic T>
    struct ReadOnlyMatrixView
    {
        const T* m_Data;                 ///< Pointer to the data of the original matrix
        const std::size_t m_Size;        ///< Size of matrix data(1D)
        const std::size_t m_ViewRows;    ///< Number of rows in the MatrixView
        const std::size_t m_ViewColumns; ///< Number of columns in the Matrix View
        const std::size_t m_RowBlock;    ///< Row block of the Matrix View
        const std::size_t m_ColumnBlock; ///< Column block of the Matrix View
        const std::size_t m_Stride;      ///< Length of each strip of data(usually the column count of an NxN Matrix)

        const bool m_BitCeil; ///< Flag that returns a T(0) instead of throwing runtime_exception when passed in an
                              ///< index larger
                              // than the size of matrix.
        // TODO: Update docs

        /**
         * @brief Construct a non-owning view into a subset of a Matrix.
         *        This constructor initializes a virtual window into an existing contiguous 1D array.
         *        It uses block-based indexing to support recursive sub-matrix partitioning.
         *
         * @param[in] data      Pointer to the first element of the parent matrix memory.
         * @param[in] size      Total element count of the parent matrix's physical storage.
         * @param[in] rows      The logical height (number of rows) of this view.
         * @param[in] cols      The logical width (number of columns) of this view.
         * @param[in] rowBlock  Vertical block index used to calculate the physical row offset.
         * @param[in] colBlock  Horizontal block index used to calculate the physical column offset.
         * @param[in] stride    The physical width (row-length) of the parent matrix.
         * @param[in] bitCeil   If true, out-of-bounds accesses return T(0) up to the next power of 2.
         *
         * @throw std::out_of_range If the calculated physical offset exceeds the parent's size.
         */
        ReadOnlyMatrixView(const T* data, std::size_t size, std::size_t rows, std::size_t cols, std::size_t rowBlock,
                           std::size_t colBlock, std::size_t stride, bool bitCeil = false);


        /**
         * @brief Access the element at (i, j) within the view for mutation.
         *        Provides an immutable reference to the underlying matrix data.
         *        This operation requires the indices to map to a physical memory location within the parent matrix.
         *
         * @param[in] i Local row index relative to the start of the view.
         * @param[in] j Local column index relative to the start of the view.
         * @return A const reference to the element at the mapped physical location.
         *
         * @note Virtual elements (enabled by bitCeil) returns T(0) when accessed.
         *
         * @throws std::out_of_range If (i, j) exceeds view dimensions, or if the mapped
         * physical index exceeds the parent matrix storage (when bitCeil is false).
         *
         * @par Example
         * For a 3x3 parent, a 2x2 view starting at Block(1,1) maps its local(1,1) to parent(3,3).
         * Since parent(3,3) is out of bounds for a 3x3 matrix, will return @ref T(0).
         */
        const T& operator()(std::size_t i, std::size_t j) const;


        /**
         * @brief Return a submatrix view on the current view matrix.
         *
         * @param[in] rowBlock     The submatrix's row block.
         * @param[in] colBlock     The submatrix's column block.
         * @param[in] rowBlockSize The submatrix's row span.
         * @param[in] colBlockSize The submatrix's column span.
         *
         * @return A readonly submatrix view of the current MatrixView.
         */
        constexpr ReadOnlyMatrixView<T> getSubView(std::size_t rowBlock, std::size_t colBlock,
                                                   std::size_t rowBlockSize, std::size_t colBlockSize);


        /**
         * @brief Write the @ref MatrixView to an output stream.
         *        Formats the matrix view as a string representation for debugging or logging.
         *
         * @tparam T Numeric type of the matrix.
         * @param[in,out] os The output stream to write to.
         * @param[in] mv The matrix to be streamed.
         * @return A reference to the output stream @p os.
         */
        friend std::ostream& operator<<(std::ostream& os, const ReadOnlyMatrixView<T>& mv)
        {
            for (std::size_t i = 0; i < mv.m_ViewRows; ++i)
            {
                for (std::size_t j = 0; j < mv.m_ViewColumns; ++j)
                    os << std::fixed << std::setprecision(2) << mv(i, j) << "  ";
                os << "\n";
            }
            return os;
        }


        private:
        static inline const T s_Zero = T(0); ///< Shared null object for BitCeil
    };


    template <Arithmetic T>
    constexpr ReadOnlyMatrixView<T> ReadOnlyMatrixView<T>::getSubView(std::size_t rowBlock, std::size_t colBlock, std::size_t rowBlockSize, std::size_t colBlockSize)
    {
        return *this;
    }
} // namespace datastructures


#include "ReadOnlyMatrixView.tpp"