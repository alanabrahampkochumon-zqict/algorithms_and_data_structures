add_executable(BenchmarkSuite)

# DAC -> Divide And Conquer
set(DACDirectory "src/DivideAndConquer/")
set(DACFiles "MaxSumSubArrayBenchmarks.cpp")
list(TRANSFORM DACFiles PREPEND ${DACDirectory})

set(HelperDirectory "include/helpers/")
set(HelperFiles "RandomGenerators.h")
list(TRANSFORM HelperFiles PREPEND ${HelperDirectory})

target_sources(
    BenchmarkSuite
    PRIVATE
    ${DACFiles}
    ${HelperFiles}
)

target_precompile_headers(
    BenchmarkSuite
    PRIVATE
    <benchmark/benchmark.h>
    <vector>
)

target_include_directories(BenchmarkSuite PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(
    BenchmarkSuite
    PRIVATE
    DivideAndConquer
    benchmark::benchmark
    benchmark::benchmark_main
)

source_group("Source Files\\Divide and Conquer" FILES ${DACFiles})