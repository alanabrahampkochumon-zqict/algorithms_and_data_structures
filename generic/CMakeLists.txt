add_library(Generic INTERFACE)
target_compile_features(Generic INTERFACE cxx_std_17)

set(HeaderFiles include/BinaryAdder.h)
set(TemplateDefinitions include/BinaryAdder.tpp)

target_sources(
    Generic
    INTERFACE
    ${HeaderFiles} ${TemplateDefinitions}
)

target_include_directories(
    Generic
    INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_DEFAULT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)

source_group("Templates" FILES ${TemplateDefinitions})

add_custom_target(GenericAlgorithms
    ALL
    SOURCES
        ${HeaderFiles} ${TemplateDefinitions}
)