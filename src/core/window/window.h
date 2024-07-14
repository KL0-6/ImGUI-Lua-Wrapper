#ifndef IMGUIWIDGETS_WINDOW_H
#define IMGUIWIDGETS_WINDOW_H

#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h> 
#include <lualib.h>

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
        lua_State* L;
        int lua_ref = 0;
        virtual void render() = 0;
    };

    struct button : public base
    {
        std::string text; // Required
        int callback_ref = 0;

        void render() override;
    };

    struct label : public base
    {
        std::string text; // Required

        void render() override;
    };

    struct separator : public base
    {
        std::string text; 
        float extra_width = 0.0f; 

        void render() override;
    };

    struct window
    {
        std::string title; // Required
        int lua_ref;
        
        std::vector<base*> children;

        void render();
    };

    extern std::vector<window*> windows;
}

#endif // IMGUIWIDGETS_WINDOW_H