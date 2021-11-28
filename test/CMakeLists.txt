include(CTest)
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

find_package(ImGui-SFML REQUIRED)

find_package(tl-expected REQUIRED)
include_directories(${tl_INCLUDE_DIRS})

find_package(fmt REQUIRED)
include_directories(${fmt_INCLUDE_DIRS})

enable_testing()
include(GoogleTest)

include_directories(../src/imgui)

add_executable(
        categoryTests
        categoryTests.cpp
)
target_link_libraries(
        categoryTests
        gtest_main
        project_warnings
        project_options
        fmt::fmt
)
gtest_discover_tests(categoryTests)

add_executable(
        dateTests
        dateTests.cpp
)
target_link_libraries(
        dateTests
        gtest_main
        project_warnings
        project_options
        fmt::fmt
)
gtest_discover_tests(dateTests)

add_executable(
        mapTests
        mapTests.cpp
)
target_link_libraries(
        mapTests
        gtest_main
        project_warnings
        project_options
)
gtest_discover_tests(mapTests)

add_executable(
        tableBuilderTests
        tableBuilderTests.cpp
)
target_link_libraries(
        tableBuilderTests
        gtest_main
        project_warnings
        project_options
        ImGui-SFML::ImGui-SFML
        fmt::fmt
)
gtest_discover_tests(tableBuilderTests)

add_executable(
        fileHandlerTests
        fileHandlerTests.cpp
)
target_link_libraries(
        fileHandlerTests
        gtest_main
        project_warnings
        project_options
)
gtest_discover_tests(fileHandlerTests)
add_custom_command(
        TARGET fileHandlerTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources
        ${CMAKE_CURRENT_BINARY_DIR}/resources
)
