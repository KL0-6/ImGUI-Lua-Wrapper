cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(ImguiWrapper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp" "src/*.c" "src/*.mm")

add_executable(ImguiWrapper
    src/main.cpp
    ${SOURCES}
)

target_include_directories(ImguiWrapper PRIVATE 
    src/dependencies
    src/dependencies/Luau
    src/dependencies/Luau/Ast/include
    src/dependencies/Luau/Common/include
    src/dependencies/Luau/Compiler/include
    src/dependencies/Luau/VM/include
)

find_package(glfw3 REQUIRED)

target_link_libraries(ImguiWrapper 
    GL
    glfw
)
