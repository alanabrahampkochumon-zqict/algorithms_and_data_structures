#include <gtest/gtest.h>

#include <concepts>

#include <MatrixMultiplication.h>

template<typename T>
	requires std::integral<T> || std::floating_point<T>
struct TestDataParam
{
	std::initializer_list<std::initializer_list<T>> inputData;
	std::size_t expectedRows;
	std::size_t expectedCols;
	std::vector<T> expectedData;
};

class MatrixInitializationTestFixture : public ::testing::TestWithParam<TestDataParam<int>> { };

TEST_P(MatrixInitializationTestFixture, InitializesToCorrectValues)
{
	// Given, some raw input numbers
	const auto& [inputData, expectedRows, expectedCols, expectedData] = GetParam();

	// When initialized as matrix
	Algorithms::Matrix mat(inputData);

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
					EXPECT_DOUBLE_EQ(expectedData[i * expectedCols + j], mat.m_Data[i * expectedRows + j]);
				else
					EXPECT_FLOAT_EQ(static_cast<float>(expectedData[i * expectedCols + j]), static_cast<float>(mat.m_Data[i * expectedRows + j]));
			}
		}
	}
	else
		EXPECT_EQ(mat.m_Data, expectedData);
}

INSTANTIATE_TEST_SUITE_P(
	MatrixInitializationTest,
	MatrixInitializationTestFixture,
	::testing::Values(
		TestDataParam(
			{ {1, 2}, {3, 4} },
			2,
			2,
			{ 1, 2, 3, 4 }
		),
		TestDataParam(
			{ {1, 2}, {3, 4, 5} },
			2,
			3,
			{ 1, 2, 0, 3, 4, 5 }
		),
		TestDataParam(
			{ {1, 2, 3}, {4, 5} },
			2,
			3,
			{ 1, 2, 3, 4, 5, 0 }
		),
		TestDataParam(
			{ {1}, {2}, {3} },
			3,
			1,
			{ 1, 2, 3 }
		),
		TestDataParam(
			{ {1, 2},{}, { 3, 4 } },
			3,
			2,
			{ 1, 2, 0, 0, 3, 4 }
		)
	)
);

TEST(MatrixInitializationTest, RowColCountInitailizesIdentityMatrix)
{
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
			EXPECT_EQ(static_cast<int>(i == j), mat.m_Data[i * cols + j]);
}

TEST(MatrixAccess, ElementsCanBeAccessedAsRowColumn)
{
	// Given a matrix is created with rows and columns
	constexpr int rows = 5;
	constexpr int cols = 7;
	const Algorithms::Matrix<int> mat(rows, cols);

	// Then, the matrix can be access with (row, col)
	for (std::size_t i = 0; i < rows; ++i)
		for (std::size_t j = 0; j < cols; ++j)
			EXPECT_EQ(static_cast<int>(i == j), mat(i, j));
}


TEST(MatrixAccess, AccessAtSizeThrowsError)
{
	// Given a matrix is created with rows and columns
	constexpr int rows = 5;
	constexpr int cols = 7;
	const Algorithms::Matrix<int> mat(rows, cols);

	// When accessed at rowsize, colsize
	// Then, it throws runtime error
	EXPECT_THROW(mat(rows, cols), std::runtime_error);
}


TEST(MatrixAccess, InvalidIndexThrowsError)
{
	// Given a matrix is created with rows and columns
	constexpr int rows = 5;
	constexpr int cols = 7;
	const Algorithms::Matrix<int> mat(rows, cols);

	// When accessed at invalid index
	// Then, it throws runtime error
	EXPECT_THROW(mat(rows + 10, cols + 10), std::runtime_error);
}



TEST(MatrixMutation, ElementsCanBeMutatedAtRowColumn)
{
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
			EXPECT_EQ(i == j ? 50: 0, mat(i, j));
}


TEST(MatrixMutation, AtSizeThrowsError)
{
	// Given a matrix is created with rows and columns
	constexpr int rows = 5;
	constexpr int cols = 7;
	Algorithms::Matrix<int> mat(rows, cols);

	// When mutated at rowsize, colsize
	// Then, it throws runtime error
	EXPECT_THROW(mat(rows, cols) = 5, std::runtime_error);
}


TEST(MatrixMutation, InvalidIndexThrowsError)
{
	// Given a matrix is created with rows and columns
	constexpr int rows = 5;
	constexpr int cols = 7;
	Algorithms::Matrix<int> mat(rows, cols);

	// When mutated at invalid index
	// Then, it throws runtime error
	EXPECT_THROW(mat(rows + 10, cols + 10) = 6, std::runtime_error);
}