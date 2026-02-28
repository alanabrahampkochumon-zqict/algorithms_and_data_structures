add_executable(Benchmark)

# DAC -> Divide And Conquer
set(DACDirectory "src/DivideAndConquer/")
set(DACFiles "MaxSumSubArrayBenchmarks.cpp")
list(TRANSFORM DACFiles PREPEND ${DACDirectory})

target_sources(
    Benchmark
    PRIVATE
    ${DACFiles}
)

target_link_libraries(
    Benchmark
    PRIVATE
    DivideAndConquer
)

source_group("Source Files\\Divide and Conquer" FILES ${DACFiles})