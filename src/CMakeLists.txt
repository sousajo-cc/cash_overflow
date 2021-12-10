option(CPP_STARTER_USE_QT "Enable compilation of QT sample" OFF)
option(CPP_STARTER_USE_FLTK "Enable compilation of FLTK sample" OFF)
option(CPP_STARTER_USE_GTKMM "Enable compilation of GTKMM sample" OFF)
option(CPP_STARTER_USE_IMGUI "Enable compilation of ImGui sample" OFF)
option(CPP_STARTER_USE_NANA "Enable compilation of Nana GUI sample" OFF)
option(CPP_STARTER_USE_SDL "Enable compilation of SDL sample" OFF)

# sdl
if(CPP_STARTER_USE_SDL)
  message("THIS OPTION WAS REMOVED!")
endif()

# qt
if(CPP_STARTER_USE_QT)
  message("THIS OPTION WAS REMOVED!")
endif()

# fltk test
if(CPP_STARTER_USE_FLTK)
  message("THIS OPTION WAS REMOVED!")
endif()

# gtkmm test
if(CPP_STARTER_USE_GTKMM)
  message("THIS OPTION WAS REMOVED!")
endif()

# imgui example
if(CPP_STARTER_USE_IMGUI)
  message("Using Dear ImGui")
  add_subdirectory(imgui)
endif()

# Nana
if(CPP_STARTER_USE_NANA)
  message("THIS OPTION WAS REMOVED!")
endif()


find_package(fmt)
find_package(spdlog)
find_package(docopt)
find_package(SQLite3 REQUIRED)
include_directories(${SQLite3_INCLUDE_DIRS})
# Generic test that uses conan libs
add_executable(intro main.cpp)
target_link_libraries(
  intro
  PRIVATE project_options
          project_warnings
          docopt::docopt
          fmt::fmt
          spdlog::spdlog ${SQLite3_LIBRARIES})

