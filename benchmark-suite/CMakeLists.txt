add_executable(BenchmarkSuite)

# DAC -> Divide And Conquer
set(DACDirectory "src/DivideAndConquer/")
set(DACFiles "MaxSumSubArrayBenchmarks.cpp")
list(TRANSFORM DACFiles PREPEND ${DACDirectory})

target_sources(
    BenchmarkSuite
    PRIVATE
    ${DACFiles}
)

target_link_libraries(
    BenchmarkSuite
    PRIVATE
    DivideAndConquer
    benchmark::benchmark
    benchmark::benchmark_main
)

source_group("Source Files\\Divide and Conquer" FILES ${DACFiles})