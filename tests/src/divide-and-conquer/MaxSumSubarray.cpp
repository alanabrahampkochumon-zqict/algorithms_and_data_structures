#include <gtest/gtest.h>
#include <concepts>
#include <array>
#include <MaxSumSubarray.h>
#include <climits>

using namespace Algorithms::DivideAndConquer;


template<typename T>
	requires std::integral<T> || std::floating_point<T>
struct TestCaseData
{
	std::vector<T> input;
	std::size_t start;
	std::size_t end;
	WideType<T> sum;
};

template<typename T>
	requires std::integral<T> || std::floating_point<T>
struct AlgorithmTestParam
{
	AlgorithmType algo;
	TestCaseData<T> data;
};

template <typename T>
static std::ostream& operator<<(std::ostream& os, const AlgorithmTestParam<T>& param)
{
	os << "AlgorithmTestsParams( " << "Algorithm: " << param.algo << ", data: { sum: " << param.data.sum << ", start: " << param.data.start << ", end: " << param.data.end << " })\n";
	return os;
}


class MaxSumSubarrayIntegralTestFixture : public ::testing::TestWithParam<AlgorithmTestParam<int>> { };
class MaxSumSubarrayFloatingPointTestFixture : public ::testing::TestWithParam<AlgorithmTestParam<float>> { };

template <typename T>
static void runTests(const AlgorithmTestParam<T>& param)
{
	auto [algo, data] = param;

	auto [start, end, sum] = maxSumSubarray(data.input, data.input.size(), algo);

	if constexpr(std::is_floating_point_v<T>)
		ASSERT_DOUBLE_EQ(data.sum, sum);
	else
		ASSERT_EQ(data.sum, sum);

	ASSERT_EQ(data.start, start);
	ASSERT_EQ(data.end, end);
}

TEST_P(MaxSumSubarrayIntegralTestFixture, ReturnsCorrectSubarrayAndSum)
{
	runTests(GetParam());
}

TEST_P(MaxSumSubarrayFloatingPointTestFixture, ReturnsCorrectSubarrayAndSum)
{
	runTests(GetParam());
}



INSTANTIATE_TEST_CASE_P(
	MaxSumSubarrayIntegralTests,
	MaxSumSubarrayIntegralTestFixture,
	::testing::Values(
		// Brute Force
		AlgorithmTestParam<int>(BRUTE_FORCE, { {-2, 1, -3, 4, -1, 2, 1, -5, 4}, 3, 6, 6 }),
		AlgorithmTestParam<int>(BRUTE_FORCE, { {-5, -8, -1, -2, -4}, 2, 2, -1 }),
		AlgorithmTestParam<int>(BRUTE_FORCE, { {1, 2, 3, 4, 5}, 0, 4, 15 }),
		AlgorithmTestParam<int>(BRUTE_FORCE, { {7}, 0, 0, 7 }),
		AlgorithmTestParam<int>(BRUTE_FORCE, { {0}, 0, 0, 0 }),
		AlgorithmTestParam<int>(BRUTE_FORCE, { {INT32_MAX, INT32_MAX}, 0, 1, 2 * static_cast<WideType<int>>(INT32_MAX) }),

		// Divide and Conquer
		AlgorithmTestParam<int>(DIVIDE_AND_CONQUER, { {-2, 1, -3, 4, -1, 2, 1, -5, 4}, 3, 6, 6 }),
		AlgorithmTestParam<int>(DIVIDE_AND_CONQUER, { {-5, -8, -1, -2, -4}, 2, 2, -1 }),
		AlgorithmTestParam<int>(DIVIDE_AND_CONQUER, { {1, 2, 3, 4, 5}, 0, 4, 15 }),
		AlgorithmTestParam<int>(DIVIDE_AND_CONQUER, { {0}, 0, 0, 0 }),
		AlgorithmTestParam<int>(DIVIDE_AND_CONQUER, { {7}, 0, 0, 7 }),
		AlgorithmTestParam<int>(DIVIDE_AND_CONQUER, { {INT32_MAX, INT32_MAX}, 0, 1, 2 * static_cast<WideType<int>>(INT32_MAX) })
	)
);

INSTANTIATE_TEST_CASE_P(
	MaxSumSubarrayFloatingPointTests,
	MaxSumSubarrayFloatingPointTestFixture,
	::testing::Values(
		// Brute Force
		AlgorithmTestParam<float>(BRUTE_FORCE, { {-2.0f, 1.0f, -3.0f, 4.0f, -1.0f, 2.0f, 1.0f, -5.0f, 4.0f}, 3, 6, 6.0f }),
		AlgorithmTestParam<float>(BRUTE_FORCE, { {-5.0f, -8.0f, -1.0f, -2.0f, -4.0f}, 2, 2, -1.0f }),
		AlgorithmTestParam<float>(BRUTE_FORCE, { {1.0f, 2.0f, 3.0f, 4.0f, 5.0f}, 0, 4, 15.0f }),
		AlgorithmTestParam<float>(BRUTE_FORCE, { {7.0f}, 0, 0, 7.0f }),
		AlgorithmTestParam<float>(BRUTE_FORCE, { {0.0f}, 0, 0, 0.0f }),
		AlgorithmTestParam<float>(BRUTE_FORCE, { {FLT_MAX, FLT_MAX}, 0, 1, 2 * static_cast<WideType<float>>(FLT_MAX) }),

		// Divide and Conquer
		AlgorithmTestParam<float>(DIVIDE_AND_CONQUER, { {-2.0f, 1.0f, -3.0f, 4.0f, -1.0f, 2.0f, 1.0f, -5.0f, 4.0f}, 3, 6, 6.0f }),
		AlgorithmTestParam<float>(DIVIDE_AND_CONQUER, { {-5.0f, -8.0f, -1.0f, -2.0f, -4.0f}, 2, 2, -1.0f }),
		AlgorithmTestParam<float>(DIVIDE_AND_CONQUER, { {1.0f, 2.0f, 3.0f, 4.0f, 5.0f}, 0, 4, 15.0f }),
		AlgorithmTestParam<float>(DIVIDE_AND_CONQUER, { {7.0f}, 0, 0, 7.0f }),
		AlgorithmTestParam<float>(DIVIDE_AND_CONQUER, { {0.0f}, 0, 0, 0.0f }),
		AlgorithmTestParam<float>(DIVIDE_AND_CONQUER, { {FLT_MAX, FLT_MAX}, 0, 1, 2 * static_cast<WideType<float>>(FLT_MAX) })
	)
);