# CMakeLists.txt file for generating the build system for saying hello from C++ in Python
cmake_minimum_required(VERSION 3.16...3.29)
project(hello VERSION 0.1.0 LANGUAGES C)

find_package(Python COMPONENTS Development.Module REQUIRED)

python_add_library(hello MODULE hello.c WITH_SOABI)

install(TARGETS hello LIBRARY DESTINATION .)
