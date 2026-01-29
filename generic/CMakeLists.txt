add_library(Generic INTERFACE)
target_compile_features(Generic INTERFACE cxx_std_17)

set(HeaderDirectory "include/")
set(HeaderFiles BinaryAdder.h TwoSum.h)
list(TRANSFORM HeaderFiles PREPEND ${HeaderDirectory})
set(TemplateDefinitionFiles BinaryAdder.tpp TwoSum.tpp)
list(TRANSFORM TemplateDefinitionFiles PREPEND ${HeaderDirectory})

target_sources(
    Generic
    INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
        ${HeaderFiles} ${TemplateDefinitionFiles}
)

target_include_directories(
    Generic
    INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)

source_group("Templates" FILES ${TemplateDefinitionFiles})

add_custom_target(
    GenericAlgorithms
    ALL
    SOURCES
        ${HeaderFiles} ${TemplateDefinitionFiles}
)