cmake_minimum_required(VERSION 3.4)
project(DroneControl VERSION 0.1.0)

add_subdirectory(simulation)
#add_subdirectory(visualization)

include_directories(${DroneControlSimulation_INCLUDE_DIRS})
#include_directories(${DroneControlVisualization_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} DroneControlSimulation)
#target_link_libraries(${PROJECT_NAME} DroneControlVisualization)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)