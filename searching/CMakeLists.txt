add_library(Searching INTERFACE)
target_compile_features(Searching INTERFACE cxx_std_17)

set(TemplateDefinitions include/LinearSearch.tpp)
set(Headers include/LinearSearch.h)

target_sources(Searching
    INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
        ${TemplateDefinitions} ${Headers}
)

target_include_directories(
    Searching
    INTERFACE
    # Fixed the missing closing '>' below
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)

# Grouping for VS Solution Explorer
source_group("Templates" FILES ${TemplateDefinitions})

add_custom_target(
    SearchingAlgorithms
    ALL
    SOURCES
    ${TemplateDefinitions} ${Headers}
)