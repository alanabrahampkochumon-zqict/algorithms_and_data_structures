include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723 # release-1.17.0
    SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/vendors/googletest"
)

FetchContent_MakeAvailable(googletest)

# Group the projects into a single folder
set_target_properties(gtest gtest_main gmock gmock_main PROPERTIES Folder "Google Test")