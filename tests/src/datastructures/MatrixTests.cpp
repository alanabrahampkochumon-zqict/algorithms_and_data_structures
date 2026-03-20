/**
 * @file MatrixTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 03, 2026
 *
 * @brief Unit tests for @ref datastructures::Matrix.
 * @details Verifies initialization, bounds checking, and arithmetic operations.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "TestUtils.h"

#include <Matrix.h>
#include <cassert>
#include <concepts>
#include <gtest/gtest.h>


using namespace testutils;


/*********************************
 *                               *
 *            SETUP              *
 *                               *
 *********************************/

template <typename T>
    requires std::integral<T> || std::floating_point<T>
struct MatrixInitializerParams
{
    std::vector<std::vector<T>> inputData;
    std::size_t expectedRows;
    std::size_t expectedCols;
    std::vector<T> expectedData;
};
/** @brief Fixture for testing @ref datastructures::Matrix initialization with varied input shapes. */
class MatrixInitializationTests: public ::testing::TestWithParam<MatrixInitializerParams<int>>
{
};


template <typename T>
    requires std::integral<T> || std::floating_point<T>
struct MatrixViewParams
{
    datastructures::Matrix<T> mat;
    datastructures::Matrix<T> expectedView;
    std::size_t rowStart;
    std::size_t colStart;
    std::size_t rowSize;
    std::size_t colSize;
    bool bitCeil;
};
/** @brief Fixture for testing element-wise addition of two matrices. */
class MatrixViewTests: public ::testing::TestWithParam<MatrixViewParams<int>>
{
};


template <typename T>
    requires std::integral<T> || std::floating_point<T>
struct MatrixAdditionParams
{
    datastructures::Matrix<T> a;
    datastructures::Matrix<T> b;
    datastructures::Matrix<T> result;
};
class MatrixAdditionTests: public ::testing::TestWithParam<MatrixAdditionParams<int>>
{
};


template <typename T>
    requires std::integral<T> || std::floating_point<T>
struct MatrixSubtractionParams
{
    datastructures::Matrix<T> a;
    datastructures::Matrix<T> b;
    datastructures::Matrix<T> result;
};
class MatrixSubtractionTests: public ::testing::TestWithParam<MatrixSubtractionParams<int>>
{
};


template <typename T>
    requires std::integral<T> || std::floating_point<T>
struct MatrixMultiplicationParams
{
    datastructures::Matrix<T> a;
    datastructures::Matrix<T> b;
    datastructures::Matrix<T> result;
    datastructures::MultiplicationAlgorithmType algo;
};
class MatrixMultiplicationTests: public ::testing::TestWithParam<MatrixMultiplicationParams<int>>
{
};


/**
 * @addtogroup T_Mat_Init
 * @{
 */

/*********************************
 *                               *
 *     INITIALIZATION TESTS      *
 *                               *
 *********************************/

/** @test Verify that @ref datastructures::Matrix parameterized constructor initializes with @ref std::vector input data */
TEST_P(MatrixInitializationTests, InitializesToCorrectValues)
{
    // Given, some raw input numbers
    const auto& [inputData, expectedRows, expectedCols, expectedData] = GetParam();

    // When initialized as matrix
    datastructures::Matrix mat(inputData);

    // Then the matrix is initialized with correct values and row, column size
    EXPECT_EQ(mat.m_Rows, expectedRows);
    EXPECT_EQ(mat.m_Columns, expectedCols);
    if constexpr (std::is_floating_point_v<typename decltype(mat)::value_type>)
    {
        for (std::size_t i = 0; i < expectedRows; ++i)
        {
            for (std::size_t j = 0; j < expectedCols; ++j)
            {
                if constexpr (std::is_same_v<typename decltype(mat)::value_type, double>)
                    EXPECT_DOUBLE_EQ(expectedData[i * expectedCols + j], mat.m_Data[i * expectedCols + j]);
                else
                    EXPECT_FLOAT_EQ(static_cast<float>(expectedData[i * expectedCols + j]),
                                    static_cast<float>(mat.m_Data[i * expectedCols + j]));
            }
        }
    }
    else
        EXPECT_EQ(mat.m_Data, expectedData);
}

