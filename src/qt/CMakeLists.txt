find_package(Qt6Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
add_executable(CashOverflow qtMain.cpp TabDialog.cpp AccountsTab.cpp)
# set_target_properties( helloQt PROPERTIES CMAKE_AUTOMOC ON )
target_link_libraries(CashOverflow
  project_warnings
  project_options
  Qt6::Widgets)
target_compile_features(CashOverflow PUBLIC cxx_nullptr cxx_lambdas)
