option(CPP_STARTER_USE_IMGUI "Enable compilation of ImGui sample" ON)



# imgui example
if(CPP_STARTER_USE_IMGUI)
  message("Using Dear ImGui")
  add_subdirectory(imgui)
endif()


find_package(fmt)
find_package(spdlog)
find_package(docopt)

# Generic test that uses conan libs
# add_executable(intro main.cpp)
# target_link_libraries(
#   intro
#   PRIVATE project_options
#           project_warnings
#           docopt::docopt
#           fmt::fmt
#           spdlog::spdlog)
