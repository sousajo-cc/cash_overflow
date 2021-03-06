from conans import ConanFile


class CppStarterProject(ConanFile):
    # Note: options are copied from CMake boolean options.
    # When turned off, CMake sometimes passes them as empty strings.
    options = {
        "cpp_starter_use_imgui": ["ON", "OFF", ""],
        "cpp_starter_use_sdl": ["ON", "OFF", ""]
    }
    name = "CppStarterProject"
    version = "0.1"
    requires = (
        "catch2/2.13.7",
        "docopt.cpp/0.6.2",
        "fmt/8.0.1",
        "range-v3/0.11.0",
        "spdlog/1.9.2",
        "tl-expected/1.0.0",
        "sqlite3/3.36.0",
        "imgui-sfml/2.2@bincrafters/stable",
    )
    generators = "cmake", "gcc", "txt", "cmake_find_package"

    def requirements(self):
        if self.options.cpp_starter_use_imgui == "ON":
            self.requires("imgui-sfml/2.2@bincrafters/stable")
        if self.options.cpp_starter_use_sdl == "ON":
            self.requires("sdl2/2.0.10@bincrafters/stable")

