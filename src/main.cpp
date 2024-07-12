#include <iostream>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h> 

#include "core/api/api.h"

int main()
{
    if (!glfwInit())
    {
        std::printf("[FATAL ERROR]: Failed to initialize GLFW!");

        return 0;
    }

    lua_State* L = api::initialize();
    if(L == nullptr)
    {
        std::printf("[FATAL ERROR]: Failed to initialize lua_State!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
#if defined(__APPLE__)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#elif
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    if(monitor == nullptr)
    {
        std::printf("[FATAL ERROR]: Failed to get primary monitor!");

        return 0;
    }

    int xpos = 0;
    int ypos = 0;
    int width = 0;
    int height = 0;

    glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);

    GLFWwindow* window = glfwCreateWindow(width, height, "Window", nullptr, nullptr);

    if (window == nullptr)
    {
        std::printf("[FATAL ERROR]: Failed to create window!");

        return 0;
    }

    /*
    window::button* button = new window::button;
    button->text = "Click me!";
    button->callback = []()
    {
        std::printf("Button Clicked!\n");
    };

    window::window* win = new window::window;
    win->title = "Hello!";
    win->children.push_back(button);

    window::windows.push_back(win);
    */
   
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);

    ImGui_ImplOpenGL3_Init(nullptr);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int w, h;
        glfwGetFramebufferSize(window, &w, &h);

        ImGui::SetNextWindowSize(ImVec2(w, h)); 
        ImGui::SetNextWindowPos(ImVec2(0, 0));

        for(window::window* win : window::windows)
            win->render();

        ImGui::Render();
        
        glViewport(0, 0, w, h);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}