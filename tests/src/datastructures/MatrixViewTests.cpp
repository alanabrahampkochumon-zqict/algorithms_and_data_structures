/**
 * @file MatrixViewTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 13, 2026
 *
 * @brief Verifies the initialization, access, and mutation of @ref datastructures::MatrixView.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <MatrixView.h>


/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

using SupportedTypes = ::testing::Types<unsigned char, short, int, float, double, unsigned long long>;

template <typename T>
class MatrixViewInitializationTests: public ::testing::Test
{
    protected:
    std::vector<T> data{ T(1), T(2), T(3), T(4), T(5), T(6) };
    T* data_ptr = data.data();
    std::size_t size = data.size();
    std::size_t rows = 2;
    std::size_t cols = 2;
    std::size_t rowOffset = 0;
    std::size_t colOffset = 1;
    std::size_t calcOffset = 1;
    std::size_t stride = 3;
    bool bitCeil = true;
};
/** @brief Test fixture for @ref MatrixView initialization, parameterized by @ref SupportedTypes */
TYPED_TEST_SUITE(MatrixViewInitializationTests, SupportedTypes);


template <typename T>
struct MatrixAccessorParams
{
    datastructures::MatrixView<T> matrixView;
    std::size_t row;
    std::size_t col;
    T expectedValue;
};
/** @brief Test fixture for @ref MatrixView accessor, parameterized by @ref MatrixAccessorParams */
class MatrixViewAccessorTests: public ::testing::TestWithParam<MatrixAccessorParams<int>>
{};


template <typename T>
struct MatrixMutationParams
{
    using value_type = T;
    datastructures::MatrixView<T> matrixView;
    std::size_t row;
    std::size_t col;
};
/** @brief Test fixture for @ref MatrixView mutation, parameterized by @ref MatrixMutationParams */
class MatrixViewMutationTests: public ::testing::TestWithParam<MatrixMutationParams<int>>
{};


template <typename T>
std::ostream& operator<<(std::ostream& os, MatrixAccessorParams<T> params)
{
    os << "MatrixView: " << params.matrixView << "\n(Rows, Columns): (" << params.row << ", " << params.col
       << "). Expected Value: " << params.expectedValue << "\n";
    return os;
}


/**
 * @addtogroup MatView_Init
 * @{
 */

/** @test Verify that @ref datastructures::MatrixView initialization initializes member variables with the passed-in
 * arguments. */
TYPED_TEST(MatrixViewInitializationTests, InitializesToCorrectValues)
{
    // When matrix view is initialized with default values.
    const datastructures::MatrixView<TypeParam> view(this->data.data(), this->size, this->rows, this->cols,
                                                     this->rowOffset, this->colOffset, this->stride, this->bitCeil);

    // Then, it gets initialized with the passed in values.
    ASSERT_EQ(this->data_ptr, view.m_Data);
    ASSERT_EQ(this->size, view.m_Size);
    ASSERT_EQ(this->rows, view.m_ViewRows);
    ASSERT_EQ(this->cols, view.m_ViewColumns);
    ASSERT_EQ(this->stride, view.m_Stride);
    ASSERT_EQ(this->rowOffset, view.m_RowBlock);
    ASSERT_EQ(this->colOffset, view.m_ColumnBlock);
    ASSERT_EQ(this->calcOffset, view.m_Offset);
    ASSERT_EQ(this->bitCeil, view.m_BitCeil);
}

/** @test Verify that @ref datastructures::MatrixView initialization sets m_BitCeil to false by default. */
TYPED_TEST(MatrixViewInitializationTests, BitCeilIsFalseByDefault)
{
    // When matrix view is initialized without bitCeil
    const datastructures::MatrixView<TypeParam> view(this->data.data(), this->size, this->rows, this->cols,
                                                     this->rowOffset, this->colOffset, this->stride);

    // Then, it gets initialized with the passed in values with bit ceil having default value of false
    ASSERT_EQ(this->data_ptr, view.m_Data);
    ASSERT_EQ(this->size, view.m_Size);
    ASSERT_EQ(this->rows, view.m_ViewRows);
    ASSERT_EQ(this->cols, view.m_ViewColumns);
    ASSERT_EQ(this->stride, view.m_Stride);
    ASSERT_EQ(this->rowOffset, view.m_RowBlock);
    ASSERT_EQ(this->colOffset, view.m_ColumnBlock);
    ASSERT_EQ(this->calcOffset, view.m_Offset);
    ASSERT_FALSE(view.m_BitCeil);
}

