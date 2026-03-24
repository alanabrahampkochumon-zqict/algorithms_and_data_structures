/**
 * @file ReadOnlyMatrixViewTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 24, 2026
 *
 * @brief Verifies the initialization, access, and mutation of @ref datastructures::ReadOnlyMatrixView.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <ReadOnlyMatrixView.h>


/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

using SupportedTypes = ::testing::Types<unsigned char, short, int, float, double, unsigned long long>;

template <typename T>
class ReadOnlyMatrixViewInitializationTests: public ::testing::Test
{
protected:
    std::vector<T> _data{ T(1), T(2), T(3), T(4), T(5), T(6) };
    T* _dataPtr = _data.data();
    std::size_t _size = _data.size();
    std::size_t rows = 2;
    std::size_t cols = 2;
    std::size_t rowBlock = 0;
    std::size_t colBlock = 1;
    std::size_t stride = 3;
    bool bitCeil = true;
};
/** @brief Test fixture for @ref ReadOnlyMatrixView initialization, parameterized by @ref SupportedTypes */
TYPED_TEST_SUITE(ReadOnlyMatrixViewInitializationTests, SupportedTypes);


template <typename T>
struct ReadOnlyMatrixAccessorParams
{
    datastructures::ReadOnlyMatrixView<T> matrixView;
    std::size_t row;
    std::size_t col;
    T expectedValue;
};
/** @brief Test fixture for @ref ReadOnlyMatrixView accessor, parameterized by @ref MatrixAccessorParams */
class ReadOnlyMatrixViewAccessorTests: public ::testing::TestWithParam<ReadOnlyMatrixAccessorParams<int>>
{};


template <typename T>
struct MatrixMutationParams
{
    using value_type = T;
    datastructures::ReadOnlyMatrixView<T> matrixView;
    std::size_t row;
    std::size_t col;
};
/** @brief Test fixture for @ref ReadOnlyMatrixView in-bounds mutation, parameterized by @ref MatrixMutationParams */
class ReadOnlyMatrixViewMutationTests: public ::testing::TestWithParam<MatrixMutationParams<int>>
{};
/** @brief Test fixture for @ref ReadOnlyMatrixView out-of-bounds mutation, parameterized by @ref MatrixMutationParams
 */
class ReadOnlyMatrixViewMutationOutOfBoundsTests: public ::testing::TestWithParam<MatrixMutationParams<int>>
{};



template <typename T>
std::ostream& operator<<(std::ostream& os, ReadOnlyMatrixAccessorParams<T> params)
{
    os << "ReadOnlyMatrixView: " << params.matrixView << "\n(Rows, Columns): (" << params.row << ", " << params.col
       << "). Expected Value: " << params.expectedValue << "\n";
    return os;
}



/**
 * @addtogroup T_RO_MatView_Init
 * @{
 */

/** @test Verify that @ref datastructures::ReadOnlyMatrixView parameterized constructor initializes member variables
 * with the passed-in arguments. */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, InitializesToCorrectValues)
{
    // When matrix view is initialized with default values.
    const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size, this->rows, this->cols,
                                                             this->rowBlock, this->colBlock, this->stride,
                                                             this->bitCeil);

    // Then, it gets initialized with the passed in values.
    ASSERT_EQ(this->_dataPtr, view.m_Data);
    ASSERT_EQ(this->_size, view.m_Size);
    ASSERT_EQ(this->rows, view.m_ViewRows);
    ASSERT_EQ(this->cols, view.m_ViewColumns);
    ASSERT_EQ(this->stride, view.m_Stride);
    ASSERT_EQ(this->rowBlock, view.m_RowBlock);
    ASSERT_EQ(this->colBlock, view.m_ColumnBlock);
    ASSERT_EQ(this->bitCeil, view.m_BitCeil);
}

/** @test Verify that @ref datastructures::ReadOnlyMatrixView parameterized constructor sets m_BitCeil to false by
 * default. */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, BitCeilIsFalseByDefault)
{
    // When matrix view is initialized without bitCeil
    const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size, this->rows, this->cols,
                                                             this->rowBlock, this->colBlock, this->stride);

    // Then, it gets initialized with the passed in values with bit ceil having default value of false
    ASSERT_EQ(this->_dataPtr, view.m_Data);
    ASSERT_EQ(this->_size, view.m_Size);
    ASSERT_EQ(this->rows, view.m_ViewRows);
    ASSERT_EQ(this->cols, view.m_ViewColumns);
    ASSERT_EQ(this->stride, view.m_Stride);
    ASSERT_EQ(this->rowBlock, view.m_RowBlock);
    ASSERT_EQ(this->colBlock, view.m_ColumnBlock);
    ASSERT_FALSE(view.m_BitCeil);
}

