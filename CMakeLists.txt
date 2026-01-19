cmake_minimum_required(VERSION 3.23)
project(Algorithms)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(dependencies.cmake)

add_subdirectory(sorting)
add_subdirectory(playground)
add_subdirectory(tests)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Playground)
