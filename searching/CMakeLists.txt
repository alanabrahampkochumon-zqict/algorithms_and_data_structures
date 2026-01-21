add_library(Searching INTERFACE)

set(TemplateUnits include/LinearSearch.tpp)
set(Headers include/LinearSearch.h)

target_sources(Searching
    INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
        ${TemplateUnits} ${Headers}
)

target_include_directories(
    Sorting
    INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)

source_group("Templates" FILES ${TemplateUnits})

add_custom_target(
    SearchingAlgorithms
    ALL
    SOURCES
    ${TemplateUnits} ${Headers}
)