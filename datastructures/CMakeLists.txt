add_library(DataStructure INTERFACE)

target_compile_features(DataStructure INTERFACE cxx_std_20)

set(IncludeDirectory "include/")
set(HeaderFiles "Matrix.h;MatrixView.h")
list(TRANSFORM HeaderFiles PREPEND ${IncludeDirectory})

set(TemplateFiles "Matrix.tpp;MatrixView.tpp")
list(TRANSFORM TemplateFiles PREPEND ${IncludeDirectory})

target_sources(
    DataStructure
    INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ${IncludeDirectory}
    FILES ${HeaderFiles} ${TemplateFiles}
)

target_include_directories(
    DataStructure INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(
    DataStructure INTERFACE Common
)

source_group("Header Files" FILES ${HeaderFiles})
source_group("Template Files" FILES ${TemplateFiles})

add_custom_target(
    DataStructures
    ALL
    SOURCES
    ${HeaderFiles} ${TemplateFiles}
)