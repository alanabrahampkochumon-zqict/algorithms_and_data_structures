add_library(DivideAndConquer INTERFACE)

target_compile_options(DivideAndConquer INTERFACE cxx_std_20)

set(IncludeDirectory "include/")
set(HeaderFiles "MaxSumSubarray.h")
list(TRANSFORM HeaderFiles PREPEND ${IncludeDirectory})

set(TemplateFiles "MaxSumSubarray.tpp")
list(TRANSFORM TemplateFiles PREPEND ${IncludeDirectory})

target_sources(
    DivideAndConquer
    INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ${IncludeDirectory}
    FILES
    ${HeaderFiles} ${TemplateFiles}
)

target_include_directories(
    DivideAndConquer INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)

source_group("Template Files" FILES ${TemplateFiles})

add_custom_target(
    DivideAndConquerAlgorithms
    ALL
    SOURCES
    ${HeaderFiles} ${TemplateFiles}
)