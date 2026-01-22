add_library(GenericAlgorithms STATIC)

target_sources(
    GenericAlgorithms
    PRIVATE
        src/BinaryAdder.cpp

    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
        include/
    FILES
        include/BinaryAdder.h
)