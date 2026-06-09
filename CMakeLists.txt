cmake_minimum_required(VERSION 4.2)
project(GLEngine_Sample)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(engine)

add_executable(sample main.cpp)

target_link_libraries(sample glengine)

engine_copy_dll(sample)