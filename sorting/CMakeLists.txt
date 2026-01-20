add_library(
    Sorting
    INTERFACE
)

set(Headers include/InsertionSort.h)
set(TemplateUnits include/InsertionSort.tpp)

set(INCLUDE_FILES
    ${Headers} ${TemplateUnits}
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

source_group("Templates" FILES ${TemplateUnits})

add_custom_target(SortingAlgorithms ALL
    SOURCES
    ${INCLUDE_FILES}
)