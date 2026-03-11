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


    template <Arithmetic T>
    struct MatrixView
    {
        T* data;                  ///< Pointer to the data of the original matrix
        std::size_t rows;         ///< Rows of MatrixView
        std::size_t columns;      ///< Columns of Matrix View
        std::size_t rowOffset;    ///< Row offset of the Matrix View
        std::size_t colOffset;    ///< Column offset of the Matrix View
        std::size_t columnStride; //< Number of columns in the original Matrix

        bool bitCeil; ///< Whether to virtually pad the view with zeros(when ceiling matrix nearest power of size)

        MatrixView(T* data, std::size_t rows, std::size_t columns, std::size_t rowOffset, std::size_t colOffset,
                   std::size_t columnStride, bool bitCeil = false)
            : data(data),
              rows(rows),
              columns(columns),
              rowOffset(rowOffset),
              colOffset(colOffset),
              columnStride(columnStride),
              bitCeil(bitCeil)
        {
        }
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

} // namespace datastructures

#include "Matrix.tpp"