TEST(MatrixInitializationTest, RowColCountInitailizesZeroMatrix)
{
    // When a matrix is created with rows and columns
    constexpr int rows = 5;
    constexpr int cols = 7;
    const datastructures::Matrix<int> mat(rows, cols);

    // Then, rows and columns get correctly initialized
    EXPECT_EQ(rows, mat.m_Rows);
    EXPECT_EQ(cols, mat.m_Columns);

    // And, the elements form an identity matrix
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            EXPECT_EQ(0, mat.m_Data[i * cols + j]);
}

INSTANTIATE_TEST_SUITE_P(
    MatrixInitializationTestSuite, MatrixInitializationTests,
    ::testing::Values(
        MatrixInitializerParams{ std::vector<std::vector<int>>{ { 1, 2 }, { 3, 4 } }, 2, 2, { 1, 2, 3, 4 } },
        MatrixInitializerParams{ std::vector<std::vector<int>>{ { 1, 2 }, { 3, 4, 5 } }, 2, 3, { 1, 2, 0, 3, 4, 5 } },
        MatrixInitializerParams{ std::vector<std::vector<int>>{ { 1, 2, 3 }, { 4, 5 } }, 2, 3, { 1, 2, 3, 4, 5, 0 } },
        MatrixInitializerParams{ std::vector<std::vector<int>>{ { 1 }, { 2 }, { 3 } }, 3, 1, { 1, 2, 3 } },
        MatrixInitializerParams{
            std::vector<std::vector<int>>{ { 1, 2 }, {}, { 3, 4 } }, 3, 2, { 1, 2, 0, 0, 3, 4 } }));


/** @} */




/**
 * @addtogroup T_Mat_Access
 * @{
 */

/*********************************
 *                               *
 *         ACCESS TESTS          *
 *                               *
 *********************************/

/**
 * @test Verify @ref datastructures::Matrix can be accessed as (row, column)
 */
TEST(MatrixAccess, ElementsCanBeAccessedAsRowColumn)
{
    // Given a matrix is created with rows and columns
    constexpr int rows = 5;
    constexpr int cols = 7;
    datastructures::Matrix<int> mat(rows, cols);

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            mat(i, j) = static_cast<int>(i + j);

    // Then, the matrix can be access with (row, col)
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            EXPECT_EQ(i + j, mat(i, j));
}

TEST(MatrixAccess, AccessAtSizeThrowsError)
{
    // Given a matrix is created with rows and columns
    constexpr int rows = 5;
    constexpr int cols = 7;
    const datastructures::Matrix<int> mat(rows, cols);

    // When accessed at rows, cols
    // Then, it throws out of range error
    EXPECT_THROW(mat(rows, cols), std::out_of_range);
}

TEST(MatrixAccess, InvalidIndexThrowsError)
{
    // Given a matrix is created with rows and columns
    constexpr int rows = 5;
    constexpr int cols = 7;
    const datastructures::Matrix<int> mat(rows, cols);

    // When accessed at invalid index
    // Then, it throws out of range error
    EXPECT_THROW(mat(rows + 10, cols + 10), std::out_of_range);
}

/** @} */

/*********************************
 *                               *
 *         MUTATION TESTS        *
 *                               *
 *********************************/

TEST(MatrixMutation, ElementsCanBeMutatedAtRowColumn)
{
    // Given a matrix is created with rows and columns
    constexpr int rows = 5;
    constexpr int cols = 7;
    datastructures::Matrix<int> mat(rows, cols);

    // When elements are mutated
    for (std::size_t i = 0; i < rows; ++i)
        mat(i, i) = 50;

    // Then, the matrix can be access with (row, col)
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            EXPECT_EQ(i == j ? 50 : 0, mat(i, j));
}

