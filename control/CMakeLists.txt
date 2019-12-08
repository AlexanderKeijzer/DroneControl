cmake_minimum_required(VERSION 3.4)
project(DroneControlControl)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ build)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
include_directories(${DroneControlSimulation_INCLUDE_DIRS})

add_subdirectory(pybind11)
pybind11_add_module(${PROJECT_NAME} pythonInterface.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE DroneControlLib)
target_link_libraries(${PROJECT_NAME} PRIVATE DroneControlSimulation)

if(WITH_VISUALIZATION)
    target_link_libraries(${PROJECT_NAME} PRIVATE DroneControlVisualization)
endif()