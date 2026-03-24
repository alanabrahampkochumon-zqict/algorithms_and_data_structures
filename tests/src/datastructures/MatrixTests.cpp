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

#include <Concepts.h>
#include <Matrix.h>
#include <cassert>
#include <gtest/gtest.h>


using namespace testutils;


/*********************************
 *                               *
 *            SETUP              *
 *                               *
 *********************************/

template <Arithmetic T>
struct MatrixInitializerParams
{
    std::vector<std::vector<T>> inputData;
    std::size_t expectedRows;
    std::size_t expectedCols;
    std::vector<T> expectedData;
};
/** @brief Test fixture for testing @ref datastructures::Matrix initialization with varied input shapes, parameterized
 *         by @ref MatrixInitializerParams. */
class MatrixInitializationTests: public ::testing::TestWithParam<MatrixInitializerParams<int>>
{};


template <Arithmetic T>
struct MatrixViewParams
{
    datastructures::Matrix<T> mat;
    datastructures::ReadOnlyMatrixView<T> expectedView;
    std::size_t rowBlock;
    std::size_t colBlock;
    std::size_t blockSize;
    bool bitCeil;
};
/** @brief Test fixture for verifying @ref datastructures::Matrix addition, parameterized by @ref MatrixViewParams. */
class MatrixViewTests: public ::testing::TestWithParam<MatrixViewParams<int>>
{};


template <Arithmetic T>
struct MatrixAdditionParams
{
    datastructures::Matrix<T> a;
    datastructures::Matrix<T> b;
    datastructures::Matrix<T> result;
};
/** @brief Test fixture for verifying @ref datastructures::Matrix multiplication, parameterized by @ref
 *         MatrixAdditionParams. */
class MatrixAdditionTests: public ::testing::TestWithParam<MatrixAdditionParams<int>>
{};


template <Arithmetic T>
struct MatrixSubtractionParams
{
    datastructures::Matrix<T> a;
    datastructures::Matrix<T> b;
    datastructures::Matrix<T> result;
};
/** @brief Test fixture for verifying @ref datastructures::Matrix subtraction, parameterized by @ref
 *         MatrixSubtractionParams. */
class MatrixSubtractionTests: public ::testing::TestWithParam<MatrixSubtractionParams<int>>
{};


template <Arithmetic T>
struct MatrixMultiplicationParams
{
    datastructures::Matrix<T> a;
    datastructures::Matrix<T> b;
    datastructures::Matrix<T> result;
    datastructures::MultiplicationAlgorithmType algo;
};
/** @brief Test fixture for verifying @ref datastructures::Matrix multiplication, parameterized by @ref
 *         MatrixMultiplicationParams. */
class MatrixMultiplicationTests: public ::testing::TestWithParam<MatrixMultiplicationParams<int>>
{};



/**
 * @addtogroup T_Mat_Init
 * @{
 */

/*********************************
 *                               *
 *     INITIALIZATION TESTS      *
 *                               *
 *********************************/

/**
 * @test Verify that @ref datastructures::Matrix parameterized constructor initializes with member variables with
 *       passed-in values.
 */
