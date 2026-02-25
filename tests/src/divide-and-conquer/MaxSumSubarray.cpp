#include <gtest/gtest.h>
#include <concepts>
#include <array>
#include <MaxSumSubarray.h>

using namespace Algorithms::DivideAndConquer;


template<typename T>
	requires std::integral<T> || std::floating_point<T>
struct TestCaseData
{
	std::vector<T> input;
	std::size_t start;
	std::size_t end;
	T sum;
};

template<typename T>
	requires std::integral<T> || std::floating_point<T>
struct AlgorithmTestParam
{
	AlgorithmType algo;
	TestCaseData<T> data;
};



class MaxSumSubarrayTestFixture : public ::testing::TestWithParam<AlgorithmTestParam<int>> {};

TEST_P(MaxSumSubarrayTestFixture, ReturnsCorrectSubarrayAndSum)
{
	const auto& param = GetParam();

	auto [start, end, sum] = maxSumSubarray(param.data.input, param.algo);

	ASSERT_EQ(param.data.start, start);
	ASSERT_EQ(param.data.end, end);
	ASSERT_EQ(param.data.sum, sum);
}



INSTANTIATE_TEST_CASE_P(
	MaxSumSubarrayTests,
	MaxSumSubarrayTestFixture,
	::testing::Values(
		AlgorithmTestParam<int>(BRUTE_FORCE, { {-2, 1, -3, 4, -1, 2, 1, -5, 4}, 3, 6, 6 }),
		AlgorithmTestParam<int>(BRUTE_FORCE, { {-5, -8, -1, -2, -4}, 2, 2, -1 }),
		AlgorithmTestParam<int>(BRUTE_FORCE, { {1, 2, 3, 4, 5}, 0, 4, 15 }),
		AlgorithmTestParam<int>(BRUTE_FORCE, { {7}, 0, 0, 7 })
	)

);