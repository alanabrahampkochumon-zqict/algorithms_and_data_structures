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
    std::size_t _rows = 2;
    std::size_t _cols = 2;
    std::size_t _rowBlock = 0;
    std::size_t _colBlock = 1;
    std::size_t _stride = 3;
    bool _bitCeil = true;
};
/** @brief Test fixture for @ref datastructures::ReadOnlyMatrixView initialization, parameterized by @ref SupportedTypes */
TYPED_TEST_SUITE(ReadOnlyMatrixViewInitializationTests, SupportedTypes);


template <typename T>
struct ReadOnlyMatrixAccessorParams
{
    datastructures::ReadOnlyMatrixView<T> matrixView;
    std::size_t row;
    std::size_t col;
    T expectedValue;
};
/** @brief Test fixture for @ref datastructures::ReadOnlyMatrixView accessor, parameterized by @ref MatrixAccessorParams */
class ReadOnlyMatrixViewAccessorTests: public ::testing::TestWithParam<ReadOnlyMatrixAccessorParams<int>>
{};


template <typename T>
struct MatrixSubviewParams
{
    datastructures::ReadOnlyMatrixView<T> matrixView, expectedSubmatrixView;
    std::size_t rowBlock, colBlock, rowBlockSize, colBlockSize;
};
/** @brief Test fixture for @ref datastructures::ReadOnlyMatrixView subview tests, parameterized by @ref MatrixSubviewParams */
class ReadOnlyMatrixSubviewTests: public ::testing::TestWithParam<MatrixSubviewParams<int>>
{};



/**
 * @addtogroup T_RO_MatView_Init
 * @{
 */

/**
 * @test Verify that @ref datastructures::ReadOnlyMatrixView parameterized constructor initializes member variables
 *       with the passed-in arguments.
 */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, InitializesToCorrectValues)
{
    // When matrix view is initialized with default values.
    const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size, this->_rows, this->_cols,
                                                             this->_rowBlock, this->_colBlock, this->_stride,
                                                             this->_bitCeil);

    // Then, it gets initialized with the passed in values.
    ASSERT_EQ(this->_dataPtr, view.m_Data);
    ASSERT_EQ(this->_size, view.m_Size);
    ASSERT_EQ(this->_rows, view.m_ViewRows);
    ASSERT_EQ(this->_cols, view.m_ViewColumns);
    ASSERT_EQ(this->_stride, view.m_Stride);
    ASSERT_EQ(this->_rowBlock, view.m_RowBlock);
    ASSERT_EQ(this->_colBlock, view.m_ColumnBlock);
    ASSERT_EQ(this->_bitCeil, view.m_BitCeil);
}


/** 
 * @test Verify that @ref datastructures::ReadOnlyMatrixView parameterized constructor sets 
 *       m_BitCeil to false by default.
 */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, BitCeilIsFalseByDefault)
{
    // When matrix view is initialized without bitCeil
    const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size, this->_rows, this->_cols,
                                                             this->_rowBlock, this->_colBlock, this->_stride);

    // Then, it gets initialized with the passed in values with bit ceil having default value of false
    ASSERT_EQ(this->_dataPtr, view.m_Data);
    ASSERT_EQ(this->_size, view.m_Size);
    ASSERT_EQ(this->_rows, view.m_ViewRows);
    ASSERT_EQ(this->_cols, view.m_ViewColumns);
    ASSERT_EQ(this->_stride, view.m_Stride);
    ASSERT_EQ(this->_rowBlock, view.m_RowBlock);
    ASSERT_EQ(this->_colBlock, view.m_ColumnBlock);
    ASSERT_FALSE(view.m_BitCeil);
}


/**
 * @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with view rows of 0 
 *       throws `std::out_of_range`.
 */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, ZeroViewRowThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size, 0,
                                                                          this->_cols, this->_rowBlock, this->_colBlock,
                                                                          this->_stride, true),
                 std::out_of_range);
}


/** 
 * @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with view columns of 0 
 *       throws `std::out_of_range`.
 */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, ZeroViewColumnThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size, this->_rows,
                                                                          0, this->_rowBlock, this->_colBlock,
                                                                          this->_stride, true),
                 std::out_of_range);
}


