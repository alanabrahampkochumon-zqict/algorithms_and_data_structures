#pragma once
/**
 * @file Matrix.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 09, 2026
 *
 * @brief Templated matrix for integral and floating point types.
 * @note Matrix can be initialized with a row, col or using an initializer list of elements.
 *
 * @par Operations
 * Addition, Subtraction, and Multiplication, with 3 implementation for multiplication. Check
 * `MultiplicationAlgorithmType` for details.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <Concepts.h>
#include <MatrixView.h>
#include <vector>


// TODO: Naive transpose multiplication to optimize cache hits(Since we are using 1D structure internally)

namespace datastructures
{
    enum class MultiplicationAlgorithmType
    {
        BRUTE_FORCE,
        DIVIDE_AND_CONQUER,
        STRASSENS
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
         * @brief Access the element at the specified location.
         *        Provides read-write access to the element.
         *
         * @param row The row index to access.
         * @param col The column index to access.
         *
         * @return A reference to the element at (row, col).
         *
         * @throws std::out_of_range If row or col is outside the matrix bounds.
         */
        T& operator()(std::size_t row, std::size_t col);


        /**
         * @brief Access the element at the specified location (read-only).
         *
         * @param row The row index to access.
         * @param col The column index to access.
         *
         * @return A constant reference to the element at (row, col).
         *
         * @throws std::out_of_range If row or col is outside the matrix bounds.
         */
        const T& operator()(std::size_t row, std::size_t col) const;




        /**************************************
         *                                    *
         *       ARITHMETIC OPERATIONS        *
         *                                    *
         **************************************/

        /**
         * @brief Perform element-wise addition of two matrices.
         *
         * @tparam U Numeric type of the RHS Matrix.
         *
         * @param rhs The matrix to add.
         *
         * @return A new matrix containing element-wise sum with promoted type.
         *
         * @throws std::invalid_argument If matrix dimensions do not match.
         */
        template <Arithmetic U>
        auto operator+(const Matrix<U>& rhs) const -> Matrix<std::common_type_t<T, U>>;


        /**
         * @brief Add another matrix to this matrix.
         *        Perform element-wise addition in-place and returns a reference to this matrix.
         *
         * @tparam U Numeric type of the RHS Matrix.
         *
         * @param rhs The matrix to add.
         *
         * @return A reference to this matrix (*this) after addition.
         *
         * @throws std::invalid_argument If matrix dimensions do not match.
         */
        template <Arithmetic U>
        Matrix& operator+=(const Matrix<U>& rhs);


        /**
         * @brief Perform element-wise subtraction of two matrices.
         *
         * @tparam U Numeric type of the RHS Matrix.
         *
         * @param rhs The matrix to subtract.
         *
         * @return A new matrix containing element-wise difference with promoted type.
         *
         * @throws std::invalid_argument If matrix dimensions do not match.
         */
        template <Arithmetic U>
        auto operator-(const Matrix<U>& rhs) const -> Matrix<std::common_type_t<T, U>>;


        /**
         * @brief Subtract another matrix from this matrix.
         *        Perform element-wise subtraction in-place and returns a reference to this matrix.
         *
         * @tparam U Numeric type of the RHS Matrix.
         *
         * @param rhs The matrix to subtract.
         *
         * @return A reference to this matrix (*this) after subtraction.
         *
         * @throws std::invalid_argument If matrix dimensions do not match.
         */
        template <Arithmetic U>
        Matrix& operator-=(const Matrix<U>& rhs);


        /**
         * @brief Create a submatrix view of the current matrix.
         *
         * @note Padding applied will be virtual zeroes.
         *
         * @param rowStart      Starting row index of the view.
         * @param colStart      Starting column index of the view.
         * @param rowSize       Number of rows in the view.
         * @param colSize       Number of columns in the view.
         * @param bitCeilMatrix If true, pads the view dimensions to the next power of two.
         *
         * @return A @ref datastructures::MatrixView of size (@p rowSize, @p colSize) or the padded size.
         */
        MatrixView<T> getView(std::size_t rowStart, std::size_t colStart, std::size_t rowSize, std::size_t colSize,
                              bool bitCeilMatrix = false);


        /**
         * @brief Compute the product of two matrices.
         *
         * @details Represents the composition of linear transformations.
         *          Uses row-column multiplication (dot product) semantics.
         *
         * @tparam U Numeric type of the RHS matrix.
         *
         * @param rhs  The matrix to multiply.
         * @param algo The multiplication algorithm to use. See @ref datastructures::MultiplicationAlgorithmType
         *
         * @return A new matrix containing the multiplication result with promoted type.
         *
         * @throws std::invalid_argument If the column count of this matrix does not match the row count of @p rhs.
         */
        template <Arithmetic U>
        auto multiply(const Matrix<U>& rhs,
                      MultiplicationAlgorithmType algo = MultiplicationAlgorithmType::DIVIDE_AND_CONQUER) const
            -> Matrix<std::common_type_t<T, U>>;

        /**
         * @brief @copybrief multiply(const Matrix<U>&, MultiplicationAlgorithmType)
         *
         * @tparam U Numeric type of RHS matrix.
         *
         * @param lhs  The left hand side matrix.
         * @param rhs  The right hand side matrix.
         * @param algo The multiplication algorithm to use. See @ref datastructures::MultiplicationAlgorithmType
         *
         * @return A new matrix containing the multiplication result with promoted type.
         *
         * @throws std::invalid_argument If the column count of @p matA does not match the row count of @p matB.
         */
        template <Arithmetic U>
        static auto multiply(const Matrix& lhs, const Matrix<U>& rhs,
                             MultiplicationAlgorithmType algo = MultiplicationAlgorithmType::DIVIDE_AND_CONQUER)
            -> Matrix<std::common_type_t<T, U>>;

        // TODO: *, *= op
    };

} // namespace datastructures


#include "Matrix.tpp"