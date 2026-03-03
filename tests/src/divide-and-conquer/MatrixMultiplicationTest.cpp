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
					EXPECT_FLOAT_EQ(expectedData[i * expectedCols + j], mat.m_Data[i * expectedRows + j]);
			}
		}
	}
	else
		EXPECT_EQ(mat.m_Data, expectedData);
}

INSTANTIATE_TEST_CASE_P(
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