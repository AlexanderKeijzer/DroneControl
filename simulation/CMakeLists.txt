cmake_minimum_required(VERSION 3.4)
project(DroneControlSimulation)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "include/*.hpp")

include_directories(include)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)