/** @test Verify that initializing @ref datastructures::MatrixView with view rows of 0 throw std::out_of_range. */
TYPED_TEST(MatrixViewInitializationTests, ZeroViewRowThrowsError)
{
    EXPECT_THROW(const datastructures::MatrixView<TypeParam> view(this->data.data(), this->size, 0, this->cols,
                                                                  this->rowOffset, this->colOffset, this->stride, true),
                 std::out_of_range);
}

/** @test Verify that initializing @ref datastructures::MatrixView with view columns of 0 throw std::out_of_range. */
TYPED_TEST(MatrixViewInitializationTests, ZeroViewColumnThrowsError)
{
    EXPECT_THROW(const datastructures::MatrixView<TypeParam> view(this->data.data(), this->size, this->rows, 0,
                                                                  this->rowOffset, this->colOffset, this->stride, true),
                 std::out_of_range);
}

/** @test Verify that initializing @ref datastructures::MatrixView with a stride of 0 throw std::out_of_range. */
TYPED_TEST(MatrixViewInitializationTests, ZeroStrideThrowsError)
{
    EXPECT_THROW(const datastructures::MatrixView<TypeParam> view(this->data.data(), this->size, this->rows, this->cols,
                                                                  this->rowOffset, this->colOffset, 0, true),
                 std::out_of_range);
}

/**
 * @test Verify that initializing @ref datastructures::MatrixView with a stride greater than size of matrix throw
 *       std::out_of_range.
 */
TYPED_TEST(MatrixViewInitializationTests, StrideGreaterThanSizeThrowsError)
{
    EXPECT_THROW(const datastructures::MatrixView<TypeParam> view(this->data.data(), this->size, this->rows, this->cols,
                                                                  this->rowOffset, this->colOffset, this->size + 1,
                                                                  true),
                 std::out_of_range);
}

/** @test Verify that initializing @ref datastructures::MatrixView with a size of 0 throws std::out_of_range. */
TYPED_TEST(MatrixViewInitializationTests, ZeroSizeThrowsError)
{
    EXPECT_THROW(const datastructures::MatrixView<TypeParam> view(this->data.data(), 0, this->rows, this->cols,
                                                                  this->rowOffset, this->colOffset, this->stride, true),
                 std::out_of_range);
}

/**
 * @test Verify that initializing @ref datastructures::MatrixView with a row size larger than maximum support value
 *       (nearest power of 2) throws std::out_of_range.
 */
TYPED_TEST(MatrixViewInitializationTests, InvalidRowThrowsError)
{
    EXPECT_THROW(const datastructures::MatrixView<TypeParam> view(this->data.data(), this->size, this->rows + 10,
                                                                  this->cols, this->rowOffset, this->colOffset,
                                                                  this->stride, true),
                 std::out_of_range);
}

/**
 * @test Verify that initializing @ref datastructures::MatrixView with a row size larger than maximum support value
 *       (nearest power of 2) throws std::out_of_range.
 */
TYPED_TEST(MatrixViewInitializationTests, InvalidColumnThrowsError)
{
    EXPECT_THROW(const datastructures::MatrixView<TypeParam> view(this->data.data(), this->size, this->rows,
                                                                  this->cols + 10, this->rowOffset, this->colOffset,
                                                                  this->stride, true),
                 std::out_of_range);
}

/**
 * @test Verify that initializing @ref datastructures::MatrixView with a row block larger than row size
 *       (nearest power of 2) throws std::out_of_range.
 */
TYPED_TEST(MatrixViewInitializationTests, InvalidRowOffsetThrowsError)
{
    EXPECT_THROW(const datastructures::MatrixView<TypeParam> view(this->data.data(), this->size, this->rows, this->cols,
                                                                  this->rows + 1, this->colOffset, this->stride, true),
                 std::out_of_range);
}

