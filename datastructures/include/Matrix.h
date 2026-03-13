#pragma once
/**
 * @file Matrix.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 09, 2026
 *
 * @brief Template matrix for integral and floating point types.
 * @note Matrix can be initialized with a row, col or using an initializer list of elements.
 *
 * @par Operations
 * Addition, Subtraction, and Multiplication, with 3 implementation for multiplication. Check
 * `MultiplicationAlgorithmType` for details.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <concepts>
#include <vector>


namespace datastructures
{
    enum class MultiplicationAlgorithmType
    {
        BRUTE_FORCE,
        DIVIDE_AND_CONQUER,
        STRASSENS
    };

    template <typename T>
    concept Arithmetic = std::integral<T> || std::floating_point<T>;


    // template <Arithmetic T>
    // struct MatrixView
    //{
    //     T* data;                  ///< Pointer to the data of the original matrix
    //     std::size_t rows;         ///< Rows of MatrixView
    //     std::size_t columns;      ///< Columns of Matrix View
    //     std::size_t rowOffset;    ///< Row offset of the Matrix View
    //     std::size_t colOffset;    ///< Column offset of the Matrix View
    //     std::size_t columnStride; //< Number of columns in the original Matrix

    //    bool m_BitCeil; ///< Whether to virtually pad the view with zeros(when ceiling matrix nearest power of size)

    //    MatrixView(T* data, std::size_t rows, std::size_t columns, std::size_t rowOffset, std::size_t colOffset,
    //               std::size_t columnStride, bool m_BitCeil = false)
    //        : data(data),
    //          rows(rows),
    //          columns(columns),
    //          rowOffset(rowOffset),
    //          colOffset(colOffset),
    //          columnStride(columnStride),
    //          m_BitCeil(m_BitCeil)
    //    {
    //    }
    //};

    template <Arithmetic T>
    struct MatrixView
    {
        T* m_Data;                 ///< Pointer to the data of the original matrix
        std::size_t m_Size;        ///< Size of matrix data(1D)
        std::size_t m_ViewRows;    ///< Number of rows in the MatrixView
        std::size_t m_ViewColumns; ///< Number of columns in the Matrix View
        std::size_t m_RowOffset; ///< Row offset of the Matrix View
        std::size_t m_ColumnOffset; ///< Column offset of the Matrix View
        std::size_t
            m_Offset; ///< Calculated offset of the current view
        std::size_t m_Stride;    ///< Length of each strip of data(usually the column count of an NxN Matrix)

        bool m_BitCeil; ///< Flag that returns a T(0) instead of throwing runtime_exception when passed in an index
                        ///< larger
                        // than the size of matrix.


        MatrixView(T* data, std::size_t size, std::size_t rows, std::size_t cols, std::size_t rowOffset, std::size_t colOffset,
                   std::size_t stride, bool bitCeil = false);

        /**
         * @brief Gives access to the value at ith row and jth column of the view matrix
         * @param i row index of the submatrix
         * @param j column index of the submatrix
         * @return value at the index or 0 if out of bounds and `bitCeil` is true.
         * @throws `std::runtime_error` if access is out of bounds (i < 0 or i >= m_Rows) or access is in bounds of the
         * submatrix but out of bounds for the original matrix
         * @par Example
         * 3x3 matrix with offset of 6 and stride of 3 (last 2x2 submatrix) and trying to access (1, 1) -> throws
         * `std::runtime_error` if `bitCeil = false` and 0 if `bitCeil = true`.
         */
        T& operator()(std::size_t i, std::size_t j);

        const T& operator()(std::size_t i, std::size_t j) const;
    };


    template <Arithmetic T>
    struct Matrix
    {
        using value_type = T;

        std::size_t m_Rows, m_Columns;
        std::vector<T> m_Data;

        Matrix(std::size_t rows, std::size_t cols);
        Matrix(const std::vector<std::vector<T>>& list);

        /**
         * Assignment operator overload.
         * @param row row to be accessed.
         * @param col column to be accessed.
         * @return element<T> if it exists.
         * @throws runtime_exception if the row or columns are out of bounds.
         */
        T& operator()(std::size_t row, std::size_t col);

        /**
         * Access operator overload.
         * @param row row to be accessed.
         * @param col column to be accessed.
         * @return element<T> if it exists.
         * @throws runtime_exception if the row or columns are out of bounds.
         */
        const T& operator()(std::size_t row, std::size_t col) const;


        /**************************************
         *                                    *
         *       ARITHMETIC OPERATIONS        *
         *                                    *
         **************************************/

        template <Arithmetic U>
        auto operator+(const Matrix<U>& other) const -> Matrix<std::common_type_t<T, U>>;

        template <Arithmetic U>
        Matrix& operator+=(const Matrix<U>& other);

        template <Arithmetic U>
        auto operator-(const Matrix<U>& other) const -> Matrix<std::common_type_t<T, U>>;

        template <Arithmetic U>
        Matrix& operator-=(const Matrix<U>& other);

        template <Arithmetic U>
        MatrixView<T>& getView(std::size_t rowStart, std::size_t colStart, std::size_t rowEnd, std::size_t colEnd,
                               bool bitCeilMatrix = false);

        template <Arithmetic U>
        auto multiply(const Matrix<U>& other,
                      MultiplicationAlgorithmType algo = MultiplicationAlgorithmType::DIVIDE_AND_CONQUER) const
            -> Matrix<std::common_type_t<T, U>>;

        template <Arithmetic U>
        static auto multiply(const Matrix& matA, const Matrix<U>& matB,
                             MultiplicationAlgorithmType algo = MultiplicationAlgorithmType::DIVIDE_AND_CONQUER)
            -> Matrix<std::common_type_t<T, U>>;

        // TODO: *, *= op
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const datastructures::MatrixView<T>& mv);

} // namespace datastructures


#include "Matrix.tpp"