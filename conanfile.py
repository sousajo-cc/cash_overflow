from conans import ConanFile


class CppStarterProject(ConanFile):
    options = {
        "cpp_starter_use_imgui": ["ON", "OFF", ""],
    }
    name = "CppStarterProject"
    version = "0.1"
    requires = (
        "catch2/2.13.7",
        "docopt.cpp/0.6.2",
        "fmt/8.0.1",
        "spdlog/1.9.2",
        "tl-expected/1.0.0",
    )
    generators = "cmake", "gcc", "txt", "cmake_find_package"
    def requirements(self):
        if self.options.cpp_starter_use_imgui == "ON":
            self.requires("imgui-sfml/2.2@bincrafters/stable")