/**
 * @test Verify that initializing @ref datastructures::MatrixView with a column block larger than column size
 *       (nearest power of 2) throws std::out_of_range.
 */
TYPED_TEST(MatrixViewInitializationTests, InvalidColumnOffsetThrowsError)
{
    EXPECT_THROW(const datastructures::MatrixView<TypeParam> view(this->data.data(), this->size, this->rows, this->cols,
                                                                  this->rowOffset, this->cols + 1, this->stride, true),
                 std::out_of_range);
}

/** @} */




/**
 * @addtogroup MatView_Access
 * @{
 */

/** @test Verify @ref MatrixView accessor return correct value. */
TEST_P(MatrixViewAccessorTests, AccessorReturnsCorrectValue)
{
    const auto& [matrixView, row, col, expected] = GetParam();

    const auto value = matrixView(row, col);

    EXPECT_EQ(expected, value);
}

std::vector data1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
const datastructures::MatrixView matView1_00 = { data1.data(), data1.size(), 2, 2, 0, 0, 3, true };
const datastructures::MatrixView matView1_01 = { data1.data(), data1.size(), 2, 2, 0, 1, 3, true };
const datastructures::MatrixView matView1_10 = { data1.data(), data1.size(), 2, 2, 1, 0, 3, true };
const datastructures::MatrixView matView1_11 = { data1.data(), data1.size(), 2, 2, 1, 1, 3, true };

std::vector data2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
const datastructures::MatrixView matView2_00 = { data2.data(), data2.size(), 2, 2, 0, 0, 4, true };
const datastructures::MatrixView matView2_01 = { data2.data(), data2.size(), 2, 2, 0, 1, 4, true };
const datastructures::MatrixView matView2_10 = { data2.data(), data2.size(), 2, 2, 1, 0, 4, true };
const datastructures::MatrixView matView2_3 = { data2.data(), data2.size(), 2, 2, 1, 1, 4, true };

INSTANTIATE_TEST_SUITE_P(
    MatrixAccessorTestSuite, MatrixViewAccessorTests,
    ::testing::Values(MatrixAccessorParams{ matView1_00, 0, 0, 1 }, MatrixAccessorParams{ matView1_00, 0, 1, 2 },
                      MatrixAccessorParams{ matView1_00, 1, 0, 4 }, MatrixAccessorParams{ matView1_00, 1, 1, 5 },

                      MatrixAccessorParams{ matView1_01, 0, 0, 3 }, MatrixAccessorParams{ matView1_01, 0, 1, 0 },
                      MatrixAccessorParams{ matView1_01, 1, 0, 6 }, MatrixAccessorParams{ matView1_01, 1, 1, 0 },

                      MatrixAccessorParams{ matView1_10, 0, 0, 7 }, MatrixAccessorParams{ matView1_10, 0, 1, 8 },
                      MatrixAccessorParams{ matView1_10, 1, 0, 0 }, MatrixAccessorParams{ matView1_10, 1, 1, 0 },

                      MatrixAccessorParams{ matView1_11, 0, 0, 9 }, MatrixAccessorParams{ matView1_11, 0, 1, 0 },
                      MatrixAccessorParams{ matView1_11, 1, 0, 0 }, MatrixAccessorParams{ matView1_11, 1, 1, 0 },

                      MatrixAccessorParams{ matView2_00, 0, 0, 1 }, MatrixAccessorParams{ matView2_00, 0, 1, 2 },
                      MatrixAccessorParams{ matView2_00, 1, 0, 5 }, MatrixAccessorParams{ matView2_00, 1, 1, 6 },

                      MatrixAccessorParams{ matView2_01, 0, 0, 3 }, MatrixAccessorParams{ matView2_01, 0, 1, 4 },
                      MatrixAccessorParams{ matView2_01, 1, 0, 7 }, MatrixAccessorParams{ matView2_01, 1, 1, 8 },

                      MatrixAccessorParams{ matView2_10, 0, 0, 9 }, MatrixAccessorParams{ matView2_10, 0, 1, 10 },
                      MatrixAccessorParams{ matView2_10, 1, 0, 13 }, MatrixAccessorParams{ matView2_10, 1, 1, 14 },

                      MatrixAccessorParams{ matView2_3, 0, 0, 11 }, MatrixAccessorParams{ matView2_3, 0, 1, 12 },
                      MatrixAccessorParams{ matView2_3, 1, 0, 15 }, MatrixAccessorParams{ matView2_3, 1, 1, 16 }));


