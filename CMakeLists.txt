cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(ImguiWrapper LANGUAGES C CXX)

set(PLATFORM_LIBS)
set(PLATFORM_SOURCES)

if (NOT MSVC)
    find_package(glfw3)
    if(APPLE)
        list(APPEND PLATFORM_LIBS "-framework OpenGL")
    else()
        list(APPEND PLATFORM_LIBS GL)
    endif()
else()
    add_subdirectory(glfw)
    list(APPEND PLATFORM_LIBS OpenGL32)
endif()

option(IMGUIWIDGETS_NIX_X11 "Enable X11 support" ON)
option(IMGUIWIDGETS_NIX_WAYLAND "Enable Wayland support" ON)
option(IMGUIWIDGETS_NIX_GNOME "Enable GNOME support" ON)
option(IMGUIWIDGETS_NIX_KDE "Enable KDE support" ON)
option(IMGUIWIDGETS_NIX_XFCE "Enable Xfce support" ON)
option(IMGUIWIDGETS_NIX_LXQT "Enable LXQt support" ON)
option(IMGUIWIDGETS_NIX_LXDE "Enable LXDE support" ON)

set(LUAU_BUILD_CLI OFF)
set(LUAU_BUILD_WEB OFF)
set(LUAU_BUILD_TESTS OFF)
add_subdirectory(luau/)

add_executable(ImguiWrapper
    src/main.cpp
    src/core/api/api.cpp
    src/core/api/metatable.cpp
    src/core/window/windows.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_draw.cpp
    imgui/imgui.cpp
    imgui/backends/imgui_impl_glfw.cpp 
    imgui/backends/imgui_impl_opengl3.cpp
)

set_target_properties(ImguiWrapper PROPERTIES CXX_STANDARD 17)

target_include_directories(ImguiWrapper PRIVATE 
    src/dependencies
    Luau/Analysis/include
    Luau/Ast/include
    Luau/Common/include
    Luau/Compiler/include
    Luau/VM/include
    Luau/VM/src
    imgui/
)

target_link_libraries(ImguiWrapper
    ${PLATFORM_LIBS}
    glfw
	Luau.Common
	Luau.Ast
	Luau.Compiler
	Luau.Config
	Luau.Analysis
	Luau.CodeGen
	Luau.VM
)
