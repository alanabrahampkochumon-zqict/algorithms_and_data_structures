add_library(Searching INTERFACE)
target_compile_features(Searching INTERFACE cxx_std_17)

set(HeaderDirectory "include/")
set(HeaderFiles LinearSearch.h BinarySearch.h)
list(TRANSFORM HeaderFiles PREPEND ${HeaderDirectory})

set(TemplateDefinitionDirectory "include/")
set(TemplateDefinitionFiles LinearSearch.tpp BinarySearch.tpp)
list(TRANSFORM TemplateDefinitionFiles PREPEND ${TemplateDefinitionDirectory})


target_sources(Searching
    INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
        ${HeaderFiles} ${TemplateDefinitionFiles}
)

target_include_directories(
    Searching
    INTERFACE   
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)

# Grouping for VS Solution Explorer
source_group("Templates" FILES ${TemplateDefinitionFiles})

add_custom_target(
    SearchingAlgorithms
    ALL
    SOURCES
    ${HeaderFiles} ${TemplateDefinitionFiles}
)