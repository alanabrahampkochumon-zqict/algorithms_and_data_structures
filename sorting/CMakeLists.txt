add_library(
    Sorting
    INTERFACE
)

set(INCLUDE_FILES
    include/InsertionSort.h include/InsertionSort.tpp
)

target_sources(
    Sorting

    INTERFACE
    FILE_SET HEADERS
    TYPE HEADERS
    BASE_DIRS include
    FILES
        ${INCLUDE_FILES}
)

target_include_directories(
    Sorting
    INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include"
    "$<INSTALL_INTERFACE:include>"
)

add_custom_target(SortingHeaders ALL
    SOURCES
    ${INCLUDE_FILES}
)