#include <MaxSumSubarray.h>

#include <benchmark/benchmark.h>

#include "../../include/helpers/RandomGenerators.h"

using namespace Helpers;

static void BM_BruteForce(benchmark::State &state)
{
	std::size_t size = state.range(0);
	std::vector vector = generateRandomVector<int>(size);

	for (auto _ : state)
		benchmark::DoNotOptimize(Algorithms::DivideAndConquer::maxSumSubarray(vector, vector.size(), Algorithms::DivideAndConquer::BRUTE_FORCE));
}


BENCHMARK(BM_BruteForce)->RangeMultiplier(2)->Range(8, 8192);