/** 
 * @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with a stride of 0 
 *       throws `std::out_of_range`.
 */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, ZeroStrideThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(
                     this->_data.data(), this->_size, this->_rows, this->_cols, this->_rowBlock, this->_colBlock, 0, true),
                 std::out_of_range);
}


/**
 * @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with a stride greater than size of matrix
 *       throws `std::out_of_range`.
 */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, StrideGreaterThanSizeThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size, this->_rows,
                                                                          this->_cols, this->_rowBlock, this->_colBlock,
                                                                          this->_size + 1, true),
                 std::out_of_range);
}


/** @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with a size of 0 throws `std::out_of_range`. */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, ZeroSizeThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), 0, this->_rows,
                                                                          this->_cols, this->_rowBlock, this->_colBlock,
                                                                          this->_stride, true),
                 std::out_of_range);
}


/**
 * @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with a row size larger than maximum support
 *       value (nearest power of 2) throws `std::out_of_range`.
 */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, InvalidRowThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size,
                                                                          this->_rows + 10, this->_cols, this->_rowBlock,
                                                                          this->_colBlock, this->_stride, true),
                 std::out_of_range);
}


/**
 * @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with a row size larger than maximum support
 *       value (nearest power of 2) throws `std::out_of_range`.
 */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, InvalidColumnThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size, this->_rows,
                                                                          this->_cols + 10, this->_rowBlock,
                                                                          this->_colBlock, this->_stride, true),
                 std::out_of_range);
}


/**
 * @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with a row block larger than row size
 *       (nearest power of 2) throws `std::out_of_range`.
 */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, InvalidRowOffsetThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size, this->_rows,
                                                                          this->_cols, this->_rows + 1, this->_colBlock,
                                                                          this->_stride, true),
                 std::out_of_range);
}


/**
 * @test Verify that initializing @ref datastructures::ReadOnlyMatrixView with a column block larger than column size
 *       (nearest power of 2) throws `std::out_of_range`.
 */
