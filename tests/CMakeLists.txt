add_executable(Tests)

target_sources(
    Tests
    PRIVATE
    src/sorting/InsertionSortTest.cpp
)

target_link_libraries(
    Tests

    PRIVATE
    Sorting
    GTest::gtest_main
)

enable_testing()
include(GoogleTest)
gtest_discover_tests(Tests)