TEST(MatrixMutation, AtSizeThrowsError)
{
    // Given a matrix is created with rows and columns
    constexpr int rows = 5;
    constexpr int cols = 7;
    datastructures::Matrix<int> mat(rows, cols);

    // When mutated at rowsize, colsize
    // Then, it throws out of range error error
    EXPECT_THROW(mat(rows, cols) = 5, std::out_of_range);
}

TEST(MatrixMutation, InvalidIndexThrowsError)
{
    // Given a matrix is created with rows and columns
    constexpr int rows = 5;
    constexpr int cols = 7;
    datastructures::Matrix<int> mat(rows, cols);

    // When mutated at invalid index
    // Then, it throws out of range error
    EXPECT_THROW(mat(rows + 10, cols + 10) = 6, std::out_of_range);
}


/*********************************
 *                               *
 *          VIEW TESTS           *
 *                               *
 *********************************/
//
// TEST_P(MatrixViewTests, ViewsGenerateCorrectValues)
//{
//    // When a matrix view is requested
//    const auto& [matrix, viewMatrix, rowStart, colStart, rowSize, colSize, bitCeil] = GetParam();
//
//    // Then it contains the given size
//}


/*********************************
 *                               *
 *        ADDITION TESTS         *
 *                               *
 *********************************/

TEST_P(MatrixAdditionTests, PlusOperatorReturnsMatrixWithElementsAddedTogether)
{
    // When two matrices are added together
    const auto& [matA, matB, matExpected] = GetParam();
    auto result = matA + matB;

    // Then, the resultant matrix contains elements of both added together
    EXPECT_MAT_EQ(matExpected, result);
}

TEST(MatrixAddtionTests, PlusOperatorDifferentDimensionThrowsException)
{
    // Given two matrices of different dimension
    datastructures::Matrix<int> matA(5, 5);
    datastructures::Matrix<int> matB(4, 3);

    // When added together
    // Then it throws a invalid argument error
    EXPECT_THROW(matA + matB, std::invalid_argument);
}


TEST_P(MatrixAdditionTests, PlusEqualOperatorCombinesFirstMatrixWithSecond)
{
    // When two matrices are added together with +=
    const auto& [matA, matB, matExpected] = GetParam();
    datastructures::Matrix result = matA;
    result += matB;

    // Then, the resultant matrix contains elements of both added together
    EXPECT_MAT_EQ(matExpected, result);
}

TEST(MatrixAddtionTests, PlusEqualsOperatorDifferentDimensionThrowsException)
{
    // Given two matrices of different dimension
    datastructures::Matrix<int> matA(5, 5);
    datastructures::Matrix<int> matB(4, 3);

    // When added and assigned (+=)
    // Then it throws an invalid argument error
    EXPECT_THROW(matA += matB, std::invalid_argument);
}

INSTANTIATE_TEST_SUITE_P(
    MatrixAdditionTestSuite, MatrixAdditionTests,
    ::testing::Values(
        MatrixAdditionParams<int>{
            { { { 1, 2 }, { 3, 4 } } }, { { { 5, 6 }, { 7, 8 } } }, { { { 6, 8 }, { 10, 12 } } } },
        MatrixAdditionParams<int>{
            { { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } } },
            { { { 10, 20, 30, 40 }, { 50, 60, 70, 80 }, { 90, 100, 110, 120 }, { 130, 140, 150, 160 } } },
            { { { 11, 22, 33, 44 }, { 55, 66, 77, 88 }, { 99, 110, 121, 132 }, { 143, 154, 165, 176 } } } },
        MatrixAdditionParams<int>{ { { { 1, 2, 3, 4 }, { 5, 6, 7, 8 } } },
                                   { { { 8, 8, 8, 8 }, { 3, 1, 6, 8 } } },
                                   { { { 9, 10, 11, 12 }, { 8, 7, 13, 16 } } } },
        MatrixAdditionParams<int>{ { { { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7, 8 } } },
                                   { { { 1, 2 }, { 4, 5 }, { 12, 13 }, { 16, 18 } } },
                                   { { { 2, 4 }, { 7, 9 }, { 17, 19 }, { 23, 26 } } } },
        MatrixAdditionParams<int>{ { { { 1, 2, 3, 4, 5, 6, 7, 8 } } },
                                   { { { 8, 9, 10, 11, 12, 13, 14, 15 } } },
                                   { { { 9, 11, 13, 15, 17, 19, 21, 23 } } } }));


