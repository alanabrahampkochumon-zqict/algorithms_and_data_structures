add_executable(Tests)

set(SortTestFolder "src/sorting/")
set(SortTestFiles "InsertionSortTest.cpp;SelectionSortTest.cpp")
list(TRANSFORM SortTestFiles PREPEND ${SortTestFolder})

set(SearchTestFolder "src/searching/")
set(SearchTestFiles "LinearSearchTest.cpp;BinarySearchTest.cpp;RecursiveInsertionSortTest.cpp")
list(TRANSFORM SearchTestFiles PREPEND ${SearchTestFolder})

set(GenericTestFolder "src/generic/")
set(GenericTestFiles "BinaryAdderTest.cpp")
list(TRANSFORM GenericTestFiles PREPEND ${GenericTestFolder})


target_sources(
    Tests
    PRIVATE
    ${SearchTestFiles} ${SortTestFiles} ${GenericTestFiles}
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