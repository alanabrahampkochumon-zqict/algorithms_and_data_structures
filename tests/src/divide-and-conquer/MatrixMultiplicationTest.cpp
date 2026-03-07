#include <gtest/gtest.h>

#include <MatrixMultiplication.h>
#include <cassert>
#include <concepts>

#include "../../include/TestUtils.h"
using namespace TestUtils;

template <typename T>
  requires std::integral<T> || std::floating_point<T>
struct MatrixInitializerParams {
  std::vector<std::vector<T>> inputData;
  std::size_t expectedRows;
  std::size_t expectedCols;
  std::vector<T> expectedData;
};
class MatrixInitializationTestFixture
    : public ::testing::TestWithParam<MatrixInitializerParams<int>> {};

template <typename T>
  requires std::integral<T> || std::floating_point<T>
struct MatrixAdditionParams {
  
};

template <typename T>
  requires std::integral<T> || std::floating_point<T>
struct MatrixMultiplicationParams {
  Algorithms::Matrix<T> a;
  Algorithms::Matrix<T> b;
  Algorithms::Matrix<T> result;
  Algorithms::MultiplicationAlgorithmType algo;
};
class MatrixMultiplicationTestFixture
    : public ::testing::TestWithParam<MatrixMultiplicationParams<int>> {};

TEST_P(MatrixInitializationTestFixture, InitializesToCorrectValues) {
  // Given, some raw input numbers
  const auto &[inputData, expectedRows, expectedCols, expectedData] =
      GetParam();

  // When initialized as matrix
  Algorithms::Matrix mat(inputData);

  // Then the matrix is initialized with correct values and row, column size
  EXPECT_EQ(mat.m_Rows, expectedRows);
  EXPECT_EQ(mat.m_Columns, expectedCols);
  if constexpr (std::is_floating_point_v<typename decltype(mat)::value_type>) {
    for (std::size_t i = 0; i < expectedRows; ++i) {
      for (std::size_t j = 0; j < expectedCols; ++j) {
        if constexpr (std::is_same_v<typename decltype(mat)::value_type,
                                     double>)
          EXPECT_DOUBLE_EQ(expectedData[i * expectedCols + j],
                           mat.m_Data[i * expectedRows + j]);
        else
          EXPECT_FLOAT_EQ(
              static_cast<float>(expectedData[i * expectedCols + j]),
              static_cast<float>(mat.m_Data[i * expectedRows + j]));
      }
    }
  } else
    EXPECT_EQ(mat.m_Data, expectedData);
}

INSTANTIATE_TEST_SUITE_P(
    MatrixInitializationTest, MatrixInitializationTestFixture,
    ::testing::Values(
        MatrixInitializerParams{
            std::vector<std::vector<int>>{{1, 2}, {3, 4}}, 2, 2, {1, 2, 3, 4}},
        MatrixInitializerParams{
            std::vector<std::vector<int>>{{1, 2}, {3, 4, 5}},
            2,
            3,
            {1, 2, 0, 3, 4, 5}},
        MatrixInitializerParams{
            std::vector<std::vector<int>>{{1, 2, 3}, {4, 5}},
            2,
            3,
            {1, 2, 3, 4, 5, 0}},
        MatrixInitializerParams{
            std::vector<std::vector<int>>{{1}, {2}, {3}}, 3, 1, {1, 2, 3}},
        MatrixInitializerParams{
            std::vector<std::vector<int>>{{1, 2}, {}, {3, 4}},
            3,
            2,
            {1, 2, 0, 0, 3, 4}}));

TEST(MatrixInitializationTest, RowColCountInitailizesZeroMatrix) {
  // When a matrix is created with rows and columns
  constexpr int rows = 5;
  constexpr int cols = 7;
  const Algorithms::Matrix<int> mat(rows, cols);

  // Then, rows and columns get correctly initialized
  EXPECT_EQ(rows, mat.m_Rows);
  EXPECT_EQ(cols, mat.m_Columns);

  // And, the elements form an identity matrix
  for (std::size_t i = 0; i < rows; ++i)
    for (std::size_t j = 0; j < cols; ++j)
      EXPECT_EQ(0, mat.m_Data[i * cols + j]);
}

TEST(MatrixAccess, ElementsCanBeAccessedAsRowColumn) {
  // Given a matrix is created with rows and columns
  constexpr int rows = 5;
  constexpr int cols = 7;
  Algorithms::Matrix<int> mat(rows, cols);

  for (std::size_t i = 0; i < rows; ++i)
    for (std::size_t j = 0; j < cols; ++j)
      mat(i, j) = static_cast<int>(i + j);

  // Then, the matrix can be access with (row, col)
  for (std::size_t i = 0; i < rows; ++i)
    for (std::size_t j = 0; j < cols; ++j)
      EXPECT_EQ(i + j, mat(i, j));
}

TEST(MatrixAccess, AccessAtSizeThrowsError) {
  // Given a matrix is created with rows and columns
  constexpr int rows = 5;
  constexpr int cols = 7;
  const Algorithms::Matrix<int> mat(rows, cols);

  // When accessed at rowsize, colsize
  // Then, it throws runtime error
  EXPECT_THROW(mat(rows, cols), std::runtime_error);
}