/*********************************
 *                               *
 *       SUBTRACTION TESTS       *
 *                               *
 *********************************/

TEST_P(MatrixSubtractionTests, MinusOperatorReturnsMatrixWithElementsSubtractedFromEachOther)
{
    // When two matrices are subtracted
    const auto& [matA, matB, matExpected] = GetParam();
    auto result = matA - matB;

    // Then, the resultant matrix contains elements of a subtracted from b
    EXPECT_MAT_EQ(matExpected, result);
}

TEST(MatrixSubtractionTests, MinusOperatorDifferentDimensionThrowsException)
{
    // Given two matrices of different dimension
    datastructures::Matrix<int> matA(5, 5);
    datastructures::Matrix<int> matB(4, 3);

    // When subtracted
    // Then it throws an invalid argument error
    EXPECT_THROW(matA - matB, std::invalid_argument);
}

TEST_P(MatrixSubtractionTests, MinusEqualOperatorTakesSecondMatrixFromFirst)
{
    // When two matrices are subtracted with -=
    const auto& [matA, matB, matExpected] = GetParam();
    datastructures::Matrix result = matA;
    result -= matB;

    // Then, the resultant matrix contains elements of both added together
    EXPECT_MAT_EQ(matExpected, result);
}

TEST(MatrixSubtractionTests, MinusEqualsDifferentDimensionThrowsException)
{
    // Given two matrices of different dimension
    datastructures::Matrix<int> matA(5, 5);
    datastructures::Matrix<int> matB(4, 3);

    // When subtracted and assigned(-=)
    // Then, it throws an invalid argument error
    EXPECT_THROW(matA -= matB, std::invalid_argument);
}

INSTANTIATE_TEST_SUITE_P(
    MatrixSubtractionTestSuite, MatrixSubtractionTests,
    ::testing::Values(
        MatrixSubtractionParams<int>{
            { { { 1, 2 }, { 3, 4 } } }, { { { 5, 6 }, { 7, 8 } } }, { { { -4, -4 }, { -4, -4 } } } },
        MatrixSubtractionParams<int>{
            { { { 11, 12, 35, 23 }, { 100, 88, 238, 122 }, { 55, 111, 23, 111 }, { 777, 458, 238, 128 } } },
            { { { 10, 20, 30, 40 }, { 50, 60, 70, 80 }, { 90, 100, 110, 120 }, { 130, 140, 150, 160 } } },
            { { { 1, -8, 5, -17 }, { 50, 28, 168, 42 }, { -35, 11, -87, -9 }, { 647, 318, 88, -32 } } } },
        MatrixSubtractionParams<int>{ { { { 15, 15, 15, 18 }, { 21, 13, 21, 14 } } },
                                      { { { 8, 8, 8, 8 }, { 3, 1, 6, 8 } } },
                                      { { { 7, 7, 7, 10 }, { 18, 12, 15, 6 } } } },
        MatrixSubtractionParams<int>{ { { { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7, 8 } } },
                                      { { { 1, 2 }, { 4, 5 }, { 12, 13 }, { 16, 18 } } },
                                      { { { 0, 0 }, { -1, -1 }, { -7, -7 }, { -9, -10 } } } },
        MatrixSubtractionParams<int>{ { { { 118, 119, 120, 131, 141, 123, 123, 0 } } },
                                      { { { 8, 9, 10, 11, 12, 13, 14, 15 } } },
                                      { { { 110, 110, 110, 120, 129, 110, 109, -15 } } } }));


