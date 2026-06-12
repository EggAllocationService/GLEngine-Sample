cmake_minimum_required(VERSION 4.2)
project(GLEngine_Sample)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(engine)

add_executable(sample main.cpp
        components/PortalMeshComponent.cpp
        components/PortalMeshComponent.h
        actors/PortalPyramid.cpp
        actors/PortalPyramid.h)

create_resource_library(
        NAME DemoShaders
        SOURCES
            portal.wgsl
)

build_pak(
        NAME assets
        SOURCES
            assets/pyramid.obj
            assets/end_portal.png
        NAMES
            /pyramid.obj
            /portal.png
)

target_link_libraries(sample glengine DemoShaders)
target_include_directories(sample PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
add_dependencies(sample assets)

engine_copy_dll(sample)