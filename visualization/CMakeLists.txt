cmake_minimum_required(VERSION 3.4)
project(DroneControlVisualization)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/" ${CMAKE_MODULE_PATH})

# Add Corrade as a subproject
add_subdirectory(corrade EXCLUDE_FROM_ALL)

# Add Magnum as a subproject, enable Sdl2Application
set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/SDL2-2.0.10 ${CMAKE_PREFIX_PATH})
set(WITH_SDL2APPLICATION ON)
add_subdirectory(magnum EXCLUDE_FROM_ALL)

add_subdirectory(src)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src
                                 ${PROJECT_SOURCE_DIR}/magnum/src
                                 ${PROJECT_SOURCE_DIR}/corrade/src
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)