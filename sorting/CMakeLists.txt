add_library(
    Sorting
    INTERFACE
)
target_compile_features(Sorting INTERFACE cxx_std_17)

set(HeaderFolder "include/")
set(TemplateFolder "include/")

set(HeaderFiles "InsertionSort.h;SelectionSort.h")
set(TemplateFiles "InsertionSort.tpp;SelectionSort.tpp")

function(ConcatWithFolder FolderName FileList ResultList)

    set(TempList "${${ResultList}}")

    foreach(_file ${FileList})
        string(CONCAT FileName ${FolderName} ${_file})
        list(APPEND TempList ${FileName})
    endforeach()

    set(${ResultList} ${TempList} PARENT_SCOPE)

endfunction()


ConcatWithFolder(${HeaderFolder} "${HeaderFiles}" HeaderSources)
ConcatWithFolder(${TemplateFolder} "${TemplateFiles}" TemplateDefinitionSources)


set(INCLUDE_FILES ${HeaderSources} ${TemplateDefinitionSources})

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

source_group("Templates" FILES ${TemplateDefinitionSources})

add_custom_target(SortingAlgorithms ALL
    SOURCES
    ${INCLUDE_FILES}
)