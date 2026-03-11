add_executable(Tests)

set(IncludeDirectory "include/")
set(TestUtilFiles "TestUtils.h")
list(TRANSFORM TestUtilFiles PREPEND ${IncludeDirectory})

set(SortTestFolder "src/sorting/")
set(SortTestFiles "InsertionSortTests.cpp;SelectionSortTests.cpp;RecursiveInsertionSortTests.cpp;BinaryInsertionSortTests.cpp;MergeSortTests.cpp;HybridSortTests.cpp;BubbleSortTests.cpp")
list(TRANSFORM SortTestFiles PREPEND ${SortTestFolder})

set(SearchTestFolder "src/searching/")
set(SearchTestFiles "LinearSearchTests.cpp;BinarySearchTests.cpp")
list(TRANSFORM SearchTestFiles PREPEND ${SearchTestFolder})

set(GenericTestFolder "src/generic/")
set(GenericTestFiles "BinaryAdderTests.cpp;TwoSumTests.cpp;HornersRuleTests.cpp;InversionCountTests.cpp")
list(TRANSFORM GenericTestFiles PREPEND ${GenericTestFolder})

set(DivideAndConquerTestFolder "src/divide-and-conquer/")
set(DivideAndConquerTestFiles "MaxSumSubarrayTests.cpp;")
list(TRANSFORM DivideAndConquerTestFiles PREPEND ${DivideAndConquerTestFolder})

set(DataStructuresTestFolder "src/datastructures/")
set(DataStructuresTestFiles "MatrixTests.cpp;")
list(TRANSFORM DataStructuresTestFiles PREPEND ${DataStructuresTestFolder})

target_sources(
    Tests
    PRIVATE
    ${SearchTestFiles} ${SortTestFiles} ${GenericTestFiles} ${DivideAndConquerTestFiles} ${DataStructuresTestFiles}

    PRIVATE
    FILE_SET HEADERS
    BASE_DIRS ${IncludeDirectory}
    FILES ${TestUtilFiles}
)

source_group("Source Files\\SearchTests" FILES ${SearchTestFiles})
source_group("Source Files\\SortTests" FILES ${SortTestFiles})
source_group("Source Files\\GenericTests" FILES ${GenericTestFiles})
source_group("Source Files\\DivideAndConquerTests" FILES ${DivideAndConquerTestFiles})
source_group("Source Files\\DataStructureTests" FILES ${DataStructuresTestFiles})

target_precompile_headers(Tests PRIVATE
    <vector>
    <gtest/gtest.h>
)

target_include_directories(Tests PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>")

target_link_libraries(
    Tests

    PRIVATE
    Sorting
    Searching
    Generic
    DivideAndConquer
    DataStructure
    GTest::gtest_main
    GTest::gmock_main
)


enable_testing()
include(GoogleTest)
gtest_discover_tests(Tests)