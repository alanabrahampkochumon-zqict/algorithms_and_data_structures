add_executable(Tests)

set(SearchTestSources "src/searching/LinearSearchTest.cpp")
set(SortTestSources "src/sorting/InsertionSortTest.cpp")


target_sources(
    Tests
    PRIVATE
    ${SearchTestSources} ${SortTestSources}
)

target_link_libraries(
    Tests

    PRIVATE
    Sorting
    Searching
    GTest::gtest_main
)

enable_testing()
include(GoogleTest)
gtest_discover_tests(Tests)