/*********************************
 *                               *
 *      MULTIPLICATION TESTS     *
 *                               *
 *********************************/

TEST_P(MatrixMultiplicationTests, MultiplicationProvidesCorrectResult)
{
    // When two matrices are multiplied together
    const auto& [matA, matB, matExpected, algo] = GetParam();
    auto result = matA.multiply(matB, algo);

    // Then, it matches expected result
    EXPECT_MAT_EQ(matExpected, result);
}

TEST(MatrixMultiplicationTestFixture,
     MultiplicationIsNotCommutative) // A * B != B * A
{
    // When two matrices are multiplied together
    datastructures::Matrix<int> matA{ { { 1, 2 }, { 3, 4 } } };
    datastructures::Matrix<int> matB{ { { 4, 5 }, { 6, 7 } } };
    auto result1 = matA.multiply(matB, datastructures::MultiplicationAlgorithmType::BRUTE_FORCE);
    auto result2 = matB.multiply(matA, datastructures::MultiplicationAlgorithmType::BRUTE_FORCE);

    // Then, it matches expected result
    EXPECT_MAT_NE(result1, result2);
}

TEST_P(MatrixMultiplicationTests, StaticWrapper_MultiplicationProvidesCorrectResult)
{
    // When two matrices are multiplied together with static wrapper
    const auto& [matA, matB, matExpected, algo] = GetParam();
    auto result = datastructures::Matrix<decltype(matExpected)::value_type>::multiply(matA, matB, algo);

    // Then, it matches expected result
    EXPECT_MAT_EQ(matExpected, result);
}

TEST(MatrixMutliplication, MatricesWithIncorrectRowColumnsThrowsException)
{
    // Given two matrices that can't be multiplied
    datastructures::Matrix<int> matA{ { { 1, 2 }, { 3, 4 } } };
    datastructures::Matrix<int> matB{ { { 3, 2 } } };

    // Then, their multiplication invalid argument error
    EXPECT_THROW(matA.multiply(matB, datastructures::MultiplicationAlgorithmType::BRUTE_FORCE), std::invalid_argument);
}

INSTANTIATE_TEST_SUITE_P(
    MatrixMutliplicationTestSuite, MatrixMultiplicationTests,
    ::testing::Values(
        MatrixMultiplicationParams<int>{ { { { 1, 2 }, { 3, 4 } } },
                                         { { { 5, 6 }, { 7, 8 } } },
                                         { { { 19, 22 }, { 43, 50 } } },
                                         datastructures::MultiplicationAlgorithmType::BRUTE_FORCE }, // 2x2 * 2x2
                                                                                                     // = 2x2
        MatrixMultiplicationParams<int>{ { { { 1 }, { 2 }, { 3 } } },
                                         { { { 4, 5, 6 } } },
                                         { { { 4, 5, 6 }, { 8, 10, 12 }, { 12, 15, 18 } } },
                                         datastructures::MultiplicationAlgorithmType::BRUTE_FORCE }, // 3x1 * 1x3
                                                                                                     // = 3x3
        MatrixMultiplicationParams<int>{ { { { 1, 2 }, { 3, 4 } } },
                                         { { { 1, 0 }, { 0, 1 } } },
                                         { { { 1, 2 }, { 3, 4 } } },
                                         datastructures::MultiplicationAlgorithmType::BRUTE_FORCE }, // 2x2 * I2 =
                                                                                                     // 2x2
        MatrixMultiplicationParams<int>{ { { { 1, 2 }, { 3, 4 } } },
                                         { { { 0, 0 }, { 0, 0 } } },
                                         { { { 0, 0 }, { 0, 0 } } },
                                         datastructures::MultiplicationAlgorithmType::BRUTE_FORCE } // 2x2 * 0 = 2x2(0)
        ));