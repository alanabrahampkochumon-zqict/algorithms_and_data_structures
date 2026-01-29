add_library(
    Sorting
    INTERFACE
)
target_compile_features(Sorting INTERFACE cxx_std_17)


set(HeaderFolder "include/")
set(HeaderFiles "InsertionSort.h;SelectionSort.h;RecursiveInsertionSort.h;BinaryInsertionSort.h;MergeSort.h")
list(TRANSFORM HeaderFiles PREPEND ${HeaderFolder})

set(TemplateDefinitionsFolder "include/")
set(TemplateDefinitionsFiles "InsertionSort.tpp;SelectionSort.tpp;RecursiveInsertionSort.tpp;BinaryInsertionSort.tpp;MergeSort.tpp")
list(TRANSFORM TemplateDefinitionsFiles PREPEND ${TemplateDefinitionsFolder})

# message(${TemplateDefinitionsFiles})
# message(${HeaderFiles})

target_sources(
    Sorting
    INTERFACE
    FILE_SET HEADERS
    TYPE HEADERS
    BASE_DIRS include
    FILES
        ${HeaderFiles} ${TemplateDefinitionsFiles}
)

target_include_directories(
    Sorting
    INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)

source_group("Template Files" FILES ${TemplateDefinitionsFiles})

add_custom_target(SortingAlgorithms ALL
    SOURCES
    ${HeaderFiles} ${TemplateDefinitionsFiles}
)