add_library(Common INTERFACE)

set(IncludeDirectory "include/")
set(IncludeFiles "Concepts.h")
list(TRANSFORM IncludeFiles PREPEND ${IncludeDirectory})

target_sources(
    Common INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ${IncludeDirectory}
    FILES ${IncludeFiles}
)

target_include_directories(
    Common INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${IncludeDirectory}>
    $<INSTALL_INTERFACE:include>
)

add_custom_target(
    CommonUtils
    ALL
    SOURCES ${IncludeFiles}
)