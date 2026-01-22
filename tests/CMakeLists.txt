add_executable(Tests)

set(SearchTestSources "src/searching/LinearSearchTest.cpp")
set(SortTestSources "src/sorting/InsertionSortTest.cpp" "src/generic/Test.cpp")
set(GenericTestSources "src/generic/BinaryAdderTests.cpp")


target_sources(
    Tests
    PRIVATE
    ${SearchTestSources} ${SortTestSources} ${GenericTestSources}
)

target_link_libraries(
    Tests

    PRIVATE
    Sorting
    Searching
    Generic
    GTest::gtest_main
)
 
enable_testing()
include(GoogleTest)
gtest_discover_tests(Tests)