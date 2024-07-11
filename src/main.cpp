#include <iostream>

#include <Imgui/imgui.h>
#include <Imgui/imgui_impl_glfw.h>
#include <Imgui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h> 

int main()
{
    if (!glfwInit())
    {
        std::printf("[FATAL ERROR]: Failed to initialize GLFW!");

        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#if defined(__APPLE__)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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

        ImGui::Begin("Test");
        {

            ImGui::End();
        }


        ImGui::Render();
        
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
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