/** @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with view rows of 0 throw std::out_of_range.
 */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, ZeroViewRowThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size, 0,
                                                                          this->cols, this->rowBlock, this->colBlock,
                                                                          this->stride, true),
                 std::out_of_range);
}

/** @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with view columns of 0 throw
 * std::out_of_range. */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, ZeroViewColumnThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size, this->rows,
                                                                          0, this->rowBlock, this->colBlock,
                                                                          this->stride, true),
                 std::out_of_range);
}

/** @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with a stride of 0 throw std::out_of_range.
 */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, ZeroStrideThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(
                     this->_data.data(), this->_size, this->rows, this->cols, this->rowBlock, this->colBlock, 0, true),
                 std::out_of_range);
}

/**
 * @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with a stride greater than size of matrix
 * throw std::out_of_range.
 */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, StrideGreaterThanSizeThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size, this->rows,
                                                                          this->cols, this->rowBlock, this->colBlock,
                                                                          this->_size + 1, true),
                 std::out_of_range);
}

/** @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with a size of 0 throws std::out_of_range. */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, ZeroSizeThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), 0, this->rows,
                                                                          this->cols, this->rowBlock, this->colBlock,
                                                                          this->stride, true),
                 std::out_of_range);
}

/**
 * @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with a row size larger than maximum support
 * value (nearest power of 2) throws std::out_of_range.
 */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, InvalidRowThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size,
                                                                          this->rows + 10, this->cols, this->rowBlock,
                                                                          this->colBlock, this->stride, true),
                 std::out_of_range);
}

/**
 * @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with a row size larger than maximum support
 * value (nearest power of 2) throws std::out_of_range.
 */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, InvalidColumnThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size, this->rows,
                                                                          this->cols + 10, this->rowBlock,
                                                                          this->colBlock, this->stride, true),
                 std::out_of_range);
}

/**
 * @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with a row block larger than row size
 *       (nearest power of 2) throws std::out_of_range.
 */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, InvalidRowOffsetThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size, this->rows,
                                                                          this->cols, this->rows + 1, this->colBlock,
                                                                          this->stride, true),
                 std::out_of_range);
}

/**
 * @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with a column block larger than column size
 *       (nearest power of 2) throws std::out_of_range.
 */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, InvalidColumnOffsetThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size, this->rows,
                                                                          this->cols, this->rowBlock, this->cols + 1,
                                                                          this->stride, true),
                 std::out_of_range);
}

/** @} */




/**
 * @addtogroup T_RO_MatView_Access
 * @{
 */

/** @test Verify @ref ReadOnlyMatrixView accessor return correct value. */
TEST_P(ReadOnlyMatrixViewAccessorTests, AccessorReturnsCorrectValue)
{
    const auto& [matrixView, row, col, expected] = GetParam();

    const auto value = matrixView(row, col);

    EXPECT_EQ(expected, value);
}

static std::vector g_firstData = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
datastructures::ReadOnlyMatrixView matView1_00 = { g_firstData.data(), g_firstData.size(), 2, 2, 0, 0, 3, true };
const datastructures::ReadOnlyMatrixView matView1_01 = { g_firstData.data(), g_firstData.size(), 2, 2, 0, 1, 3, true };
const datastructures::ReadOnlyMatrixView matView1_10 = { g_firstData.data(), g_firstData.size(), 2, 2, 1, 0, 3, true };
const datastructures::ReadOnlyMatrixView matView1_11 = { g_firstData.data(), g_firstData.size(), 2, 2, 1, 1, 3, true };

static std::vector data2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
const datastructures::ReadOnlyMatrixView matView2_00 = { data2.data(), data2.size(), 2, 2, 0, 0, 4, true };
const datastructures::ReadOnlyMatrixView matView2_01 = { data2.data(), data2.size(), 2, 2, 0, 1, 4, true };
const datastructures::ReadOnlyMatrixView matView2_10 = { data2.data(), data2.size(), 2, 2, 1, 0, 4, true };
const datastructures::ReadOnlyMatrixView matView2_3 = { data2.data(), data2.size(), 2, 2, 1, 1, 4, true };

