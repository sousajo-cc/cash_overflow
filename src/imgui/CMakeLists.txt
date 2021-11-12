# imgui test executable, with full warnings enable
add_executable(test_imgui test.cpp logger.hpp fileHandler.hpp window.hpp)
find_package(ImGui-SFML REQUIRED)
find_package(tl-expected REQUIRED)
include_directories(${tl_INCLUDE_DIRS})
find_package(fmt REQUIRED)
include_directories(${fmt_INCLUDE_DIRS})

target_link_libraries(test_imgui PRIVATE project_warnings project_options ImGui-SFML::ImGui-SFML fmt::fmt)