TEST(MatrixAccess, InvalidIndexThrowsError) {
  // Given a matrix is created with rows and columns
  constexpr int rows = 5;
  constexpr int cols = 7;
  const Algorithms::Matrix<int> mat(rows, cols);

  // When accessed at invalid index
  // Then, it throws runtime error
  EXPECT_THROW(mat(rows + 10, cols + 10), std::runtime_error);
}

TEST(MatrixMutation, ElementsCanBeMutatedAtRowColumn) {
  // Given a matrix is created with rows and columns
  constexpr int rows = 5;
  constexpr int cols = 7;
  Algorithms::Matrix<int> mat(rows, cols);

  // When elements are mutated
  for (std::size_t i = 0; i < rows; ++i)
    mat(i, i) = 50;

  // Then, the matrix can be access with (row, col)
  for (std::size_t i = 0; i < rows; ++i)
    for (std::size_t j = 0; j < cols; ++j)
      EXPECT_EQ(i == j ? 50 : 0, mat(i, j));
}

TEST(MatrixMutation, AtSizeThrowsError) {
  // Given a matrix is created with rows and columns
  constexpr int rows = 5;
  constexpr int cols = 7;
  Algorithms::Matrix<int> mat(rows, cols);

  // When mutated at rowsize, colsize
  // Then, it throws runtime error
  EXPECT_THROW(mat(rows, cols) = 5, std::runtime_error);
}

TEST(MatrixMutation, InvalidIndexThrowsError) {
  // Given a matrix is created with rows and columns
  constexpr int rows = 5;
  constexpr int cols = 7;
  Algorithms::Matrix<int> mat(rows, cols);

  // When mutated at invalid index
  // Then, it throws runtime error
  EXPECT_THROW(mat(rows + 10, cols + 10) = 6, std::runtime_error);
}

TEST_P(MatrixMultiplicationTestFixture, MultiplicationProvidesCorrectResult) {
  // When two matrices are multiplied together
  const auto &[matA, matB, matExpected, algo] = GetParam();
  auto result = matA.multiply(matB, algo);

  // Then, it matches expected result
  EXPECT_MAT_EQ(matExpected, result);
}

TEST(MatrixMultiplicationTestFixture,
     MultiplicationIsNotCommutative) // A * B != B * A
{
  // When two matrices are multiplied together
  Algorithms::Matrix<int> matA{{{1, 2}, {3, 4}}};
  Algorithms::Matrix<int> matB{{{4, 5}, {6, 7}}};
  auto result1 =
      matA.multiply(matB, Algorithms::MultiplicationAlgorithmType::BRUTE_FORCE);
  auto result2 =
      matB.multiply(matA, Algorithms::MultiplicationAlgorithmType::BRUTE_FORCE);

  // Then, it matches expected result
  EXPECT_MAT_NE(result1, result2);
}

TEST_P(MatrixMultiplicationTestFixture,
       StaticWrapper_MultiplicationProvidesCorrectResult) {
  // When two matrices are multiplied together with static wrapper
  const auto &[matA, matB, matExpected, algo] = GetParam();
  auto result = Algorithms::Matrix<decltype(matExpected)::value_type>::multiply(
      matA, matB, algo);

  // Then, it matches expected result
  EXPECT_MAT_EQ(matExpected, result);
}

// TODO: Op *, *= tests

TEST(MatrixMutliplication, MatricesWithIncorrectRowColumnsThrowsException) {
  // Given two matrices that can't be multiplied
  Algorithms::Matrix<int> matA{{{1, 2}, {3, 4}}};
  Algorithms::Matrix<int> matB{{{3, 2}}};

  // Then, their multiplication throws an error
  EXPECT_THROW(
      matA.multiply(matB, Algorithms::MultiplicationAlgorithmType::BRUTE_FORCE),
      std::runtime_error);
}

INSTANTIATE_TEST_SUITE_P(
    MatrixMutliplication, MatrixMultiplicationTestFixture,
    ::testing::Values(
        MatrixMultiplicationParams<int>{
            {{{1, 2}, {3, 4}}},
            {{{5, 6}, {7, 8}}},
            {{{19, 22}, {43, 50}}},
            Algorithms::MultiplicationAlgorithmType::BRUTE_FORCE}, // 2x2 * 2x2
                                                                   // = 2x2
        MatrixMultiplicationParams<int>{
            {{{1}, {2}, {3}}},
            {{{4, 5, 6}}},
            {{{4, 5, 6}, {8, 10, 12}, {12, 15, 18}}},
            Algorithms::MultiplicationAlgorithmType::BRUTE_FORCE}, // 3x1 * 1x3
                                                                   // = 3x3
        MatrixMultiplicationParams<int>{
            {{{1, 2}, {3, 4}}},
            {{{1, 0}, {0, 1}}},
            {{{1, 2}, {3, 4}}},
            Algorithms::MultiplicationAlgorithmType::BRUTE_FORCE}, // 2x2 * I2 =
                                                                   // 2x2
        MatrixMultiplicationParams<int>{
            {{{1, 2}, {3, 4}}},
            {{{0, 0}, {0, 0}}},
            {{{0, 0}, {0, 0}}},
            Algorithms::MultiplicationAlgorithmType::BRUTE_FORCE}
        // 2x2 * 0 = 2x2(0)
        ));