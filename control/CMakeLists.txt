cmake_minimum_required(VERSION 3.4)
project(DroneControlControl)

add_subdirectory(pybind11)
pybind11_add_module(${PROJECT_NAME} pythonInterface.cpp)