from conans import ConanFile


class CppStarterProject(ConanFile):
    name = "CppStarterProject"
    version = "0.1"
    requires = (
        "fmt/8.0.1",
        "imgui-sfml/2.2@bincrafters/stable",
    )
    generators = "cmake", "gcc", "txt", "cmake_find_package"
