find_package(ImGui-SFML REQUIRED)
find_package(tl-expected REQUIRED)
include_directories(${tl_INCLUDE_DIRS})
find_package(fmt REQUIRED)
include_directories(${fmt_INCLUDE_DIRS})
find_package(range-v3 REQUIRED)
include_directories(SYSTEM ${range-v3_INCLUDE_DIRS})

add_library(money money.cpp money.hpp)
target_link_libraries(money PRIVATE project_warnings project_options)

add_executable(test_imgui main.cpp logger.hpp fileHandler.hpp imguiWrapper/window.hpp logger.hpp)
target_link_libraries(test_imgui PRIVATE project_warnings project_options money ImGui-SFML::ImGui-SFML fmt::fmt)

add_custom_command(
        TARGET test_imgui POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets
)
