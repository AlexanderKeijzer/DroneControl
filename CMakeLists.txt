cmake_minimum_required(VERSION 3.4)
project(DroneControl VERSION 0.1.0)

option(WITH_VISUALIZATION "Enable visualization" ON)

add_subdirectory(simulation)
include_directories(${DroneControlSimulation_INCLUDE_DIRS})

if(WITH_VISUALIZATION)
    add_definitions(-DUSE_VISULATIZATION)
    add_subdirectory(visualization)
    include_directories(${DroneControlVisualization_INCLUDE_DIRS})
endif()

add_executable(${PROJECT_NAME} main.cpp)
add_library(${PROJECT_NAME}Lib STATIC main.cpp)

target_link_libraries(${PROJECT_NAME} DroneControlSimulation)

if(WITH_VISUALIZATION)
    target_link_libraries(${PROJECT_NAME} DroneControlVisualization)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)