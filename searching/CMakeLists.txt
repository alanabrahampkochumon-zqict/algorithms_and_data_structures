add_library(Searching INTERFACE)
target_compile_features(Searching INTERFACE cxx_std_17)

function(CreateSourceWithFolder FolderName FileList ResultList)
    set(TempList "${${ResultList}}")
    foreach(_FILE ${FileList})
        string(CONCAT Filename ${FolderName} ${_FILE})
        list(APPEND ResultList ${Filename})
    endforeach()
    set(${ResultList} ${TempList} PARENT_SCOPE)
endfunction()

set(HeaderDirectory "include/")
set(HeaderFiles LinearSearch.h BinarySearch.h)
CreateSourceWithFolder(${HeaderDirectory} "${HeaderFiles}" HeaderSource)

set(TemplateDefinitionDirectory "include/")
set(TemplateDefinitionFiles LinearSearch.h BinarySearch.h)
CreateSourceWithFolder(${TemplateDefinitionDirectory} "${TemplateDefinitionFiles}" TemplateDefinitionSource)


set(Headers include/LinearSearch.h include/BinarySearch.h)
set(TemplateDefinitions include/LinearSearch.tpp include/BinarySearch.tpp)

target_sources(Searching
    INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
        ${HeaderSource} ${TemplateDefinitionSource}
)

target_include_directories(
    Searching
    INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)

# Grouping for VS Solution Explorer
source_group("Templates" FILES ${TemplateDefinitionSource})

add_custom_target(
    SearchingAlgorithms
    ALL
    SOURCES
    ${HeaderSource} ${TemplateDefinitionSource}
)