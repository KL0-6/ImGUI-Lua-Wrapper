#ifndef _window_h_
#define _window_h_

#include <Imgui/imgui.h>
#include <Imgui/imgui_impl_glfw.h>
#include <Imgui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h> 

#include <string>
#include <vector>
#include <functional>

namespace window
{
    struct base
    {
        protected:
	        ~base() = default;

        public:
            int lua_ref = 0;
            virtual void render() {};
    };

    struct button : public base
    {
        std::string text;

        std::function<void()> callback;

        void render() override
        {
            if(ImGui::Button(text.c_str()))
                callback();
        }
    };

    struct label : public base
    {
        std::string text;

        void render() override
        {
            ImGui::Text(text.c_str());
        }
    };

    struct window
    {
        std::string title;
        int lua_ref;
        
        std::vector<base*> children;

        void render()
        {
            ImGui::Begin(title.c_str());

            for(auto child : children)
                child->render();

            ImGui::End();
        }
    };

    inline std::vector<window*> windows;
}

#endif