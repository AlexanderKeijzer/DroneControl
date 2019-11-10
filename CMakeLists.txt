cmake_minimum_required(VERSION 3.0.0)
project(DroneControl VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(include)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "include/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