TYPED_TEST(ReadOnlyMatrixViewInitializationTests, InvalidColumnOffsetThrowsError)
{
    EXPECT_THROW(const datastructures::ReadOnlyMatrixView<TypeParam> view(this->_data.data(), this->_size, this->_rows,
                                                                          this->_cols, this->_rowBlock, this->_cols + 1,
                                                                          this->_stride, true),
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

static const std::vector DATA1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
const datastructures::ReadOnlyMatrixView MAT_VIEW1_00 = { DATA1.data(), DATA1.size(), 2, 2, 0, 0, 3, true };
const datastructures::ReadOnlyMatrixView MAT_VIEW1_01 = { DATA1.data(), DATA1.size(), 2, 2, 0, 1, 3, true };
const datastructures::ReadOnlyMatrixView MAT_VIEW1_10 = { DATA1.data(), DATA1.size(), 2, 2, 1, 0, 3, true };
const datastructures::ReadOnlyMatrixView MAT_VIEW1_11 = { DATA1.data(), DATA1.size(), 2, 2, 1, 1, 3, true };

static const std::vector DATA2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
const datastructures::ReadOnlyMatrixView MAT_VIEW2_00 = { DATA2.data(), DATA2.size(), 2, 2, 0, 0, 4, true };
const datastructures::ReadOnlyMatrixView MAT_VIEW2_01 = { DATA2.data(), DATA2.size(), 2, 2, 0, 1, 4, true };
const datastructures::ReadOnlyMatrixView MAT_VIEW2_10 = { DATA2.data(), DATA2.size(), 2, 2, 1, 0, 4, true };
const datastructures::ReadOnlyMatrixView MAT_VIEW2_11 = { DATA2.data(), DATA2.size(), 2, 2, 1, 1, 4, true };

INSTANTIATE_TEST_SUITE_P(
    MatrixAccessorTestSuite, ReadOnlyMatrixViewAccessorTests,
    ::testing::Values(
        ReadOnlyMatrixAccessorParams{ MAT_VIEW1_00, 0, 0, 1 }, ReadOnlyMatrixAccessorParams{ MAT_VIEW1_00, 0, 1, 2 },
        ReadOnlyMatrixAccessorParams{ MAT_VIEW1_00, 1, 0, 4 }, ReadOnlyMatrixAccessorParams{ MAT_VIEW1_00, 1, 1, 5 },

        ReadOnlyMatrixAccessorParams{ MAT_VIEW1_01, 0, 0, 3 }, ReadOnlyMatrixAccessorParams{ MAT_VIEW1_01, 0, 1, 0 },
        ReadOnlyMatrixAccessorParams{ MAT_VIEW1_01, 1, 0, 6 }, ReadOnlyMatrixAccessorParams{ MAT_VIEW1_01, 1, 1, 0 },

        ReadOnlyMatrixAccessorParams{ MAT_VIEW1_10, 0, 0, 7 }, ReadOnlyMatrixAccessorParams{ MAT_VIEW1_10, 0, 1, 8 },
        ReadOnlyMatrixAccessorParams{ MAT_VIEW1_10, 1, 0, 0 }, ReadOnlyMatrixAccessorParams{ MAT_VIEW1_10, 1, 1, 0 },

        ReadOnlyMatrixAccessorParams{ MAT_VIEW1_11, 0, 0, 9 }, ReadOnlyMatrixAccessorParams{ MAT_VIEW1_11, 0, 1, 0 },
        ReadOnlyMatrixAccessorParams{ MAT_VIEW1_11, 1, 0, 0 }, ReadOnlyMatrixAccessorParams{ MAT_VIEW1_11, 1, 1, 0 },

        ReadOnlyMatrixAccessorParams{ MAT_VIEW2_00, 0, 0, 1 }, ReadOnlyMatrixAccessorParams{ MAT_VIEW2_00, 0, 1, 2 },
        ReadOnlyMatrixAccessorParams{ MAT_VIEW2_00, 1, 0, 5 }, ReadOnlyMatrixAccessorParams{ MAT_VIEW2_00, 1, 1, 6 },

        ReadOnlyMatrixAccessorParams{ MAT_VIEW2_01, 0, 0, 3 }, ReadOnlyMatrixAccessorParams{ MAT_VIEW2_01, 0, 1, 4 },
        ReadOnlyMatrixAccessorParams{ MAT_VIEW2_01, 1, 0, 7 }, ReadOnlyMatrixAccessorParams{ MAT_VIEW2_01, 1, 1, 8 },

        ReadOnlyMatrixAccessorParams{ MAT_VIEW2_10, 0, 0, 9 }, ReadOnlyMatrixAccessorParams{ MAT_VIEW2_10, 0, 1, 10 },
        ReadOnlyMatrixAccessorParams{ MAT_VIEW2_10, 1, 0, 13 }, ReadOnlyMatrixAccessorParams{ MAT_VIEW2_10, 1, 1, 14 },

        ReadOnlyMatrixAccessorParams{ MAT_VIEW2_11, 0, 0, 11 }, ReadOnlyMatrixAccessorParams{ MAT_VIEW2_11, 0, 1, 12 },
        ReadOnlyMatrixAccessorParams{ MAT_VIEW2_11, 1, 0, 15 }, ReadOnlyMatrixAccessorParams{ MAT_VIEW2_11, 1, 1, 16 }));


/**
 * @test Verify that @ref datastructures::ReadOnlyMatrixView accessed at (rowSize, colSize) 
 *       throws `std::out_of_range`.
 */
TEST(ReadOnlyMatrixViewAccessorTests, OutOfBoundsSubindexAccessThrowsRuntimeException)
{
    EXPECT_THROW(MAT_VIEW1_00(2, 2), std::out_of_range);
}

/** 
 * @test Verify that @ref datastructures::ReadOnlyMatrixView configured with no bitCeil, when accessed at index out of
 *       bounds of the original matrix, throws `std::out_of_range`.
 */
TEST(ReadOnlyMatrixViewAccessorTests, WithoutBitCeil_OutOfBoundsAccessThrowsRuntimeException)
{
    // View of 3x3 matrix into the lower-end quadrant
    const datastructures::ReadOnlyMatrixView matView = { DATA1.data(), 9, 2, 2, 1, 1, 3, false };
    EXPECT_THROW(matView(1, 1), std::out_of_range);
}

/** @} */