INSTANTIATE_TEST_SUITE_P(
    MatrixAccessorTestSuite, ReadOnlyMatrixViewAccessorTests,
    ::testing::Values(
        ReadOnlyMatrixAccessorParams{ matView1_00, 0, 0, 1 }, ReadOnlyMatrixAccessorParams{ matView1_00, 0, 1, 2 },
        ReadOnlyMatrixAccessorParams{ matView1_00, 1, 0, 4 }, ReadOnlyMatrixAccessorParams{ matView1_00, 1, 1, 5 },

        ReadOnlyMatrixAccessorParams{ matView1_01, 0, 0, 3 }, ReadOnlyMatrixAccessorParams{ matView1_01, 0, 1, 0 },
        ReadOnlyMatrixAccessorParams{ matView1_01, 1, 0, 6 }, ReadOnlyMatrixAccessorParams{ matView1_01, 1, 1, 0 },

        ReadOnlyMatrixAccessorParams{ matView1_10, 0, 0, 7 }, ReadOnlyMatrixAccessorParams{ matView1_10, 0, 1, 8 },
        ReadOnlyMatrixAccessorParams{ matView1_10, 1, 0, 0 }, ReadOnlyMatrixAccessorParams{ matView1_10, 1, 1, 0 },

        ReadOnlyMatrixAccessorParams{ matView1_11, 0, 0, 9 }, ReadOnlyMatrixAccessorParams{ matView1_11, 0, 1, 0 },
        ReadOnlyMatrixAccessorParams{ matView1_11, 1, 0, 0 }, ReadOnlyMatrixAccessorParams{ matView1_11, 1, 1, 0 },

        ReadOnlyMatrixAccessorParams{ matView2_00, 0, 0, 1 }, ReadOnlyMatrixAccessorParams{ matView2_00, 0, 1, 2 },
        ReadOnlyMatrixAccessorParams{ matView2_00, 1, 0, 5 }, ReadOnlyMatrixAccessorParams{ matView2_00, 1, 1, 6 },

        ReadOnlyMatrixAccessorParams{ matView2_01, 0, 0, 3 }, ReadOnlyMatrixAccessorParams{ matView2_01, 0, 1, 4 },
        ReadOnlyMatrixAccessorParams{ matView2_01, 1, 0, 7 }, ReadOnlyMatrixAccessorParams{ matView2_01, 1, 1, 8 },

        ReadOnlyMatrixAccessorParams{ matView2_10, 0, 0, 9 }, ReadOnlyMatrixAccessorParams{ matView2_10, 0, 1, 10 },
        ReadOnlyMatrixAccessorParams{ matView2_10, 1, 0, 13 }, ReadOnlyMatrixAccessorParams{ matView2_10, 1, 1, 14 },

        ReadOnlyMatrixAccessorParams{ matView2_3, 0, 0, 11 }, ReadOnlyMatrixAccessorParams{ matView2_3, 0, 1, 12 },
        ReadOnlyMatrixAccessorParams{ matView2_3, 1, 0, 15 }, ReadOnlyMatrixAccessorParams{ matView2_3, 1, 1, 16 }));


/** @test Verify that @ref datastructures::ReadOnlyMatrixView accessed at (rowSize, colSize) throws @ref
 * std::out_of_range */
TEST(ReadOnlyMatrixViewAccessorTests, OutOfBoundsSubindexAccessThrowsRuntimeException)
{
    EXPECT_THROW(matView1_00(2, 2), std::out_of_range);
}

/** @test Verify that @ref datastructures::ReadOnlyMatrixView configured with no bitCeil, when accessed at index out of
 * bounds of the original matrix, throws @ref std::out_of_range */
TEST(ReadOnlyMatrixViewAccessorTests, WithoutBitCeil_OutOfBoundsAccessThrowsRuntimeException)
{
    // View of 3x3 matrix into the lower-end quadrant
    const datastructures::ReadOnlyMatrixView matView = { g_firstData.data(), 9, 2, 2, 1, 1, 3, false };
    EXPECT_THROW(matView(1, 1), std::out_of_range);
}

/** @} */
