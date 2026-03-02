#include <MaxSumSubarray.h>

#include <benchmark/benchmark.h>

#include "../../include/helpers/RandomGenerators.h"

using namespace Helpers;

using namespace Algorithms::DivideAndConquer;

namespace
{
	template<AlgorithmType Algorithm>
	void BM_MaxSumSubarray(benchmark::State& state)
	{
		std::size_t size = state.range(0);
		std::vector vector = generateRandomVector<int>(size);

		for (auto _ : state)
			benchmark::DoNotOptimize(maxSumSubarray(vector, vector.size(), Algorithm));
	}

	BENCHMARK_TEMPLATE(BM_MaxSumSubarray, BRUTE_FORCE)->RangeMultiplier(2)->Range(8, 8192);
	BENCHMARK_TEMPLATE(BM_MaxSumSubarray, DIVIDE_AND_CONQUER)->RangeMultiplier(2)->Range(8, 8192);
	BENCHMARK_TEMPLATE(BM_MaxSumSubarray, HYBRID)->RangeMultiplier(2)->Range(8, 8192);

	//void BM_MaxSumSubarray_Hybrid(benchmark::State& state)
	//{
	//	std::size_t size = state.range(0);
	//	std::size_t limit = state.range(1);

	//	std::vector vector = generateRandomVector<int>(size);

	//	for (auto _ : state)
	//		benchmark::DoNotOptimize(maxSumSubarray(vector, vector.size(), HYBRID, limit));
	//}

	//BENCHMARK(BM_MaxSumSubarray_Hybrid)->RangeMultiplier(2)->Ranges({ { 8, 8192 }, { 10, 80 } });


	template <AlgorithmType Algorithm>
	void BM_MaxSumSubarray_Hybrid_K(benchmark::State& state)
	{
		std::size_t limit = state.range(0);

		std::vector vector = generateRandomVector<int>(16000);

		for (auto _: state)
		{
			benchmark::DoNotOptimize(maxSumSubarray(vector, vector.size(),Algorithm, limit));
		}
	}

	BENCHMARK_TEMPLATE(BM_MaxSumSubarray_Hybrid_K, DIVIDE_AND_CONQUER)->DenseRange(2, 2, 2); // Baseline
	BENCHMARK_TEMPLATE(BM_MaxSumSubarray_Hybrid_K, HYBRID)->DenseRange(10, 80, 2);

}