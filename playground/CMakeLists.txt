add_executable(
    Playground
)

target_sources(
    Playground

    PRIVATE
    src/main.cpp
)

target_link_libraries(
    Playground
    Sorting
)