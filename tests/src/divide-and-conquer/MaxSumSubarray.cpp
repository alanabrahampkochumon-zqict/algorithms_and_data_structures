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


class MaxSumSubarrayTestFixture : public ::testing::TestWithParam<AlgorithmTestParam<int>> { };

TEST_P(MaxSumSubarrayTestFixture, ReturnsCorrectSubarrayAndSum)
{
	const auto& [algo, data] = GetParam();

	auto [start, end, sum] = maxSumSubarray(data.input, algo);

	ASSERT_EQ(data.start, start);
	ASSERT_EQ(data.end, end);
	ASSERT_EQ(data.sum, sum);
}



INSTANTIATE_TEST_CASE_P(
	MaxSumSubarrayTests,
	MaxSumSubarrayTestFixture,
	::testing::Values(
		AlgorithmTestParam<int>(BRUTE_FORCE, { {-2, 1, -3, 4, -1, 2, 1, -5, 4}, 3, 6, 6 }),
		AlgorithmTestParam<int>(BRUTE_FORCE, { {-5, -8, -1, -2, -4}, 2, 2, -1 }),
		AlgorithmTestParam<int>(BRUTE_FORCE, { {1, 2, 3, 4, 5}, 0, 4, 15 }),
		AlgorithmTestParam<int>(BRUTE_FORCE, { {7}, 0, 0, 7 }),
		AlgorithmTestParam<int>(BRUTE_FORCE, { {0}, 0, 0, 0 }),
		AlgorithmTestParam<int>(BRUTE_FORCE, { {INT32_MAX, INT32_MAX}, 0, 1, 2 * static_cast<WideType<int>>(INT32_MAX) })
	)
);