cmake_minimum_required(VERSION 3.4...3.18)
project(Pybind11ExampleSharingArrays)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/pybind11)
pybind11_add_module(Pybind11ExampleSharingArrays src/main.cpp)
