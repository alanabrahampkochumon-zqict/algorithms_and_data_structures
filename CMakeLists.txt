cmake_minimum_required(VERSION 3.25)
project(Algorithms)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CLANG Formatter
find_program(CLANG_FORMATTER NAMES clang-format)

if(CLANG_FORMATTER)
    file(GLOB_RECURSE ALL_SOURCE_FILES RELATIVE ${CMAKE_SOURCE_DIR} *.cpp *.h *.cxx *.hxx *.hpp *.cc *.hh *.tpp *.inl)

    add_custom_target(format
        COMMAND ${CLANG_FORMATTER} -i -style=file ${ALL_SOURCE_FILES}
        VERBATIM
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Formatting source files..."
    )
else()
    message(WARNING "clang-format not found")
endif()

include(dependencies.cmake)

add_subdirectory(sorting)
add_subdirectory(searching)
add_subdirectory(generic)
add_subdirectory(playground)
add_subdirectory(divide-and-conquer)
add_subdirectory(datastructures)
add_subdirectory(tests)
add_subdirectory(benchmark-suite)
add_subdirectory(common)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Playground)