TEST_P(MatrixInitializationTests, InitializesToCorrectValues)
{
    const auto& [inputData, expectedRows, expectedCols, expectedData] = GetParam();

    datastructures::Matrix mat(inputData);

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

/** @test Verify that @ref datastructures::Matrix gives read access to elements with (row, column) syntax. */
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

/**
 * @test Verify that accessing elements of a @ref datastructures::Matrix at row, column size boundary throws
 *       @ref std::out_of_range.
 */
TEST(MatrixAccess, AccessAtSizeThrowsError)
{
    constexpr int rows = 5;
    constexpr int cols = 7;
    const datastructures::Matrix<int> mat(rows, cols);

    EXPECT_THROW(mat(rows, cols), std::out_of_range);
}

/**
 * @test Verify that accessing elements of a @ref datastructures::Matrix at out of range index throws
 *       @ref std::out_of_range.
 */
TEST(MatrixAccess, InvalidIndexThrowsError)
{
    constexpr int rows = 5;
    constexpr int cols = 7;
    const datastructures::Matrix<int> mat(rows, cols);

    EXPECT_THROW(mat(rows + 10, cols + 10), std::out_of_range);
}

/** @} */




/**
 * @addtogroup T_Mat_Mutation
 * @{
 */

/*********************************
 *                               *
 *         MUTATION TESTS        *
 *                               *
 *********************************/

/** @test Verify that @ref datastructures::Matrix gives read/write access to elements with (row, column) syntax. */
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


/**
 * @test Verify that a write access to an element at the (row, col) size boundary of @ref datastructures::Matrix throws
 *       @ref std::out_of_range.
 */
TEST(MatrixMutation, AtSizeThrowsError)
{
    constexpr int rows = 5;
    constexpr int cols = 7;
    datastructures::Matrix<int> mat(rows, cols);

    EXPECT_THROW(mat(rows, cols) = 5, std::out_of_range);
}


/**
 * @test Verify that a write access to an element at an out of range index of @ref datastructures::Matrix throws
 *       @ref std::out_of_range.
 */
TEST(MatrixMutation, InvalidIndexThrowsError)
{
    constexpr int rows = 5;
    constexpr int cols = 7;
    datastructures::Matrix<int> mat(rows, cols);

    EXPECT_THROW(mat(rows + 10, cols + 10) = 6, std::out_of_range);
}

/** @} */




/**
 * @addtogroup T_Mat_Add
 * @{
 */

/*********************************
 *                               *
 *        ADDITION TESTS         *
 *                               *
 *********************************/

/** @test Verify that @ref datastructures::Matrix add performs element-wise addition. */
TEST_P(MatrixAdditionTests, PlusOperatorReturnsMatrixWithElementsAddedTogether)
{
    const auto& [matA, matB, matExpected] = GetParam();
    auto result = matA + matB;

    EXPECT_MAT_EQ(matExpected, result);
}

/**
 * @test Verify that adding a @ref datastructures::Matrix to another @ref datastructures::Matrix of different dimension
 *        throws a @ref std::invalid_argument
 */
TEST(MatrixAddtionTests, PlusOperatorDifferentDimensionThrowsException)
{
    datastructures::Matrix<int> matA(5, 5);
    datastructures::Matrix<int> matB(4, 3);

    EXPECT_THROW(matA + matB, std::invalid_argument);
}

/**
 * @test Verify that the addition of @ref datastructures::Matrix using compound addition assignment operator (+=)
 *       performs an in-place addition operation.
 */
TEST_P(MatrixAdditionTests, PlusEqualOperatorCombinesFirstMatrixWithSecond)
{
    const auto& [matA, matB, matExpected] = GetParam();
    datastructures::Matrix result = matA;
    result += matB;

    EXPECT_MAT_EQ(matExpected, result);
}

/**
 * @test Verify that adding a @ref datastructures::Matrix to another @ref datastructures::Matrix of different dimension
 *       using compound addition assignment (+=) throws a @ref std::invalid_argument
 */
TEST(MatrixAddtionTests, PlusEqualsOperatorDifferentDimensionThrowsException)
{
    datastructures::Matrix<int> matA(5, 5);
    datastructures::Matrix<int> matB(4, 3);

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

/** @} */




/**
 * @addtogroup T_Mat_Sub
 * @{
 */

/*********************************
 *                               *
 *       SUBTRACTION TESTS       *
 *                               *
 *********************************/

/** @test Verify that @ref datastructures::Matrix subtract performs element-wise subtraction. */
TEST_P(MatrixSubtractionTests, MinusOperatorReturnsMatrixWithElementsSubtractedFromEachOther)
{
    const auto& [matA, matB, matExpected] = GetParam();
    auto result = matA - matB;

    EXPECT_MAT_EQ(matExpected, result);
}

/**
 * @test Verify that subtracting a @ref datastructures::Matrix from another @ref datastructures::Matrix of different
 *       dimension throws a @ref std::invalid_argument
 */
TEST(MatrixSubtractionTests, MinusOperatorDifferentDimensionThrowsException)
{
    datastructures::Matrix<int> matA(5, 5);
    datastructures::Matrix<int> matB(4, 3);

    EXPECT_THROW(matA - matB, std::invalid_argument);
}

/**
 * @test Verify that the subtraction of @ref datastructures::Matrix using the compound subtraction assignment
 *       operator (-=) performs an in-place subtraction operation
 */
TEST_P(MatrixSubtractionTests, MinusEqualOperatorTakesSecondMatrixFromFirst)
{
    const auto& [matA, matB, matExpected] = GetParam();
    datastructures::Matrix result = matA;
    result -= matB;

    EXPECT_MAT_EQ(matExpected, result);
}

/**
 * @test Verify that the subtraction of @ref datastructures::Matrix using the compound subtraction assignment (+=)
 *       among matrices of different dimension throws a @ref std::invalid_argument
 */
TEST(MatrixSubtractionTests, MinusEqualsDifferentDimensionThrowsException)
{
    datastructures::Matrix<int> matA(5, 5);
    datastructures::Matrix<int> matB(4, 3);

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

/** @} */



/**
 * @addtogroup T_Mat_View
 * @{
 */

/**************************************
 *                                    *
 *         MATRIX VIEW TESTS          *
 *                                    *
 **************************************/

/** @test Verify that @ref datastructures::Matrix::getView returns a block-level view mapped to the correct source boundaries. */
TEST_P(MatrixViewTests, ProvidesCorrectView)
{
    auto& [matrix, expectedView, rowBlock, colBlock, blockSize, bitCeil] = GetParam();
    auto mutableMatrix = matrix;
    const auto matrixView = mutableMatrix.getView(blockSize, rowBlock, colBlock, bitCeil);

    ASSERT_EQ(mutableMatrix.m_Data.data(), matrixView.m_Data);
    ASSERT_EQ(mutableMatrix.m_Data.size(), matrixView.m_Size);
    ASSERT_EQ(mutableMatrix.m_Columns, matrixView.m_Stride);
    ASSERT_EQ(blockSize, matrixView.m_ViewRows);
    ASSERT_EQ(blockSize, matrixView.m_ViewColumns);
    ASSERT_EQ(rowBlock, matrixView.m_RowBlock);
    ASSERT_EQ(colBlock, matrixView.m_ColumnBlock);
    ASSERT_EQ(bitCeil, matrixView.m_BitCeil);
}

datastructures::Matrix<int> mat1{ { { 1, 2, 3, 4 }, { 1, 2, 3, 4 }, { 1, 2, 3, 4 }, { 1, 2, 3, 4 } } };
const datastructures::ReadOnlyMatrixView view1_00{ mat1.m_Data.data(), mat1.m_Data.size(), 2, 2, 0, 0, 4, true };
const datastructures::ReadOnlyMatrixView view1_01{ mat1.m_Data.data(), mat1.m_Data.size(), 2, 2, 0, 1, 4, true };
const datastructures::ReadOnlyMatrixView view1_10{ mat1.m_Data.data(), mat1.m_Data.size(), 2, 2, 1, 0, 4, true };
const datastructures::ReadOnlyMatrixView view1_11{ mat1.m_Data.data(), mat1.m_Data.size(), 2, 2, 1, 1, 4, true };

datastructures::Matrix<int> mat2{ { { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 } } };
const datastructures::ReadOnlyMatrixView view2_00{ mat2.m_Data.data(), mat2.m_Data.size(), 2, 2, 0, 0, 3, true };
const datastructures::ReadOnlyMatrixView view2_01{ mat2.m_Data.data(), mat2.m_Data.size(), 2, 2, 0, 1, 3, true };
const datastructures::ReadOnlyMatrixView view2_10{ mat2.m_Data.data(), mat2.m_Data.size(), 2, 2, 1, 0, 3, true };
const datastructures::ReadOnlyMatrixView view2_11{ mat2.m_Data.data(), mat2.m_Data.size(), 2, 2, 1, 1, 3, true };

datastructures::Matrix<int> mat3{ { { 1, 2, 3 }, { 1, 2, 3 }, { 1, 2, 3 } } };
const datastructures::ReadOnlyMatrixView view3_00{ mat3.m_Data.data(), mat3.m_Data.size(), 2, 2, 0, 0, 3, false };
const datastructures::ReadOnlyMatrixView view3_01{ mat3.m_Data.data(), mat3.m_Data.size(), 2, 2, 0, 1, 3, false };
const datastructures::ReadOnlyMatrixView view3_10{ mat3.m_Data.data(), mat3.m_Data.size(), 2, 2, 1, 0, 3, false };
const datastructures::ReadOnlyMatrixView view3_11{ mat3.m_Data.data(), mat3.m_Data.size(), 2, 2, 1, 1, 3, false };

INSTANTIATE_TEST_CASE_P(
    MatrixViewTestCase, MatrixViewTests,
    ::testing::Values(
        MatrixViewParams{ mat1, view1_00, 0, 0, 2, true }, MatrixViewParams{ mat1, view1_01, 0, 1, 2, true },
        MatrixViewParams{ mat1, view1_10, 1, 0, 2, true }, MatrixViewParams{ mat1, view1_11, 1, 1, 2, true },

        MatrixViewParams{ mat2, view2_00, 0, 0, 2, true }, MatrixViewParams{ mat2, view2_01, 0, 1, 2, true },
        MatrixViewParams{ mat2, view2_10, 1, 0, 2, true }, MatrixViewParams{ mat2, view2_11, 1, 1, 2, true },

        MatrixViewParams{ mat3, view3_00, 0, 0, 2, false }, MatrixViewParams{ mat3, view3_01, 0, 1, 2, false },
        MatrixViewParams{ mat3, view3_10, 1, 0, 2, false }, MatrixViewParams{ mat3, view3_11, 1, 1, 2, false }));

/** @} */



/**
 * @addtogroup T_Mat_Mul
 * @{
 */

/*********************************
 *                               *
 *      MULTIPLICATION TESTS     *
 *                               *
 *********************************/

/** @test Verify that @ref datastructures::Matrix multiplication performs the composition of linear transformations. */
TEST_P(MatrixMultiplicationTests, MultiplicationProvidesCorrectResult)
{
    const auto& [matA, matB, matExpected, algo] = GetParam();
    const auto result = matA.multiply(matB, algo);

    EXPECT_MAT_EQ(matExpected, result);
}

/** @test Verify that @ref datastructures::Matrix multiplication is non-commutative. */
TEST(MatrixMultiplicationTestFixture,
     MultiplicationIsNotCommutative) // A * B != B * A
{
    const datastructures::Matrix<int> matA{ { { 1, 2 }, { 3, 4 } } };
    const datastructures::Matrix<int> matB{ { { 4, 5 }, { 6, 7 } } };
    const auto result1 = matA.multiply(matB, datastructures::MultiplicationAlgorithmType::BRUTE_FORCE);
    const auto result2 = matB.multiply(matA, datastructures::MultiplicationAlgorithmType::BRUTE_FORCE);

    EXPECT_MAT_NE(result1, result2);
}

/**
 * @test Verify that the static wrapper multiplication of @ref datastructures::Matrix performs the composition of
 *       linear transformations.
 */
TEST_P(MatrixMultiplicationTests, StaticWrapper_MultiplicationProvidesCorrectResult)
{
    const auto& [matA, matB, matExpected, algo] = GetParam();
    const auto result = datastructures::Matrix<decltype(matExpected)::value_type>::multiply(matA, matB, algo);

    EXPECT_MAT_EQ(matExpected, result);
}

/**
 * @test Verify that the multiplication of @ref datastructures::Matrix with another @ref datastructures::Matrix of
 *        mismatched dimensions throws a std::invalid_argument exception.
 */
TEST(MatrixMutliplication, MatricesWithIncorrectRowColumnsThrowsException)
{
    const datastructures::Matrix<int> matA{ { { 1, 2 }, { 3, 4 } } };
    const datastructures::Matrix<int> matB{ { { 3, 2 } } };

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
        MatrixMultiplicationParams<int>{
            { { { 1, 2 }, { 3, 4 } } },
            { { { 0, 0 }, { 0, 0 } } },
            { { { 0, 0 }, { 0, 0 } } },
            datastructures::MultiplicationAlgorithmType::BRUTE_FORCE }, // 2x2 * 0 = 2x2(0),
        MatrixMultiplicationParams<int>{ { { { 1, 2 }, { 3, 4 } } },
                                         { { { 5, 6 }, { 7, 8 } } },
                                         { { { 19, 22 }, { 43, 50 } } },
                                         datastructures::MultiplicationAlgorithmType::DIVIDE_AND_CONQUER }, // 2x2 * 2x2
                                                                                                            // = 2x2
        MatrixMultiplicationParams<int>{ { { { 1 }, { 2 }, { 3 } } },
                                         { { { 4, 5, 6 } } },
                                         { { { 4, 5, 6 }, { 8, 10, 12 }, { 12, 15, 18 } } },
                                         datastructures::MultiplicationAlgorithmType::DIVIDE_AND_CONQUER }, // 3x1 * 1x3
                                                                                                            // = 3x3
        MatrixMultiplicationParams<int>{ { { { 1, 2 }, { 3, 4 } } },
                                         { { { 1, 0 }, { 0, 1 } } },
                                         { { { 1, 2 }, { 3, 4 } } },
                                         datastructures::MultiplicationAlgorithmType::DIVIDE_AND_CONQUER }, // 2x2 * I2
                                                                                                            // =
                                                                                                            // 2x2
        MatrixMultiplicationParams<int>{ { { { 1, 2 }, { 3, 4 } } },
                                         { { { 0, 0 }, { 0, 0 } } },
                                         { { { 0, 0 }, { 0, 0 } } },
                                         datastructures::MultiplicationAlgorithmType::DIVIDE_AND_CONQUER },
        MatrixMultiplicationParams<int>{ { { { 3 } } },
                                         { { { 4 } } },
                                         { { { 12 } } },
                                         datastructures::MultiplicationAlgorithmType::DIVIDE_AND_CONQUER }
        // 2x2 * 0 = 2x2(0)
        ));

/** @} */