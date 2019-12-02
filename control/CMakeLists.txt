cmake_minimum_required(VERSION 3.4)
project(DroneControlControl)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ build)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

add_subdirectory(pybind11)
pybind11_add_module(${PROJECT_NAME} pythonInterface.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE DroneControlLib)
target_link_libraries(${PROJECT_NAME} PRIVATE DroneControlSimulation)
target_link_libraries(${PROJECT_NAME} PRIVATE DroneControlVisualization)