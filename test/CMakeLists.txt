include(CTest)
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

find_package(ImGui-SFML REQUIRED)

find_package(fmt REQUIRED)
include_directories(${fmt_INCLUDE_DIRS})

enable_testing()

add_executable(
    table_builder_tests
    table_builder_tests.cpp
)
target_link_libraries(
    table_builder_tests
    gtest_main
    project_warnings
    project_options
    ImGui-SFML::ImGui-SFML
    fmt::fmt
)

include(GoogleTest)
gtest_discover_tests(table_builder_tests)
