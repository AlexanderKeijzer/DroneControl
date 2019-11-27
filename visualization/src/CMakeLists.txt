find_package(Magnum REQUIRED GL Sdl2Application)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

include_directories(src)

include_directories(${DroneControlSimulation_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp" "*.hpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(DroneControlVisualization PRIVATE
    Corrade::Main
    Magnum::Application
    Magnum::GL
    Magnum::Magnum
    Magnum::MeshTools
    Magnum::Primitives
    Magnum::Shaders)

# Make the executable a default target to build & run in Visual Studio
#set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MyApplication)
