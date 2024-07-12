#ifndef IMGUIWIDGETS_WINDOW_H
#define IMGUIWIDGETS_WINDOW_H

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
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
        virtual void render() = 0;
    };

    struct button : public base
    {
        std::string text;
        std::function<void()> callback;

        void render() override;
    };

    struct label : public base
    {
        std::string text;

        void render() override;
    };

    struct window
    {
        std::string title;
        int lua_ref;
        
        std::vector<base*> children;

        void render();
    };

    extern std::vector<window*> windows;
}

#endif // IMGUIWIDGETS_WINDOW_H