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
         * @brief Accesses the element at the specified location.
         *
         * Provides read-write access to the element.
         *
         * @param row The row index to access.
         * @param col The column index to access.
         * @return T& A reference to the element at (row, col).
         * @throws std::out_of_range If row or col is outside the matrix bounds.
         */
        T& operator()(std::size_t row, std::size_t col);


        /**
         * @brief Accesses the element at the specified location (read-only).
         *
         * @param row The row index to access.
         * @param col The column index to access.
         * @return const T& A constant reference to the element at (row, col).
         * @throws std::out_of_range If row or col is outside the matrix bounds.
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