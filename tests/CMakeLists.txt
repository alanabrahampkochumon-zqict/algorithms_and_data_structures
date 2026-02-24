add_executable(Tests)

set(SortTestFolder "src/sorting/")
set(SortTestFiles "InsertionSortTest.cpp;SelectionSortTest.cpp;RecursiveInsertionSortTest.cpp;BinaryInsertionSortTest.cpp;MergeSortTest.cpp;HybridSortTest.cpp;BubbleSortTest.cpp")
list(TRANSFORM SortTestFiles PREPEND ${SortTestFolder})

set(SearchTestFolder "src/searching/")
set(SearchTestFiles "LinearSearchTest.cpp;BinarySearchTest.cpp")
list(TRANSFORM SearchTestFiles PREPEND ${SearchTestFolder})

set(GenericTestFolder "src/generic/")
set(GenericTestFiles "BinaryAdderTest.cpp;TwoSumTest.cpp;HornersRuleTest.cpp;InversionCountTest.cpp")
list(TRANSFORM GenericTestFiles PREPEND ${GenericTestFolder})

set(DivideAndConquerTestFolder "src/divide-and-conquer/")
set(DivideAndConquerTestFiles "MaxSumSubarray.cpp")
list(TRANSFORM DivideAndConquerTestFiles PREPEND ${DivideAndConquerTestFolder})

target_sources(
    Tests
    PRIVATE
    ${SearchTestFiles} ${SortTestFiles} ${GenericTestFiles} ${DivideAndConquerTestFiles}
)

source_group("Source Files\\SearchTests" FILES ${SearchTestFiles})
source_group("Source Files\\SortTests" FILES ${SortTestFiles})
source_group("Source Files\\GenericTests" FILES ${GenericTestFiles})
source_group("Source Files\\DivideAndConquerTests" FILES ${DivideAndConquerTestFiles})

target_link_libraries(
    Tests

    PRIVATE
    Sorting
    Searching
    Generic
    DivideAndConquer
    GTest::gtest_main
    GTest::gmock_main
)


enable_testing()
include(GoogleTest)
gtest_discover_tests(Tests)