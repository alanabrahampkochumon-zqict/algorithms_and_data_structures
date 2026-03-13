/**
 * @file MatrixViewTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 13, 2026
 *
 * @brief Verifies the initialization, access, and mutation of @ref MatrixView. 
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Matrix.h"


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
TYPED_TEST_SUITE(MatrixViewInitializationTests, SupportedTypes);


template <typename T>
struct MatrixAccessorParams
{
    datastructures::MatrixView<T> matrixView;
    std::size_t row;
    std::size_t col;
    T expectedValue;
};
class MatrixAccessorTests: public ::testing::TestWithParam<MatrixAccessorParams<int>>
{
};
template <typename T>
std::ostream& operator<<(std::ostream& os, MatrixAccessorParams<T> params)
{
    os << "MatrixView: " << params.matrixView << "\n(Rows, Columns): (" << params.row << ", " << params.col
       << "). Expected Value: " << params.expectedValue << "\n";
    return os;
}



/**************************************
 *                                    *
 *        INITIALIZATION TESTS        *
 *                                    *
 **************************************/

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
    ASSERT_EQ(this->rowOffset, view.m_RowOffset);
    ASSERT_EQ(this->colOffset, view.m_ColumnOffset);
    ASSERT_EQ(this->calcOffset, view.m_Offset);
    ASSERT_EQ(this->bitCeil, view.m_BitCeil);
}

TYPED_TEST(MatrixViewInitializationTests, BitCeilIsFalseByDefault)
{
    // When matrix view is initialized without bitCeil
    const datastructures::MatrixView<TypeParam> view(this->data.data(), this->size, this->rows, this->cols,
                                                     this->rowOffset, this->colOffset, this->stride, false);

    // Then, it gets initialized with the passed in values with bit ceil having default value of false
    ASSERT_EQ(this->data_ptr, view.m_Data);
    ASSERT_EQ(this->size, view.m_Size);
    ASSERT_EQ(this->rows, view.m_ViewRows);
    ASSERT_EQ(this->cols, view.m_ViewColumns);
    ASSERT_EQ(this->stride, view.m_Stride);
    ASSERT_EQ(this->rowOffset, view.m_RowOffset);
    ASSERT_EQ(this->colOffset, view.m_ColumnOffset);
    ASSERT_EQ(this->calcOffset, view.m_Offset);
    ASSERT_FALSE(view.m_BitCeil);
}


/**************************************
 *                                    *
 *            ACCESSOR TESTS          *
 *                                    *
 **************************************/
// TEST_P(MatrixAccessorTests, AccessorReturnsCorrectValue)
//{
//     // Given a matrix view
//     const auto& [matrixView, row, col, expected] = GetParam();
//
//     // When a value is accessed
//     const auto value = matrixView(row, col);
//
//     // Then, the value is as expected
//     EXPECT_EQ(expected, value) << "Expected: " << expected << ". Got: " << value;
// }

//std::vector data1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//const datastructures::MatrixView matView1_0 = { data1.data(), data1.size(), 2, 2, 0, 3, true };
//const datastructures::MatrixView matView1_1 = { data1.data(), data1.size(), 2, 2, 1, 3, true };
//const datastructures::MatrixView matView1_2 = { data1.data(), data1.size(), 2, 2, 2, 3, true };
//const datastructures::MatrixView matView1_3 = { data1.data(), data1.size(), 2, 2, 3, 3, true };
//
//std::vector data2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
//const datastructures::MatrixView matView2_0 = { data2.data(), data2.size(), 2, 2, 0, 4, true };
//const datastructures::MatrixView matView2_1 = { data2.data(), data2.size(), 2, 2, 1, 4, true };
//const datastructures::MatrixView matView2_2 = { data2.data(), data2.size(), 2, 2, 2, 4, true };
//const datastructures::MatrixView matView2_3 = { data2.data(), data2.size(), 2, 2, 3, 4, true };

// INSTANTIATE_TEST_SUITE_P(
//     MatrixAccessorTestSuite, MatrixAccessorTests,
//     ::testing::Values(MatrixAccessorParams{ matView1_0, 0, 0, 1 }, MatrixAccessorParams{ matView1_0, 0, 1, 2 },
//                       MatrixAccessorParams{ matView1_0, 1, 0, 4 }, MatrixAccessorParams{ matView1_0, 1, 1, 5 },
//
//                       MatrixAccessorParams{ matView1_1, 0, 0, 3 }, MatrixAccessorParams{ matView1_1, 0, 1, 0 },
//                       MatrixAccessorParams{ matView1_1, 1, 0, 6 }, MatrixAccessorParams{ matView1_1, 1, 1, 0 },
//
//                       MatrixAccessorParams{ matView1_2, 0, 0, 7 }, MatrixAccessorParams{ matView1_2, 0, 1, 8 },
//                       MatrixAccessorParams{ matView1_2, 1, 0, 0 }, MatrixAccessorParams{ matView1_2, 1, 1, 0 },
//
//                       MatrixAccessorParams{ matView1_3, 0, 0, 9 }, MatrixAccessorParams{ matView1_3, 0, 1, 0 },
//                       MatrixAccessorParams{ matView1_3, 1, 0, 0 }, MatrixAccessorParams{ matView1_3, 1, 1, 0 },
//
//                       MatrixAccessorParams{ matView2_0, 0, 0, 1 }, MatrixAccessorParams{ matView2_0, 0, 1, 2 },
//                       MatrixAccessorParams{ matView2_0, 1, 0, 5 }, MatrixAccessorParams{ matView2_0, 1, 1, 6 },
//
//                       MatrixAccessorParams{ matView2_1, 0, 0, 3 }, MatrixAccessorParams{ matView2_1, 0, 1, 4 },
//                       MatrixAccessorParams{ matView2_1, 1, 0, 7 }, MatrixAccessorParams{ matView2_1, 1, 1, 8 },
//
//                       MatrixAccessorParams{ matView2_2, 0, 0, 9 }, MatrixAccessorParams{ matView2_2, 0, 1, 10 },
//                       MatrixAccessorParams{ matView2_2, 1, 0, 13 }, MatrixAccessorParams{ matView2_2, 1, 1, 14 },
//
//                       MatrixAccessorParams{ matView2_3, 0, 0, 11 }, MatrixAccessorParams{ matView2_3, 0, 1, 12 },
//                       MatrixAccessorParams{ matView2_3, 1, 0, 15 }, MatrixAccessorParams{ matView2_3, 1, 1, 16 }));

// TEST(MatrixAccessorTests, OutOfBoundsSubindexAccessThrowsRuntimeException)
//{
//     // Given a matrix view
//     // When accessed at out of bounds index
//     // Then it throws a runtime_error
//     EXPECT_THROW(matView1_0(2, 2), std::runtime_error);
// }
//
// TEST(MatrixAccessorTests, WithoutBitCeil_OutOfBoundsAccessThrowsRuntimeException)
//{
//     // Given a matrix view without bit ceil
//     const datastructures::MatrixView matView = { data1.data(), 9, 2, 2, 6, 3, false };
//     // When accessed at out of bounds index
//     // Then it throws a runtime_error
//     EXPECT_THROW(matView1_0(1, 1), std::runtime_error);
// }
