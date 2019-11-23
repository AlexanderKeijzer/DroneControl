find_package(Magnum REQUIRED GL Sdl2Application)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

include_directories(src)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp" "*.hpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(DroneControlVisualization PRIVATE
    Magnum::Application
    Magnum::GL
    Magnum::Magnum)

# Make the executable a default target to build & run in Visual Studio
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MyApplication)
