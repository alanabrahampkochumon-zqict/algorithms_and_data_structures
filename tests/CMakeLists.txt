add_executable(Tests)

set(SortTestFolder "src/sorting/")
set(SearchTestFolder "src/searching/")
set(GenericTestFolder "src/generic/")

set(SortTestFiles "InsertionSortTest.cpp;SelectionSortTest.cpp")
set(SearchTestFiles "LinearSearchTest.cpp")
set(GenericTestFiles "BinaryAdderTest.cpp")

function (ConcatWithFolder FolderName FileList ResultList)
    set(TempList "${${ResultList}}")

    foreach(_file ${FileList})
        string(CONCAT FileName ${FolderName} ${_file})
        list(APPEND TempList ${FileName})
    endforeach()

    set(${ResultList} "${TempList}" PARENT_SCOPE)

endfunction()


ConcatWithFolder(${SortTestFolder} "${SortTestFiles}" SortTestSources)
ConcatWithFolder(${SearchTestFolder} "${SearchTestFiles}" SearchTestSources)
ConcatWithFolder(${GenericTestFolder} "${GenericTestFiles}" GenericTestSources)


message(${SortTestSources})
message(${SearchTestSources})
message(${GenericTestSources})

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