/** @test Verify that @ref datastructures::MatrixView accessed at (rowSize, colSize) throws @ref std::out_of_range */
TEST(MatrixViewAccessorTests, OutOfBoundsSubindexAccessThrowsRuntimeException)
{
    EXPECT_THROW(matView1_00(2, 2), std::out_of_range);
}

/** @test Verify that @ref datastructures::MatrixView configured with no bitCeil, when accessed at index out of bounds
 *        of the original matrix, throws @ref std::out_of_range */
TEST(MatrixViewAccessorTests, WithoutBitCeil_OutOfBoundsAccessThrowsRuntimeException)
{
    // View of 3x3 matrix into the lower-end quadrant
    const datastructures::MatrixView matView = { data1.data(), 9, 2, 2, 1, 1, 3, false };
    EXPECT_THROW(matView(1, 1), std::out_of_range);
}

/** @} */




/**
 * @addtogroup MatView_Mutation
 * @{
 */

/** @test Verify @ref MatrixView mutator allows mutation at valid indices of parent matrix. */
TEST_P(MatrixViewMutationTests, AllowsMutationAtParentIndices)
{
    constexpr ParamType::value_type newValue = 123456;
    const auto& [matrixView, row, col] = GetParam();

    auto matView = matrixView; // Create a new matrix view for mutation
    
    matView(row, col) = newValue;
    const auto value = matrixView(row, col);

    EXPECT_EQ(newValue, value);
}

INSTANTIATE_TEST_SUITE_P(
    MatrixMutationTestSuite, MatrixViewMutationTests,
    ::testing::Values(MatrixMutationParams{ matView1_00, 0, 0}, MatrixMutationParams{ matView1_00, 0, 1, },
                      MatrixMutationParams{ matView1_00, 1, 0}, MatrixMutationParams{ matView1_00, 1, 1, },

                      MatrixMutationParams{ matView1_01, 0, 0},// MatrixMutationParams{ matView1_01, 0, 1, },
                      MatrixMutationParams{ matView1_01, 1, 0},// MatrixMutationParams{ matView1_01, 1, 1, },

                      MatrixMutationParams{ matView1_10, 0, 0}, MatrixMutationParams{ matView1_10, 0, 1, },
                      //MatrixMutationParams{ matView1_10, 1, 0}, MatrixMutationParams{ matView1_10, 1, 1, },

                      MatrixMutationParams{ matView1_11, 0, 0}, // MatrixMutationParams{ matView1_11, 0, 1, },
                      //MatrixMutationParams{ matView1_11, 1, 0}, MatrixMutationParams{ matView1_11, 1, 1, },

                      MatrixMutationParams{ matView2_00, 0, 0}, MatrixMutationParams{ matView2_00, 0, 1, },
                      MatrixMutationParams{ matView2_00, 1, 0}, MatrixMutationParams{ matView2_00, 1, 1, },

                      MatrixMutationParams{ matView2_01, 0, 0}, MatrixMutationParams{ matView2_01, 0, 1, },
                      MatrixMutationParams{ matView2_01, 1, 0}, MatrixMutationParams{ matView2_01, 1, 1, },

                      MatrixMutationParams{ matView2_10, 0, 0}, MatrixMutationParams{ matView2_10, 0, 1 },
                      MatrixMutationParams{ matView2_10, 1, 0 }, MatrixMutationParams{ matView2_10, 1, 1 },

                      MatrixMutationParams{ matView2_3, 0, 0 }, MatrixMutationParams{ matView2_3, 0, 1 },
                      MatrixMutationParams{ matView2_3, 1, 0 }, MatrixMutationParams{ matView2_3, 1, 1 }));

/** @} */