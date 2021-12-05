cmake_minimum_required(VERSION 3.4...3.18)
project(browser_translate)

add_subdirectory(third_party/pybind11)
add_executable(browser_translate src/translate.cpp)
target_link_libraries(browser_translate PRIVATE pybind11::embed)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(browser_translate
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})