#include <MaxSumSubarray.h>

#include <benchmark/benchmark.h>

#include "../../include/helpers/RandomGenerators.h"

using namespace Helpers;

using namespace Algorithms::DivideAndConquer;

template<AlgorithmType Algorithm>
static void BM_MaxSumSubarray(benchmark::State &state)
{
	std::size_t size = state.range(0);
	std::vector vector = generateRandomVector<int>(size);

	for (auto _ : state)
		benchmark::DoNotOptimize(maxSumSubarray(vector, vector.size(), Algorithm));
}



BENCHMARK_TEMPLATE(BM_MaxSumSubarray, BRUTE_FORCE)->RangeMultiplier(2)->Range(8, 8192);
BENCHMARK_TEMPLATE(BM_MaxSumSubarray, DIVIDE_AND_CONQUER)->RangeMultiplier(2)->Range(8, 8192);
BENCHMARK_TEMPLATE(BM_MaxSumSubarray, HYBRID)->RangeMultiplier(2)->Range(8, 8192);
