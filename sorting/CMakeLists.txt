add_library(
    Sorting
)

target_sources(
    Sorting

    PRIVATE
    src/InsertionSort.cpp
    
    PUBLIC
    FILE_SET HEADERS
    TYPE HEADERS
    BASE_DIRS include
    FILES
        include/InsertionSort.h
)